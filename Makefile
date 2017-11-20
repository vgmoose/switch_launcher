build:
	# create Linux binary
	gcc -lSDL2 -lSDL2main src/*.h src/*.c -o template

windows:
	# create windows binary
	i686-w64-mingw32-gcc src/*.h src/*.c -o template.exe -lSDL2 -lSDL2main -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid --static

run:
	./template
