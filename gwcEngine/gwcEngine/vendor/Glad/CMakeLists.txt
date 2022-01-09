cmake_minimum_required(VERSION 3.16)

set(SRC  
    "src/glad.c"
    )


include_directories("include")

add_library(Glad STATIC ${SRC})
target_compile_options(Glad PRIVATE -save-temps=obj)
