#include <string>
#include "raylib.h"
#include "../include/Pokedex.h"

// Esta función iría dentro de tu clase/módulo Graficos
void dibujarMenuPokedex(const Pokedex& miPokedex, int indiceInicio) {
    // 1. Dibujar el fondo del menú (ej: un gris oscuro semi-transparente)
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Fade(BLACK, 0.8f));
    
    // Título de la pantalla
    DrawText("POKEDEX NACIONAL", 50, 30, 40, RAYWHITE);

    int posX = 80;
    int posY = 100;
    int separacionY = 80; // Espacio entre cada renglón

    // Dibujamos 6 Pokémon en pantalla a la vez
    for (int i = indiceInicio; i < indiceInicio + 6; i++) {
        if (i > 151) break; 
        
        // Pedimos los datos procesados (oculta los no vistos)
        EntradaPokedex poke = miPokedex.obtenerDatosParaMenu(i);
        
        // --- A. DIBUJAR EL SPRITE ---
        // Lo ideal acá es: DrawTexture(texturaCargada, posX, posY, WHITE);
        // Por ahora, dibujamos un rectángulo simulando el espacio del sprite (64x64)
        if (poke.visto) {
            DrawRectangle(posX, posY, 64, 64, LIGHTGRAY); // Placeholder del sprite real
        } else {
            DrawRectangle(posX, posY, 64, 64, DARKGRAY);  // Placeholder de "???"
            DrawText("?", posX + 25, posY + 15, 40, GRAY); // Signo de pregunta
        }

        // --- B. DIBUJAR EL ID Y EL NOMBRE ---
        // Formateamos el texto, ej: "N.o 4 - Charmander" o "N.o 5 - ???"
        std::string textoMostrar = "N.o " + std::to_string(poke.id) + " - " + poke.nombre;
        
        // Elegimos el color del texto dependiendo si lo vimos o no
        Color colorTexto = poke.visto ? RAYWHITE : GRAY;
        DrawText(textoMostrar.c_str(), posX + 90, posY + 20, 30, colorTexto);

        // --- C. DIBUJAR LA POKEBALL (SI ESTÁ CAPTURADO) ---
        if (poke.capturado) {
            // Simulamos el ícono de la pokeball con un círculo rojo
            DrawCircle(posX + 400, posY + 35, 15, RED);
            DrawCircle(posX + 400, posY + 35, 10, WHITE);
            DrawLine(posX + 385, posY + 35, posX + 415, posY + 35, BLACK);
            DrawCircle(posX + 400, posY + 35, 4, BLACK);
        }

        // Bajamos para dibujar la siguiente fila
        posY += separacionY;
    }

    // Dibujar instrucciones abajo
    DrawText("Usa las FLECHAS para navegar - ESC para salir", 50, GetScreenHeight() - 50, 20, LIGHTGRAY);
}