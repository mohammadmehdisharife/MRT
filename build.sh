rm -rf build csxl.zip csxl.tar.gz
mkdir build

# linux
gcc -Oz csxl.c function.c utils.c memory.c log.c -o ./build/csxl

# win64
x86_64-w64-mingw32-gcc -Oz csxl.c function.c utils.c memory.c log.c -o ./build/csxl_win64.exe

# win32
i686-w64-mingw32-gcc -Oz csxl.c function.c utils.c memory.c log.c -o ./build/csxl_win32.exe

# create archive for release
zip -r csxl.zip build/
tar -czf csxl.tar.gz build/
