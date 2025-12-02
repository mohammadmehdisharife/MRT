rm -rf build
mkdir build

# linux
gcc csxl.c function.c memory.c -o ./build/csxl

# win64
x86_64-w64-mingw32-gcc csxl.c function.c memory.c -o ./build/csxl_win64.exe

# win32
i686-w64-mingw32-gcc csxl.c function.c memory.c -o ./build/csxl_win32.exe
