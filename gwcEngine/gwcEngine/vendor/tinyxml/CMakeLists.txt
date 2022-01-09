cmake_minimum_required(VERSION 3.16)

set(SRC  
    "./tinystr.cpp"
    "./tinyxml.cpp"
    "./xmltest.cpp"
    "./tinyxmlerror.cpp"
    "./tinyxmlparser.cpp"
    )

add_definitions("-DTIXML_USE_STL")
include_directories("include")

add_library(tinyxml STATIC ${SRC})
target_compile_options(tinyxml PRIVATE -save-temps=obj)
