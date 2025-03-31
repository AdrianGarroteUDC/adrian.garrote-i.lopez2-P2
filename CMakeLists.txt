cmake_minimum_required(VERSION 3.30)
project(adrian_garrote_i_lopez2_P2 C)

set(CMAKE_C_STANDARD 11)

find_package(MPI REQUIRED)

include_directories(${MPI_INCLUDE_PATH})

add_executable(adrian_garrote_i_lopez2_P2
        pi.c
        func_col_mpi.c
        func_col_mpi.h)

target_link_libraries(adrian_garrote_i_lopez2_P2 ${MPI_LIBRARIES})