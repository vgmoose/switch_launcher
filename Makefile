build:
	# building jsmn
	cd jsmn && make
	
	# create linux/unix binary
	gcc -lSDL2 -lSDL2main src/*.h src/*.c jsmn/libjsmn.a -o switch_launcher

windows:
	# building jsmn
	cd jsmn && make
	
	# create windows binary
	i686-w64-mingw32-gcc src/*.h src/*.c jsmn/libjsmn.a -o switch_launcher.exe -lSDL2 -lSDL2main -lm -ldinput8 -ldxguid -ldxerr8 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lshell32 -lversion -luuid --static

clean:
	cd jsmn && make clean
	rm switch_launcher switch_launcher.exe

run:
	./switch_launcher
