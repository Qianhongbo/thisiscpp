SET(MODULE_NAME "priority_queue")

SET(TARGET_NAME ${MODULE_NAME}_simple)

add_executable(${TARGET_NAME}_test
    simple_priority_queue_test.cc
)

target_include_directories(${TARGET_NAME}_test PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}_test
    GTest::GTest
    GTest::Main
)

SET(TARGET_NAME ${MODULE_NAME})

add_executable(${TARGET_NAME}
    priority_queue_test.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)
