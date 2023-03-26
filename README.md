# kill the enemies

the game about killing the enemies =D

# play

download the zip from releases, go into the directory and open the binary, it should work and I might make a windows version one day

# dependencies

cmake, a c++ compiler

entt is already there, you need to install [sfml](https://www.sfml-dev.org/tutorials/2.5/#getting-started) and [nlohmann-json](https://json.nlohmann.me/)

# build

first clone the repo

```
git clone <whatever the url for this repo is>
cd /path/to/kill-the-enemies
```
then you need to build the thing and this is what the [nvim cmake plugin](https://github.com/cdelledonne/vim-cmake) does when I run `:CMakeGenerate` or `:CMakeBuild` so I think it should work if you just manually type it
```
cmake -D CMAKE_BUILD_TYPE=Debug -S . -B Debug
cmake --build Debug
```
the binary will be in the Debug directory hopefully
cp the res directory in there or move the binary to a directory with it who cares

if this doesn't work let me know and I **MIGHT** fix it

# contribute

my hunger for pull requests is insatiable

# credits

krizej - textures, fixed a gamebreaking bug

kamil stoch - added 'kamil stoch - added 'kamil stoch - added 'kamil stoch - added 'kamil stoch - added 'kamil stoch - added '*RecursionError: maximum recursion depth exceeded*' to credits' to credits' to credits' to credits' to credits' to credits

yup that's it for now I'll gladly put you on this list if you do anything
