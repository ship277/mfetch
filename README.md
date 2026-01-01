# Mfetch
Basically "Mayurifetch".
It's a lightweight program meant to cleanly display images in a window, and get a new random one by right-clicking on it. 

### Usage
1. Place the executable in the same directory as the folder with your images
2. Make sure the folder with images is named "Mayushii" (This name is hardcoded, but you can easily change it in the source code and rebuild again).
3. Run the executable.
4. Left click to move window, right click to randomize pic, ESC to close window.

### Dependencies
- SDL3
- SDL3_image
- CMake

### Building from source
> [!NOTE]
> A compiled release is available only for Windows. Sample assets are also in the release

For GNU/Linux and Windows:
```sh
git clone https://github.com/ship277/mfetch.git
cd mfetch
mkdir build
cmake -B build
cmake --build build
```
The resulting executable will be available at ``build/src/mayurifetch``. Grab it from there and place in the appropriate directory for it to work.
