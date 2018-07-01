# Libraries:

link_libraries (gcc)

set (hwlib ${build_environment}/libraries/hwlib)
include_directories (${hwlib}/library)

set (catch ${build_environment}/libraries/Catch2)
include_directories (${catch}/single_include)

# Source Files:

set (sources
    ./src/esp32.cpp
    ./src/memory_map.hpp
    ./src/i2c.hpp
    ./src/twi.hpp
)
