cmake_minimum_required(VERSION 3.29)
project(Reto1)

set(CMAKE_CXX_STANDARD 20)

add_executable(Reto1 main.cpp
        subsequence.h
        huffman.h
        lcs.h
        palindrome.h)
