CCFLAGS = -Oz
SRC = csxl.c function.c utils.c memory.c log.c

all:
	mkdir build
	gcc $(CCFLAGS) $(SRC) -o ./build/csxl
	x86_64-w64-mingw32-gcc $(CCFLAGS) $(SRC) -o ./build/csxl_win64.exe
	i686-w64-mingw32-gcc $(CCFLAGS) $(SRC) -o ./build/csxl_win32.exe

clean:
	rm -rf build *.zip *.tar*

format:
	astyle --style=linux *.c
	astyle --style=linux *.h
