# libeventsystem - Simple event system for C++ projects

The goal was to separate my event system from network library logic. That's it.

## Conan install dependencies

```bash 
conan install . --build=missing -s build_type=Debug --output-folder="conan/Debug"
conan install . --build=missing -s build_type=Release --output-folder="conan/Release"
```

## Configure and build 

```bash
mkdir -p cmake-build && cd cmake-build
cmake .. -DCMAKE_TOOLCHAIN_FILE="../conan/Debug/conan_toolchain.cmake"
cmake --build .
```

## Usage

...

