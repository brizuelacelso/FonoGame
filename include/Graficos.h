#pragma once
#include "raylib.h"
#include <string>
#include "../include/Pokedex.h" // <-- 1. Agregá esto arriba

/**
 * @brief Inicializa configuraciones visuales adicionales si el motor lo requiere.
 */
void InitGraficos();

/**
 * @brief Libera de la memoria RAM/VRAM las texturas cargadas (como el Pokémon actual).
 */
void CloseGraficos();

/**
 * @brief Carga en memoria la textura de un Pokémon específico.
 * @param id El número de la Pokédex del Pokémon a cargar.
 */
void LoadPokemon(int id);

/**
 * @brief Renderiza la pantalla principal del combate fonético.
 * @param screenWidth Ancho de la ventana en píxeles.
 * @param screenHeight Alto de la ventana en píxeles.
 * @param currentId ID del Pokémon salvaje actual.
 * @param textoEscuchado Lo que la IA entendió que el jugador dijo.
 * @param isCorrect Bandera que indica si la pronunciación superó la prueba.
 * @param isRecording Bandera que indica si el micrófono está activo.
 * @param isProcessing Bandera que indica si Whisper está procesando el audio.
 */
void DrawGameScreen(int screenWidth, int screenHeight, int currentId, 
                    const std::string& textoEscuchado, bool isCorrect, 
                    bool isRecording, bool isProcessing);

/**
 * @brief Renderiza el menú superpuesto de la Pokédex.
 * @param miPokedex Referencia constante a los datos actuales de la Pokédex.
 * @param indiceInicio Índice de scroll para saber qué Pokémon dibujar primero.
 */
void dibujarMenuPokedex(const Pokedex& miPokedex, int indiceInicio);