cmake_minimum_required(VERSION 3.16)

project(cnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ambil semua file .cpp di src dan subfoldernya
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Tambahkan include path supaya header di subfolder bisa diakses
target_include_directories(${PROJECT_NAME}
    PRIVATE
    src
)