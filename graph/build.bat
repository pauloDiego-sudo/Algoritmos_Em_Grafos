@REM @REM g++ -o graph.exe main.cpp data_structure/src/*.cpp algorithms/src/*.cpp -I data_structure/include -I algorithms/include

mkdir build
cd build
cmake -G "MinGW Makefiles" ..
cmake --build . --target clean
cmake --build .