build:
	# create linux/unix binary
	gcc -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf jsmn/jsmn.h jsmn/jsmn.c src/*.h src/*.c -o switch_launcher

debug:
	gcc -g -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf jsmn/jsmn.h jsmn/jsmn.c src/*.h src/*.c -o switch_launcher

windows:
	# building jsmn
	cd jsmn && make
	
	# create windows binary
	i686-w64-mingw32-gcc src/*.h src/*.c jsmn/jsmn.h jsmn/jsmn.c -o switch_launcher.exe -Wl,-Bstatic,--whole-archive -lSDL2_image -lSDL2_ttf -lSDL2main -lSDL2 -lfreetype -lbz2 -lpng -lz -Wl,--no-whole-archive -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid --static

clean:
	cd jsmn && make clean
	rm switch_launcher switch_launcher.exe

run:
	./switch_launcher
