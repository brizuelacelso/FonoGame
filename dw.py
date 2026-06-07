import os
import requests

# 1. Definimos la ruta de destino
folder_path = "assets/sprites/pokes"

# 2. Creamos la carpeta si no existe
if not os.path.exists(folder_path):
    os.makedirs(folder_path)
    print(f"Carpeta creada en: {folder_path}")

# 3. Descargamos los 151 Pokémon
base_url = "https://raw.githubusercontent.com/PokeAPI/sprites/master/sprites/pokemon/"

print("Iniciando descarga de la primera generación...")

for i in range(1, 152):
    file_name = f"{i}.png"
    url = base_url + file_name
    
    response = requests.get(url)
    
    if response.status_code == 200:
        with open(os.path.join(folder_path, file_name), 'wb') as f:
            f.write(response.content)
        if i % 10 == 0:
            print(f"Descargados {i}/151...")
    else:
        print(f"Error al descargar el Pokémon #{i}")

print("¡Listo! Ya tenés a los 151 en tu carpeta de assets.")