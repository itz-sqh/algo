cmake_minimum_required(VERSION 3.31)
project(algo)

set(CMAKE_CXX_STANDARD 23)

file(GLOB_RECURSE HEADER_FILES
        "*.h"
)

add_library(algo_library INTERFACE)

target_include_directories(algo_library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

function(add_all_subdirectories base_dir)
    file(GLOB subdirs LIST_DIRECTORIES true "${base_dir}/*")
    foreach(subdir ${subdirs})
        if(IS_DIRECTORY ${subdir})
            target_include_directories(algo_library INTERFACE ${subdir})
            add_all_subdirectories(${subdir})
        endif()
    endforeach()
endfunction()

add_all_subdirectories(${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} algo_library)