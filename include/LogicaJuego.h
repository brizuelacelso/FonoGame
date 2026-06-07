#pragma once
#include <string>
#include "Pokedex.h"

// Adentro de tu clase principal o estructura de estado:
/**
 * @brief Instancia del jugador que almacena el progreso de recolección.
 */
Pokedex pokedexJugador;

/**
 * @brief Estado de la interfaz del menú Pokédex.
 */
bool menuPokedexAbierto = false;

/**
 * @brief Posición actual del cursor/scroll dentro de la lista de la Pokédex.
 */
int scrollPokedex = 1;

/**
 * @brief Cantidad total de Pokémon implementados en el motor del juego.
 */
const int MAX_POKEMON = 151;

/**
 * @brief Obtiene el nombre en texto de un Pokémon.
 * @param id El número identificador del Pokémon (1 a MAX_POKEMON).
 * @return std::string Nombre oficial del Pokémon.
 */
std::string getPokemonName(int id);

/**
 * @brief Calcula cuántos cambios hay que hacerle a s1 para que sea igual a s2.
 * @param s1 La palabra base u original.
 * @param s2 La palabra a comparar.
 * @return int El costo de operaciones (distancia). 0 = idénticas.
 */
int calcularDistanciaLevenshtein(const std::string& s1, const std::string& s2);

/**
 * @brief Evalúa si el texto hablado coincide con el texto objetivo aplicando tolerancia a errores.
 * @param expected La frase fonética que se espera escuchar.
 * @param actual La cadena de texto cruda devuelta por el micrófono.
 * @return true Si la similitud fonética es aprobada.
 * @return false Si no se entienden las palabras clave.
 */
bool CheckPronunciation(const std::string& expected, std::string actual);