SET(MODULE_NAME "singleton_pattern")

SET(TARGET_NAME ${MODULE_NAME}_test)

add_executable(${TARGET_NAME}
    singleton_pattern_test.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)