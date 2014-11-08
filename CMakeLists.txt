
cmake_minimum_required (VERSION 2.6)

project (RoboRally)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_executable(RoboRally src/main.cpp)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2 REQUIRED system window graphics audio)
find_package(GLEW REQUIRED)
find_package(SFGUI REQUIRED)

target_link_libraries(RoboRally ${SFML_LIBRARIES} ${SFML_LIBRARIES} ${SFGUI_LIBRARY})
