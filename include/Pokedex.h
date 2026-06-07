#ifndef POKEDEX_H
#define POKEDEX_H

#include <vector>
#include <string>

/**
 * @brief Estructura de datos interna que representa el registro individual de un Pokémon.
 */
struct EntradaPokedex {
    int id;                 ///< Número identificador de la Pokédex Nacional.
    std::string nombre;     ///< Nombre oficial del Pokémon.
    bool visto;             ///< True si el jugador lo encontró en estado salvaje alguna vez.
    bool capturado;         ///< True si el jugador logró atraparlo exitosamente.
    std::string rutaSprite; ///< Ruta relativa del archivo de imagen para cargarlo.
};

/**
 * @brief Clase encargada de gestionar la base de datos de los Pokémon y el progreso del jugador.
 */
class Pokedex {
private:
    std::vector<EntradaPokedex> listaPokemon; ///< Contenedor principal con todos los registros.

public:
    /**
     * @brief Constructor por defecto. Inicializa la lista y pre-carga los datos básicos.
     */
    Pokedex();

    /**
     * @brief Registra un Pokémon como "visto" cuando aparece en la hierba alta.
     * @param id El identificador numérico del Pokémon encontrado.
     * @return void (No retorna valor).
     */
    void registrarVisto(int id);

    /**
     * @brief Registra un Pokémon como "capturado" tras atraparlo (lo marca automáticamente como visto también).
     * @param id El identificador numérico del Pokémon atrapado.
     * @return void (No retorna valor).
     */
    void registrarCapturado(int id);

    /**
     * @brief Devuelve los datos listos y filtrados para renderizar el menú visual. 
     * Si el Pokémon no fue visto aún, enmascara el nombre (devuelve "???") y devuelve un sprite neutro.
     * @param id El identificador numérico a consultar en la lista.
     * @return EntradaPokedex Una copia del registro con los datos reales o censurados según su estado.
     */
    EntradaPokedex obtenerDatosParaMenu(int id) const;
};

#endif // POKEDEX_H