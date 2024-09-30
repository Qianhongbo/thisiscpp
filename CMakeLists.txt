cmake_minimum_required(VERSION 3.10)

project(thisiscpp VERSION 1.0)

find_package(GTest REQUIRED)

set(
    SUBMODULES
    priority_queue
)

foreach(submodule ${SUBMODULES})
    add_subdirectory(src/thisiscpp/${submodule})
endforeach()