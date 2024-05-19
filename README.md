# TP_Jazz_Jackrabbit_2

Trabajo Práctico Final de la materia Taller de Programación I.

| **Integrantes** | **Padrón** | **Email** |
| :-------------: | :--------: | :-------: |
| Buono, Fernando | 103523 | <fbuono@fi.uba.ar> |
| Duca, Francisco | 106308 | <fduca@fi.uba.ar> |
| Oshiro, Lucas | 107024 | <loshiro@fi.uba.ar> |
| Shiao, Tomás Jorge | 106099 | <tshiao@fi.uba.ar> |

## Informes

Los sprites fueron obtenidos desde [aquí](https://www.spriters-resource.com/pc_computer/jazzjackrabbit2thesecretfiles/), mientras que se usan los sonidos obtenidos desde [aquí](https://www.sounds-resource.com/pc_computer/jazzjackrabbit/sound/18894/).

## Dependencias

Comando completo para configurar y construir sh
# Actualizar los repositorios
sudo apt-get update

# Instalar las bibliotecas necesarias de Qt5, yaml-cpp y SDL2_image
sudo apt-get install qtbase5-dev qtdeclarative5-dev qt5-qmake qttools5-dev-tools
sudo apt-get install libyaml-cpp-dev
sudo apt-get install libsdl2-image-dev

# Crear y entrar al directorio de compilación 
mkdir build
cd build

# Configurar el proyecto con CMake
cmake ..

# Compilar el proyecto
make -j$(nproc)

# Ejecutar el cliente
./jazz_jackrabbit_2

# Ejecutar el servidor
./jazz_jackrabbit_2-server

# Ejecutar las pruebas
ctest
