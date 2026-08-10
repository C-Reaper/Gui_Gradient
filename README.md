# Project README

## Overview
- The project is a simple graphical application that generates and displays 2D and 3D hill noise patterns.

## Features
- Generates 2D hill noise using `HillNoise_2D` function.
- Generates 3D hill noise using `HillNoise_3D` function.
- Displays the generated noise in a window with adjustable frequency.

## Project Structure

### Prerequisites
- C/C++ Compiler and Debugger (GCC, Clang)
- Make utility
- Standard development tools
- X11 library for Linux
- User32, GDI32, Winmm libraries for Windows

## Build & Run

### Building on Linux
```bash
cd <Project>
make -f Makefile.linux all
```

To run the application:
```bash
./build/Main
```

### Building on Windows
```bash
cd <Project>
make -f Makefile.windows all
```

To run the application:
```bash
build\Main.exe
```

### Building for Wine (Cross-compiling for Windows on Linux)
```bash
cd <Project>
make -f Makefile.wine all
```

To run the application within Wine:
```bash
WINEPREFIX=~/wine64 WINEARCH=win64 wine build/Main.exe
```

### Building for WebAssembly with Emscripten
```bash
cd <Project>
make -f Makefile.web all
```

To serve and run the application:
```bash
emrun --no_browser --port 8080 build/index.html
```