This is an open source template for a Switch inspired homebrew app launcher.  It's written in C with SDL2 as a dependency.

![travis](https://travis-ci.org/vgmoose/switch_launcher.svg?branch=master)

### Dependencies
- SDL2, SDL2_image (libpng, zlib), SDL2_ttf (freetype, bz2)
- jsmn (included) json library

### Building
The below should build and run a `switch_launcher` executable:
```
git clone --recursive https://github.com/vgmoose/switch_launcher
cd switch_launcher
make
make run
```

A windows standalone `switch_launcher.exe` can also be built (from linux/unix). It will require mingw32, and the needed SDL libraries.
```
git clone --recursive https://github.com/vgmoose/switch_launcher
cd switch_launcher
make windows
wine switch_launcher.exe
```

### License
This software is licensed under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html). If you make derivatives of this software, please make the source code available.
