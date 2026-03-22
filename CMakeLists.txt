cmake_minimum_required(VERSION 3.16)

project(cnake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Ambil semua file .cpp
file(GLOB_RECURSE SOURCES
    src/*.cpp
)

# Tambahin resource kalau Windows
if (WIN32)
    set(RESOURCES icon.rc)
endif()

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${RESOURCES}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
    src
)

# Static linking (biar gak butuh g++ runtime)
if (MINGW)
    target_link_options(${PROJECT_NAME} PRIVATE
        -static
        -static-libgcc
        -static-libstdc++
        -pthread
    )
endif()