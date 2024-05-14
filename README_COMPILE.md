# Author 
 Junyeong Cho
 PLS contact me if you have any questions or concerns
 Email: saviour2111@gmail.com

# GAM250 Engine

This engine is based on OpenGL and offers both version 4.2, which uses shaders, and version 2.2, which does not use shaders, simultaneously.

This will be a cross platform targeting Windows & Web platforms as a minimum and possibly the Ubuntu & Mac platforms.


## How to Build and Run

First Setup your [Development Environment](docs/DevEnvironment.md)
And then follow the instructions below to build and run the project.



### Command Line Build

#### General Steps

**Release**
run the following commands in the terminal not bash(a.k.a Ubuntu on Windows)
If the build is successful, the .sln file will be in the build folder.
```sh
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

**Debug**
run the following commands in the terminal not bash(a.k.a Ubuntu on Windows)
If the build is successful, the .sln file will be in the build folder.
```sh
cmake -B build -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build/build --config Debug
```

**Emscripten**
PLS DO NOT USE THIS COMMAND 
THIS MAY CAUSE ERRORS
```sh
source /path/to/emsdk/emsdk_env.sh
emcmake cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
python3 -m http.server -d ./build/executables/
# Open Web Browser and go to http://localhost:8000/Release/graphics_fun.html
```

#### Recommended for Copy/Paste Commands
```sh
cmake -B build/release -S . -DCMAKE_BUILD_TYPE=Release
cmake -B build/debug -S . -DCMAKE_BUILD_TYPE=Debug
source ~/emsdk/emsdk_env.sh
emcmake cmake -B build/webrelease -S . -DCMAKE_BUILD_TYPE=Release
emcmake cmake -B build/webdebug -S . -DCMAKE_BUILD_TYPE=Debug
cmake --build build/release --config Release
cmake --build build//debug --config Debug
cmake --build build/webrelease --config Release
cmake --build build/webdebug --config Debug
```

