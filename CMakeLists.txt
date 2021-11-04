cmake_minimum_required(VERSION 3.17)
project(playground VERSION 1.0.0)

add_executable(playground)
target_precompile_headers(playground PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:${CMAKE_CURRENT_SOURCE_DIR}/include/pch.h>")

target_sources(playground
    PRIVATE
        include/playground.h
        include/dynArray.h
        include/stack.h
        include/queue.h
        include/sLinkedList.h

        playground.cpp
)

target_include_directories(playground
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/include
)

target_compile_features(playground PRIVATE cxx_std_17)

target_link_libraries(playground
    PRIVATE
)
