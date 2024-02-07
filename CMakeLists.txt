# CMakeLists.txt for the main project directory

# Set minimum CMake version
cmake_minimum_required(VERSION 3.0)

# Project name
project(LcdMenuBuilder)

# Add source files for the library
set (LIB_SRC LcdMenuBuilder/src)

    set(LCDBUILDER_SOURCES
    ${LIB_SRC}/MenuConfig.cpp
    ${LIB_SRC}/MenuItem.cpp
    ${LIB_SRC}/MenuSystem.cpp
    ${LIB_SRC}/MenuWidgets/SubMenu.cpp
    ${LIB_SRC}/MenuWidgets/CheckBoxList.cpp
    ${LIB_SRC}/MenuWidgets/RadioList.cpp
    ${LIB_SRC}/MenuWidgets/TextInputItem.cpp
)


# Create the library
add_library(LcdMenuBuilder ${LCDBUILDER_SOURCES})

# Include directories for the library header files
target_include_directories(LcdMenuBuilder PUBLIC LcdMenuBuilder/inc)

# Add the executable
add_executable(example Example/Main.cpp)

# Link the executable with the LcdMenuBuilder library
target_link_libraries(example LcdMenuBuilder)

# Clean target to remove extra files
add_custom_target(clean_extra_files
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.cmake
    COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_BINARY_DIR}/*.txt
    # Add any other file extensions you want to remove
    COMMENT "Cleaning extra generated files"
)
