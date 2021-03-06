cmake_minimum_required(VERSION 3.9)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

project(lexer CXX)

add_executable(lexer 
    src/main.cpp
    src/app.cpp             src/app.hpp
    src/lexercore.cpp       src/lexercore.hpp
    src/lexer.cpp           src/lexer.hpp
    src/token.cpp           src/token.hpp
    src/util/color.cpp      src/util/color.hpp
    src/util/string.cpp     src/util/string.hpp
    )
    
target_link_libraries(lexer 
    )

target_include_directories(lexer
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/src/util
    SYSTEM
        ${CMAKE_CURRENT_SOURCE_DIR}/external
    )

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    target_compile_options(lexer
        PUBLIC
            -Wall 
            -Wextra 
            -Werror=return-type
            -Werror=switch
        
            -Werror
            -Wshadow
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    target_compile_options(lexer
        PUBLIC
            -Wall 
            -Wextra 
            -Werror=return-type
            -Werror=switch
            -Wfatal-errors
        
            -Werror
            -Wshadow
            -Wnon-virtual-dtor
            -Wold-style-cast
            -Wcast-align
            -Wunused
            -Woverloaded-virtual
            -Wpedantic
            -Wconversion
            -Wsign-conversion
            -Wmisleading-indentation
            -Wduplicated-cond
            -Wlogical-op
            -Wnull-dereference
            -Wdouble-promotion
            -Wformat=2
    )
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    target_compile_options(lexer
        PUBLIC     
            /permissive
            /W4
            /w14640
            /w14242
            /w14254
            /w14263
            /w14265
            /w14287
            /we4289
            /w14296
            /w14311
            /w14545
            /w14546
            /w14547
            /w14549
            /w14555
            /w14640
            /w14826
            /w14905
            /w14906
            /w14928
    )
    source_group("src"           REGULAR_EXPRESSION "src/.*")
    source_group("src\\util"     REGULAR_EXPRESSION "src/util/.*")
endif()
