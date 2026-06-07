#include "LogicaJuego.h"
#include <vector>
#include <algorithm>
#include <cctype>
#include <sstream>

/**
 * @brief Busca el nombre oficial del Pokémon en un diccionario estático.
 * Se usa 'static' para que el vector se inicialice en memoria una sola vez 
 * durante toda la ejecución del juego, optimizando el rendimiento.
 */
std::string getPokemonName(int id) {
    static const std::vector<std::string> names = {
        "Nadie", "Bulbasaur", "Ivysaur", "Venusaur", "Charmander", "Charmeleon", "Charizard",
        "Squirtle", "Wartortle", "Blastoise", "Caterpie", "Metapod", "Butterfree",
        "Weedle", "Kakuna", "Beedrill", "Pidgey", "Pidgeotto", "Pidgeot", "Rattata",
        "Raticate", "Spearow", "Fearow", "Ekans", "Arbok", "Pikachu", "Raichu",
        "Sandshrew", "Sandslash", "Nidoran-f", "Nidorina", "Nidoqueen", "Nidoran-m",
        "Nidorino", "Nidoking", "Clefairy", "Clefable", "Vulpix", "Ninetales",
        "Jigglypuff", "Wigglytuff", "Zubat", "Golbat", "Oddish", "Gloom", "Vileplume",
        "Paras", "Parasect", "Venonat", "Venomoth", "Diglett", "Dugtrio", "Meowth",
        "Persian", "Psyduck", "Golduck", "Mankey", "Primeape", "Growlithe", "Arcanine",
        "Poliwag", "Poliwhirl", "Poliwrath", "Abra", "Kadabra", "Alakazam", "Machop",
        "Machoke", "Machamp", "Bellsprout", "Weepinbell", "Victreebel", "Tentacool",
        "Tentacruel", "Geodude", "Graveler", "Golem", "Ponyta", "Rapidash", "Slowpoke",
        "Slowbro", "Magnemite", "Magneton", "Farfetch'd", "Doduo", "Dodrio", "Seel",
        "Dewgong", "Grimer", "Muk", "Shellder", "Cloyster", "Gastly", "Haunter",
        "Gengar", "Onix", "Drowzee", "Hypno", "Krabby", "Kingler", "Voltorb",
        "Electrode", "Exeggcute", "Exeggutor", "Cubone", "Marowak", "Hitmonlee",
        "Hitmonchan", "Lickitung", "Koffing", "Weezing", "Rhyhorn", "Rhydon",
        "Chansey", "Tangela", "Kangaskhan", "Horsea", "Seadra", "Goldeen", "Seaking",
        "Staryu", "Starmie", "Mr. Mime", "Scyther", "Jynx", "Electabuzz", "Magmar",
        "Pinsir", "Tauros", "Magikarp", "Gyarados", "Lapras", "Ditto", "Eevee",
        "Vaporeon", "Jolteon", "Flareon", "Porygon", "Omanyte", "Omastar", "Kabuto",
        "Kabutops", "Aerodactyl", "Snorlax", "Articuno", "Zapdos", "Moltres",
        "Dratini", "Dragonair", "Dragonite", "Mewtwo", "Mew"
    };
    if (id >= 1 && id <= MAX_POKEMON) return names[id];
    return "Desconocido";
}

/**
 * @brief Implementa la Programación Dinámica (Matriz) para resolver la distancia de Levenshtein.
 * Compara dos palabras y determina cuántos "errores" (cambios de letras) hay entre ellas.
 */
int calcularDistanciaLevenshtein(const std::string& s1, const std::string& s2) {
    int m = s1.size();
    int n = s2.size();
    
    // Creamos una matriz bidimensional (dp) para guardar los subresultados.
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    // Inicializamos los bordes de la matriz (casos base de palabras vacías)
    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    // Llenamos la matriz calculando el mínimo costo de edición
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                // Si la letra es igual, no hay costo adicional
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                // Si es distinta, tomamos el mínimo entre: borrar, insertar o sustituir (+1 error)
                dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
    }
    return dp[m][n]; // El resultado final queda en la última celda
}

/**
 * @brief Analiza el texto detectado por el micrófono y lo valida contra el texto objetivo.
 * Normaliza las mayúsculas y signos de puntuación antes de aplicar el chequeo de tolerancia.
 */
bool CheckPronunciation(const std::string& expected, std::string actual) {
    // 1. Normalización a minúsculas
    std::transform(actual.begin(), actual.end(), actual.begin(), ::tolower);
    std::string expectedLower = expected;
    std::transform(expectedLower.begin(), expectedLower.end(), expectedLower.begin(), ::tolower);
    
    // Vía rápida: Si la frase exacta está contenida en lo escuchado, aprobamos de inmediato.
    if (actual.find(expectedLower) != std::string::npos) return true;

    // 2. Tokenización (separar la frase en palabras sueltas)
    std::stringstream ss(actual);
    std::string palabra;
    
    // Nivel de permisividad (Hasta 3 letras distintas por palabra son aceptadas)
    int tolerancia = 3; 

    // Revisamos palabra por palabra lo que entendió Whisper
    while (ss >> palabra) {
        // Borramos puntos o comas que la IA suele agregar automáticamente
        palabra.erase(std::remove_if(palabra.begin(), palabra.end(), ::ispunct), palabra.end());
        
        // Si alguna palabra hablada se parece a la frase completa esperada (dentro del umbral)
        // Damos la captura por válida. (Ideal para nombres cortos de Pokémon).
        if (calcularDistanciaLevenshtein(expectedLower, palabra) <= tolerancia) {
            return true;
        }
    }
    
    return false; // La pronunciación falló la validación
}