This is an open source template for a Switch inspired homebrew app launcher.  It's written in C with SDL2 as a dependency.

[![Build Status](https://travis-ci.org/vgmoose/switch_launcher.svg?branch=master)](https://travis-ci.org/vgmoose/switch_launcher)

### Dependencies
- SDL2, SDL2_image (libpng, zlib), SDL2_ttf (freetype, bz2)
- jsmn (included) json library

### App info
App bundles should go in the "apps" folder relative to the main binary.

An app bundle is a folder with a name ending in ".app". Currently, it should have the following structure:
```
demo.app
├── icon.png
├── info.json
└── boot.nro
```

The layout is based on the [Homebrew Channel's layout](http://wiibrew.org/wiki/Homebrew_Channel#Configuring_Applications).

The `icon.png` should be a 300x210 PNG file.

The layout of `info.json` is as follows, no fields are mandatory:
```
{
	"name": "Homebrew Title",
	"description": "Homebrew description that takes up a couple of lines, about 4 at the most.",
	"long_description": "A really long description of the homebrew, that can have line breaks and such.\nIn order to ensure that all instructions are properly followed in case there's more information that needs to be conveyed than can be in the short description",
	"author": "Homebrew Author",
	"url": "http://example.com",
	"license": "MIT License",
	"source": "https://github.com/author/source"
}

`boot.nro` is a .nro file built by [libtransistor](https://github.com/reswitched/libtransistor). This is only a proposed file name/format, and is currently ignored by this template.
```

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

### Screen shot
![screenshot](https://i.imgur.com/nshBeDX.png)
