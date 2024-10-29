SET(MODULE_NAME "c17")
SET(TARGET_NAME ${MODULE_NAME}_demo)

# use cpp 17 standard
SET(CMAKE_CXX_STANDARD 17)

add_executable(${TARGET_NAME}
    c17_demo.cc
)