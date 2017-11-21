This is an open source template for a Switch inspired appliation launcher.  It's written in C with SDL2 as a dependency.

### Dependencies
- SDL2 and SDL2_Image
- jsmn (included) json library

### Building
The below should build and run a `switch_launcher` executable:
```
git clone --recursive https://github.com/vgmoose/switch_launcher
cd switch_launcher
make
make run
```

A windows `switch_launcher.exe` can also be built (from linux/unix):
```
git clone --recursive https://github.com/vgmoose/switch_launcher
cd switch_launcher
make windows
wine switch_launcher.exe
```

### License
This software is licensed under the [GPLv3](https://www.gnu.org/licenses/gpl-3.0.en.html). If you make derivatives of this software, please make the source code available.

