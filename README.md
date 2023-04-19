# Primus Engine
## Overview
A lightweight Vulkan-based 3D game engine for producing small-scale FPS games.
## Pre-Requisites
-|Build|Run
-|-|-
[cmake](https://cmake.org/download/)|version 3.8 and above required|n/a
[mvsc](https://learn.microsoft.com/en-US/cpp/windows/latest-supported-vc-redist?view=msvc-170)|required|required
## Build Instructions
Run the build scripts under the root directory to automatically produce an executable.
Alternatively, build it yourself:
```
mkdir build
cd build
cmake .. -G"Unix Makefiles"
make
```