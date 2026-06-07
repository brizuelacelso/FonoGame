#pragma once

/**
 * @brief Cantidad total de columnas del mapa (eje X).
 */
const int MAP_COLUMNAS = 30;

/**
 * @brief Cantidad total de filas del mapa (eje Y).
 */
const int MAP_FILAS = 30;

/**
 * @brief Tamaño en píxeles de cada baldosa o tile.
 */
const int TILE_SIZE = 40;

/**
 * @brief Dibuja la cuadrícula y los elementos visuales del terreno en pantalla.
 * @return void (No retorna valor).
 */
void DrawMapa();

/**
 * @brief Verifica si una coordenada específica contiene un obstáculo infranqueable.
 * @param col La coordenada en el eje X (columna) a verificar.
 * @param fila La coordenada en el eje Y (fila) a verificar.
 * @return true Si hay una colisión (el jugador choca y no puede avanzar).
 * @return false Si el camino está libre para caminar.
 */
bool EsColision(int col, int fila);

/**
 * @brief Comprueba si el jugador pisó una zona de hierba alta donde hay encuentros salvajes.
 * @param col La coordenada en el eje X (columna).
 * @param fila La coordenada en el eje Y (fila).
 * @return true Si la baldosa corresponde a pasto alto.
 * @return false Si la baldosa es un terreno seguro.
 */
bool EsPastoAlto(int col, int fila);