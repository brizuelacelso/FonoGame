#include "AudioIA.h"
#include "raylib.h"
#include "whisper.h"
#include <vector>
#include <mutex>
#include <iostream>

#ifndef ASSETS_PATH
#define ASSETS_PATH "assets"
#endif

const int SAMPLE_RATE = 16000;

std::vector<float> g_audioBuffer;
std::mutex g_audioMutex;
whisper_context* g_ctx = nullptr;
AudioStream g_micStream;

/**
 * @brief Callback disparado automáticamente por el hardware para recolectar muestras de micrófono.
 * Utiliza un mutex (candado) para prevenir colisiones de memoria entre el hilo de audio y el hilo del juego.
 * @param buffer Puntero a la memoria donde residen los datos de audio crudos.
 * @param frames Cantidad de muestras de audio (frames) en el búfer actual.
 */
void AudioInputCallback(void *buffer, unsigned int frames) {
    std::lock_guard<std::mutex> lock(g_audioMutex);
    float *samples = (float *)buffer;
    for (unsigned int i = 0; i < frames; i++) {
        g_audioBuffer.push_back(samples[i]);
    }
}

/**
 * @brief Implementación de la inicialización del motor de IA y hardware de sonido.
 * @return true Si todo arrancó sin problemas.
 * @return false Si falta el archivo del modelo GGML.
 */
bool InitAudioAndAI() {
    InitAudioDevice();
    g_micStream = LoadAudioStream(SAMPLE_RATE, 32, 1);
    SetAudioStreamCallback(g_micStream, AudioInputCallback);
    PlayAudioStream(g_micStream);

    std::string modelPath = std::string(ASSETS_PATH) + "/models/ggml-base.bin";
    
    whisper_context_params cparams = whisper_context_default_params();
    g_ctx = whisper_init_from_file_with_params(modelPath.c_str(), cparams);
    
    if (g_ctx == nullptr) {
        std::cerr << "Error crítico: No se encontró el modelo en " << modelPath << "\n";
        return false;
    }
    return true;
}

/**
 * @brief Descarga el modelo de la RAM y cierra el dispositivo de grabación.
 */
void CloseAudioAndAI() {
    UnloadAudioStream(g_micStream);
    CloseAudioDevice();
    if (g_ctx) whisper_free(g_ctx);
}

/**
 * @brief Vacía el búfer de audio de forma segura bloqueando el hilo temporalmente.
 */
void ClearAudioBuffer() {
    std::lock_guard<std::mutex> lock(g_audioMutex);
    g_audioBuffer.clear();
}

/**
 * @brief Procesa el audio recolectado utilizando la red neuronal Whisper.
 * Realiza una copia rápida del búfer para liberar el micrófono mientras la IA hace cálculos pesados.
 * @return std::string El texto transcrito.
 */
std::string ProcessAudio() {
    std::vector<float> bufferCopia;
    {
        // Sección crítica: copiamos los datos y vaciamos el original rapidísimo
        std::lock_guard<std::mutex> lock(g_audioMutex);
        if (g_audioBuffer.empty()) return "";
        bufferCopia = g_audioBuffer;
        g_audioBuffer.clear();
    }

    std::cout << "\n[DEBUG] Audio capturado: " << bufferCopia.size() << " muestras de sonido.\n";

    whisper_full_params params = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);
    params.language = "es";
    params.n_threads = 4;
    params.print_progress = false;

    std::string resultado = "";
    // whisper_full devuelve 0 si el procesamiento fue exitoso
    if (whisper_full(g_ctx, params, bufferCopia.data(), bufferCopia.size()) == 0) {
        int n_segments = whisper_full_n_segments(g_ctx);
        for (int i = 0; i < n_segments; ++i) {
            resultado += whisper_full_get_segment_text(g_ctx, i);
        }
    }
    
    std::cout << "[DEBUG] Whisper entendió: " << resultado << "\n";
    return resultado;
}