# CNAKE

![C++](https://img.shields.io/badge/C%2B%2B-20-blue)
![Build System](https://img.shields.io/badge/build-CMake-orange)
![License](https://img.shields.io/badge/license-MIT-green)
![Status](https://img.shields.io/badge/status-early%20development-red)
![Terminal Game](https://img.shields.io/badge/interface-terminal-black)
![Platform](https://img.shields.io/badge/platform-cross--platform-blue)

CNAKE is a classic snake game that runs entirely in the command line (terminal) without any graphical user interface.

This project is primarily developed as a personal exercise to explore algorithm implementation, data structures, and real-world application development using modern C++.

## Overview

CNAKE recreates the classic snake gameplay experience in a minimal environment: the terminal.
The game is implemented purely in C++ using the C++20 standard and relies only on the C++ standard library for its core systems.

The main goal of this project is to deepen understanding of software development processes and system design while building a fully functional terminal-based application.

## Concept

The core idea behind CNAKE is simple:

> Bring the classic snake game experience directly into the terminal.

Unlike many modern implementations that rely on graphical frameworks, CNAKE intentionally avoids any GUI and focuses on terminal-based gameplay.

This design encourages exploration of:

* low-level program structure
* algorithm design
* data structure implementation
* modular C++ project organization
* build system integration with CMake

## Current Development Status

CNAKE is currently in **early development and experimental stage**.

Core features are still being implemented, including:

* Snake movement system
* Reward/food mechanics
* Score system
* Game space management
* Core game loop

Because the project is still in the research and experimentation phase, detailed usage instructions and gameplay demonstrations are not yet available.

## Technologies

CNAKE is built using:

* **C++20**
* **CMake**
* **C++ Standard Library**

No external libraries are currently used for the core implementation.

## Project Structure

```bash
cnake/
│
├── src/
│   ├── main
│   ├── snake
│   ├── coordinate
│   └── direction
│
├── .gitignore
├── CMakeLists.txt
└── README.md
```

## Installation

Currently, CNAKE can be built by cloning the repository and compiling it with CMake.

```bash
git clone <repository-url>
cd cnake

mkdir build
cd build

cmake ..
cmake --build .
```

In the future, prebuilt executables or installers may be provided to simplify installation.

## Target Users

CNAKE is intended for anyone interested in experiencing a classic snake game directly in the terminal.

It may also be useful for:

* developers learning modern C++
* programmers exploring terminal-based applications
* students studying algorithmic game logic

## License

This project is licensed under the **MIT License**.
