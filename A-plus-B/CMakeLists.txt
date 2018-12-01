cmake_minimum_required(VERSION 3.0)
project(runtest)

# With main
add_executable(main 
    test_main.cpp
    test_helper.cpp
    )

target_link_libraries(main pthread)

add_executable(generate
    generate.cpp
    )
