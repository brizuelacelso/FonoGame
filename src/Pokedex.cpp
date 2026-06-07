#include "Pokedex.h"

/**
 * @brief Constructor. Reserva espacio para los 151 Pokémon.
 */
Pokedex::Pokedex() {
    // Redimensionamos la memoria a 152 elementos para usar el ID directamente 
    // como índice (ej. listaPokemon[1] = Bulbasaur), ignorando la posición 0.
    listaPokemon.resize(152); 
    
    // TODO: Automatizar la carga masiva utilizando la función getPokemonName().
    // Ejemplo de inicialización manual estática:
    listaPokemon[1] = {1, "Bulbasaur", false, false, "sprites/001.png"};
    listaPokemon[4] = {4, "Charmander", false, false, "sprites/004.png"};
    listaPokemon[25] = {25, "Pikachu", false, false, "sprites/025.png"};
}

/**
 * @brief Activa la bandera de 'visto' de forma segura.
 */
void Pokedex::registrarVisto(int id) {
    if (id > 0 && id <= 151) {
        listaPokemon[id].visto = true;
    }
}

/**
 * @brief Activa las banderas de 'visto' y 'capturado' simultáneamente.
 */
void Pokedex::registrarCapturado(int id) {
    if (id > 0 && id <= 151) {
        listaPokemon[id].visto = true; 
        listaPokemon[id].capturado = true;
    }
}

/**
 * @brief Prepara la información visual para el renderizado del menú.
 * Si el jugador no ha descubierto al Pokémon, se devuelve un objeto censurado
 * para mantener la incertidumbre en la interfaz de usuario.
 */
EntradaPokedex Pokedex::obtenerDatosParaMenu(int id) const {
    // Validación de seguridad para evitar cuelgues (crashes)
    if (id <= 0 || id > 151) {
        return {0, "Error", false, false, "sprites/desconocido.png"};
    }

    EntradaPokedex datosReales = listaPokemon[id];

    // LA LÓGICA DEL MENÚ:
    if (!datosReales.visto) {
        // Si no lo vimos, devolvemos una estructura al vuelo con datos enmascarados
        return {
            id, 
            "???", // Nombre oculto
            false, 
            false, 
            "sprites/desconocido.png" // El sprite gris o signo de pregunta
        };
    }

    // Si ya lo vimos, la interfaz tiene permiso para leer los datos verdaderos
    return datosReales;
}