# Mfetch
Basically "Mayurifetch".
It's a lightweight program meant to display images in a window, and get a new random one by clicking on it. 

### Usage
1. Place the executable in the same directory as the folder with your images
2. Make sure it's named "Mayushii☆" (white star: u+2606). This name is hardcoded, but you can easily change it in the source code.
3. Run the executable

### Dependencies
- SDL3
- SDL3_image
- CMake

### Building from source
> [!NOTE]
> Building from source is currently the only way, but a release for windows is planned TBA.

For GNU/Linux and Windows:
```sh
git clone https://github.com/ship277/mfetch.git
cd mfetch
mkdir build
cmake -B build
cmake --build build
```
The resulting executable will be available at ``build/src/mayurifetch``. Grab it from there and place in the appropriate directory for it to work.
