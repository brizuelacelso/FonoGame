#include "Mapa.h"
#include "raylib.h"

// Leyenda de la matriz:
// 0: Camino seguro (Gris)
// 1: Pasto Alto (Verde oscuro - ¡Peligro de Pokémon!)
// 2: Árboles / Pared (Marrón - No se puede caminar)
int mapaMatriz[MAP_FILAS][MAP_COLUMNAS] = {
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    {2,0,0,0,1,1,1,1,0,0,0,0,2,2,0,0,0,0,0,2},
    {2,0,0,0,1,1,1,1,0,0,0,0,2,2,0,0,0,0,0,2},
    {2,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,2},
    {2,2,2,0,0,0,0,0,0,0,2,2,2,0,0,0,1,1,0,2},
    {2,0,0,0,0,0,0,0,0,0,2,0,0,0,0,0,1,1,0,2},
    {2,0,0,1,1,1,1,0,0,0,2,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,0,2,0,0,0,0,0,0,0,0,2},
    {2,0,0,1,1,1,1,0,0,0,2,2,2,2,2,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,0,0,0,2,2,2,2,2,2,2,2},
    {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
    {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2},
    };
    
void DrawMapa() {
    for (int fila = 0; fila < MAP_FILAS; fila++) {
        for (int col = 0; col < MAP_COLUMNAS; col++) {
            int tileX = col * TILE_SIZE;
            int tileY = fila * TILE_SIZE;
            
            if (mapaMatriz[fila][col] == 0) {
                DrawRectangle(tileX, tileY, TILE_SIZE, TILE_SIZE, LIGHTGRAY);
            } else if (mapaMatriz[fila][col] == 1) {
                DrawRectangle(tileX, tileY, TILE_SIZE, TILE_SIZE, DARKGREEN);
            } else if (mapaMatriz[fila][col] == 2) {
                DrawRectangle(tileX, tileY, TILE_SIZE, TILE_SIZE, BROWN);
            }
            
            // Dibujamos las líneas de la grilla sutilmente
            DrawRectangleLines(tileX, tileY, TILE_SIZE, TILE_SIZE, ColorAlpha(BLACK, 0.1f));
        }
    }
}

bool EsColision(int col, int fila) {
    if (col < 0 || col >= MAP_COLUMNAS || fila < 0 || fila >= MAP_FILAS) return true;
    return (mapaMatriz[fila][col] == 2);
}

bool EsPastoAlto(int col, int fila) {
    if (col < 0 || col >= MAP_COLUMNAS || fila < 0 || fila >= MAP_FILAS) return false;
    return (mapaMatriz[fila][col] == 1);
}
