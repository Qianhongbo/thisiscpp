SET(MODULE_NAME "c14")
SET(TARGET_NAME ${MODULE_NAME}_demo)

# use cpp 14 standard
SET(CMAKE_CXX_STANDARD 14)

add_executable(${TARGET_NAME}
    c14_demo.cc
)