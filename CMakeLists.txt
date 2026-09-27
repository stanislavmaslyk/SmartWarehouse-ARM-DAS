cmake_minimum_required(VERSION 3.20)

project(SmartWarehouse-ARM-DAS 
    VERSION 0.1.0 
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(warehouse_core STATIC
    include/warehouse/core/Product.hpp
    src/core/Product.cpp
    include/warehouse/core/PerishableProduct.hpp
    src/core/PerishableProduct.cpp
)

target_include_directories(warehouse_core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (MSVC)
    target_compile_options(warehouse_core PRIVATE /W4 /WX)
else()
    target_compile_options(warehouse_core PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

add_executable(warehouse_app
    src/main.cpp
)

target_link_libraries(warehouse_app PRIVATE
    warehouse_core
)