
# 🎮 FonoJuego: Aventura Fonética con IA

![C++](https://img.shields.io/badge/C++-17-blue.svg)
![Raylib](https://img.shields.io/badge/Raylib-5.5-red.svg)
![Whisper](https://img.shields.io/badge/Whisper.cpp-IA-green.svg)
![Build](https://img.shields.io/badge/Build-CMake-lightgrey.svg)

**FonoJuego** es un motor de videojuego top-down desarrollado en C++ que fusiona la exploración clásica con tecnología de **reconocimiento de voz en tiempo real**. Los jugadores deben explorar el mapa, encontrar criaturas en la hierba alta y pronunciar sus nombres correctamente por micrófono para registrarlos en su Pokédex.

---

## ✨ Características Principales

* **🎤 Interacción por Voz:** Integración nativa con `Whisper.cpp` para captura y transcripción de audio totalmente offline.
* **🧠 Tolerancia a Errores:** Sistema de validación fonética utilizando el algoritmo de **Distancia de Levenshtein**, permitiendo flexibilidad en la pronunciación (ideal para un juego interactivo).
* **🚀 Rendimiento Asíncrono:** La inferencia de la Inteligencia Artificial corre en hilos separados (`std::async`), garantizando que el motor gráfico funcione a 60 FPS sin bloqueos ni congelamientos.
* **🗺️ Arquitectura Modular:** Patrón de Máquina de Estados Finitos (FSM) para transiciones fluidas entre el mapa, las batallas fonéticas y la interfaz de la Pokédex.

---

## 🛠️ Tecnologías y Dependencias

* **Lenguaje:** C++17
* **Motor Gráfico:** [Raylib](https://www.raylib.com/)
* **Motor de IA:** [Whisper.cpp](https://github.com/ggerganov/whisper.cpp) (Modelo GGML Base en Español)
* **Build System:** CMake (Mínimo v3.16)

---

## 🚀 Guía de Instalación y Compilación

### 1. Dependencias Previas (Ejemplo para Fedora Linux)
Antes de compilar, asegurate de tener las herramientas de desarrollo y dependencias de audio instaladas:
```bash
sudo dnf install gcc-c++ cmake make alsa-lib-devel

```

### 2. Clonar el repositorio

```bash
git clone [https://github.com/TU_USUARIO/FonoJuego.git](https://github.com/TU_USUARIO/FonoJuego.git)
cd FonoJuego

```

### 3. Descargar el modelo de IA

*(Por cuestiones de peso, el modelo de Whisper no está incluido en el repositorio).*
Debes descargar el modelo `ggml-base.bin` y colocarlo en la ruta exacta dentro del proyecto:
`assets/models/ggml-base.bin`

### 4. Compilar el proyecto

El proyecto utiliza CMake para generar los binarios. Ejecuta:

```bash
mkdir build
cd build
cmake ..
make

```

### 5. Ejecutar el juego

```bash
./FonoJuego

```

---

## 🎮 Controles

* **Flechas Direccionales:** Mover al personaje por el mapa.
* **M:** Abrir el menú de pausa / Pokédex.
* **R (Mantener presionado):** Grabar audio por el micrófono durante un encuentro salvaje.
* **Espacio:** Confirmar selección / Continuar al capturar.
* **X:** Huir de la batalla / Cerrar menús.

---

## 🗺️ Próximos Pasos (Roadmap)

* [x] Integración del motor gráfico (Raylib) y compilación base.
* [x] Reconocimiento de voz asíncrono offline (Whisper.cpp).
* [x] Lógica de la Pokédex y auto-carga de base de datos.
* [ ] Implementación de sprites reales de los 151 Pokémon.
* [ ] Movimiento fluido del personaje y colisiones avanzadas.
* [ ] Efectos de sonido (SFX) y música de fondo ambiental.

---

## 🤝 Créditos y Reconocimientos

* **Desarrollo Core:** Celso Mateo Brizuela.
* **Librerías de terceros:** A los mantenedores de `Raylib` por su fantástico framework gráfico multiplataforma y a Georgi Gerganov por abrir la puerta al reconocimiento de voz eficiente con `Whisper.cpp`.
* *Aviso Legal:* Los nombres y referencias a la franquicia Pokémon son propiedad de Nintendo/Creatures Inc./GAME FREAK inc. Este es un proyecto de código abierto con fines estrictamente educativos y sin fines de lucro.

```

```
