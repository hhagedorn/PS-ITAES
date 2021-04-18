cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_STANDARD 11)

add_subdirectory(decryption)
add_subdirectory(encryption)

add_subdirectory(tests)