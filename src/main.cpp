#include "raylib.h"
#include "AudioIA.h"
#include "LogicaJuego.h"
#include "Graficos.h"
#include "Mapa.h"
#include <vector>
#include <string>

/**
 * @brief Máquina de estados finitos (FSM) que controla el flujo general de la aplicación.
 */
enum GameState { ESTADO_MAPA, ESTADO_BATALLA, ESTADO_MENU_PAUSA };

/**
 * @brief Punto de entrada principal de FonoJuego. 
 * Contiene el Game Loop principal a 60 FPS y orquesta todos los módulos.
 */
int main() {
    const int screenWidth = 800;
    const int screenHeight = 600; 
    InitWindow(screenWidth, screenHeight, "FonoJuego: Menú y Aventura");

    if (!InitAudioAndAI()) return 1; // Salida segura si falla la IA
    InitGraficos();

    SetTargetFPS(60);

    // Variables de estado global
    GameState estadoActual = ESTADO_MAPA;
    int playerCol = 1;
    int playerFila = 1;
    int currentId = 0;
    
    // Variables del sistema de batalla y reconocimiento de voz
    std::string textoEscuchado = "...";
    bool isProcessing = false;
    bool isCorrect = false;

    // Variables de la interfaz de menú
    std::vector<std::string> opcionesMenu = {"Pokédex", "Mochila", "Guardar", "Volver"};
    int opcionSeleccionada = 0;

    // ==========================================
    // GAME LOOP PRINCIPAL
    // ==========================================
    while (!WindowShouldClose()) {
        
        // --- 1. LÓGICA DE CONTROL (INPUT & ESTADOS) ---
        if (estadoActual == ESTADO_MAPA) {
            int nextCol = playerCol;
            int nextFila = playerFila;

            // Detección de movimiento
            if (IsKeyPressed(KEY_RIGHT)) nextCol++;
            if (IsKeyPressed(KEY_LEFT)) nextCol--;
            if (IsKeyPressed(KEY_DOWN)) nextFila++;
            if (IsKeyPressed(KEY_UP)) nextFila--;

            // Si el jugador intentó moverse
            if (nextCol != playerCol || nextFila != playerFila) {
                // Validación contra obstáculos físicos (árboles, paredes)
                if (!EsColision(nextCol, nextFila)) {
                    playerCol = nextCol;
                    playerFila = nextFila;

                    // Lógica de encuentros aleatorios (RNG)
                    if (EsPastoAlto(playerCol, playerFila)) {
                        if (GetRandomValue(1, 100) <= 15) { // 15% de probabilidad de aparición
                            currentId = GetRandomValue(1, MAX_POKEMON);
                            LoadPokemon(currentId);
                            textoEscuchado = "...";
                            isCorrect = false;
                            estadoActual = ESTADO_BATALLA; 
                        }
                    }
                }
            }

            // Abrir menú de pausa interactivo
            if (IsKeyPressed(KEY_M)) {
                estadoActual = ESTADO_MENU_PAUSA;
                opcionSeleccionada = 0; 
            }
        } 
        else if (estadoActual == ESTADO_MENU_PAUSA) {
            // Navegación circular del menú
            if (IsKeyPressed(KEY_DOWN)) {
                opcionSeleccionada++;
                if (opcionSeleccionada >= opcionesMenu.size()) opcionSeleccionada = 0;
            }
            if (IsKeyPressed(KEY_UP)) {
                opcionSeleccionada--;
                if (opcionSeleccionada < 0) opcionSeleccionada = opcionesMenu.size() - 1;
            }

            // Confirmación de selección
            if (IsKeyPressed(KEY_SPACE)) {
                if (opcionesMenu[opcionSeleccionada] == "Volver") {
                    estadoActual = ESTADO_MAPA;
                }
            }

            // Salida rápida
            if (IsKeyPressed(KEY_X)) {
                estadoActual = ESTADO_MAPA;
            }
        }
        else if (estadoActual == ESTADO_BATALLA) {
            // Mientras mantenga la 'R', vaciamos el buffer para limpiar ruido previo
            if (IsKeyPressed(KEY_R)) ClearAudioBuffer(); 

            // Al soltar la 'R', se detiene la grabación y empieza el análisis
            if (IsKeyReleased(KEY_R)) {
                isProcessing = true;
                // Forzamos un frame intermedio para mostrar "Procesando..." al usuario
                DrawGameScreen(screenWidth, screenHeight, currentId, textoEscuchado, isCorrect, false, isProcessing); 
                
                textoEscuchado = ProcessAudio();
                
                std::string fraseEsperada = "atrapar a " + getPokemonName(currentId);
                isCorrect = CheckPronunciation(fraseEsperada, textoEscuchado);
                
                isProcessing = false;
            }

            // Éxito fonético y salida de la batalla
            if (isCorrect && IsKeyPressed(KEY_SPACE)) {
                estadoActual = ESTADO_MAPA;
            }

            // Huir de la batalla prematuramente
            if (IsKeyPressed(KEY_X)) {
                estadoActual = ESTADO_MAPA;
                isCorrect = false;          
                textoEscuchado = "...";
            }
        }

        // --- 2. RENDERIZADO GRÁFICO (OUTPUT) ---
        BeginDrawing();
        ClearBackground(BLACK);

        if (estadoActual == ESTADO_MAPA || estadoActual == ESTADO_MENU_PAUSA) {
            DrawMapa();
            
            // Dibujado temporal del jugador (Cuadro rojo)
            DrawRectangle(playerCol * TILE_SIZE, playerFila * TILE_SIZE, TILE_SIZE, TILE_SIZE, RED);
            
            if (estadoActual == ESTADO_MAPA) {
                DrawText("Tecla M: Menú | FLECHAS: Moverse", 10, 10, 20, WHITE);
            }

            // Overlay (capa superior) del Menú de Pausa
            if (estadoActual == ESTADO_MENU_PAUSA) {
                int menuWidth = 200;
                int menuHeight = 250;
                int menuX = screenWidth - menuWidth - 20; 
                int menuY = 20;

                // Sombra y recuadro
                DrawRectangle(menuX + 5, menuY + 5, menuWidth, menuHeight, ColorAlpha(BLACK, 0.5f));
                DrawRectangle(menuX, menuY, menuWidth, menuHeight, RAYWHITE);
                DrawRectangleLines(menuX, menuY, menuWidth, menuHeight, DARKGRAY);

                for (size_t i = 0; i < opcionesMenu.size(); i++) {
                    Color colorTexto = DARKGRAY;
                    
                    if (i == opcionSeleccionada) {
                        colorTexto = RED;
                        DrawText(">", menuX + 15, menuY + 25 + (i * 50), 20, RED);
                    }
                    
                    DrawText(opcionesMenu[i].c_str(), menuX + 40, menuY + 25 + (i * 50), 25, colorTexto);
                }
                
                DrawText("[ESPACIO] Elegir   [X] Salir", menuX + 10, menuY + menuHeight + 10, 15, RAYWHITE);
            }
        } 
        else if (estadoActual == ESTADO_BATALLA) {
            bool isRecording = IsKeyDown(KEY_R);
            DrawGameScreen(screenWidth, screenHeight, currentId, textoEscuchado, isCorrect, isRecording, isProcessing);
            DrawText("Di: 'Atrapar a [Nombre]'", 20, 70, 20, DARKBLUE);
            DrawText("Presiona [X] para huir", 20, 100, 18, GRAY);
            if (isCorrect) DrawText("¡CAPTURADO! Presiona ESPACIO para volver al mapa", 100, 480, 20, DARKGREEN);
        }

        EndDrawing();
    }

    // Limpieza de memoria y salida limpia
    CloseGraficos();
    CloseAudioAndAI();
    CloseWindow();

    return 0;
}