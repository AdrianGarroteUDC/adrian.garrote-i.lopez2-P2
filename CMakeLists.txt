cmake_minimum_required(VERSION 3.30)
project(adrian_garrote_i_lopez2_P2 C)

set(CMAKE_C_STANDARD 11)

# Buscar las bibliotecas de MPI
find_package(MPI REQUIRED)

# Incluir las rutas de encabezados de MPI
include_directories(${MPI_INCLUDE_PATH})

add_executable(adrian_garrote_i_lopez2_P2
    pi.c)

# Enlazar las bibliotecas MPI al ejecutable
target_link_libraries(adrian_garrote_i_lopez2_P2 ${MPI_LIBRARIES})