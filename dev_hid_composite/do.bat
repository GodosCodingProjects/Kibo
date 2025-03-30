
:: BUILD
:: Setup cmake and build the project
cmake -S . -B build
cmake --build build

:: INSTALL
:: Send the executable to the pico, it has to be in receive mode
copy /y build\dev_hid_composite.uf2 D:\
