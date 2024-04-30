import os
import random

VIRUS_SAMPLES_PATH: str = "../virus_samples"
CLEAN_SAMPLES_PATH: str = "../clean_samples"

cantidad_de_archivos: int = len(os.listdir(VIRUS_SAMPLES_PATH))

LIMITE_INFERIOR_CANTIDAD_DE_CARACTERES = 100_000
LIMITE_SUPERIOR_CANTIDAD_DE_CARACTERES = 10_000_000

print("Hay un total de", cantidad_de_archivos, "archivos en la carpeta virus_samples.")

for i in range(cantidad_de_archivos):
    print("Generando archivo", i + 1)
    cantidad_de_caracteres = random.randint(
        LIMITE_INFERIOR_CANTIDAD_DE_CARACTERES, LIMITE_SUPERIOR_CANTIDAD_DE_CARACTERES
    )
    nombre_archivo: str = f"{CLEAN_SAMPLES_PATH}/file_{i + 1}.bin"

    contenido: bytes = bytes(
        [random.randint(0, 255) for _ in range(cantidad_de_caracteres)]
    )

    with open(nombre_archivo, "wb") as file:
        file.write(contenido)

print()
print("Archivos generados correctamente.")
