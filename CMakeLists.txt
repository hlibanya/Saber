cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_DIR out)

add_library(LinkedList app/LinkedListSolution/LinkedList.cpp)
add_library(PrintBinary app/PrintBinarySolution/PrintBinary.cpp)
add_library(RemoveDups app/RemoveDupsSolution/RemoveDups.cpp)

add_subdirectory(ext/cpputest-3.8/)

project(Saber)
add_executable(Saber 
main.cpp 
app/LinkedListSolution/tests.cpp
app/RemoveDupsSolution/tests.cpp 
app/PrintBinarySolution/tests.cpp
)

target_include_directories(Saber PUBLIC ext/cpputest-3.8/include/)
target_link_libraries(Saber PUBLIC CppUTest LinkedList PrintBinary RemoveDups)