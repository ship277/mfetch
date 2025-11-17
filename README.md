this was not intended with distribution in mind; a lot of variables and names are only relevant for myself.
i made this program as a hobby project to easily fetch images of my favorite character from my collection. it's just under 200 lines of code so it's easily recreated.
if you want to use this you'll have to edit the source code, following the instructions below.

Requirements:
SDL3, SDL3_image

Get the repo:
'git clone https://github.com/ship277/mfetch.git'

Modify the code:
'src/mayushiifetch.cpp' -> edit line 26 (required), line 29 (optional), and 76 (required only for windows)
CML files -> 2 of them in total, replace the targets with your desired name (optional)

Build 

'''cd mfetch
cmake -B build
cmake --build build
cd src/build
./[name of the program(default: mayushiifetch)]'''