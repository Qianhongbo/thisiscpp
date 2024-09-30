SET(MODULE_NAME "priority_queue")

SET(TARGET_NAME ${MODULE_NAME})

add_executable(${TARGET_NAME}_test
    priority_queue_test.cc
)

target_include_directories(${TARGET_NAME}_test PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}_test
    GTest::GTest
    GTest::Main
)