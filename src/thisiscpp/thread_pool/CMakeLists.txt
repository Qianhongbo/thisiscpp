SET(MODULE_NAME "thread_pool")

SET(TARGET_NAME ${MODULE_NAME})

add_executable(${TARGET_NAME}_test
    thread_pool_test.cc
)

target_include_directories(${TARGET_NAME}_test PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}_test
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}_test
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)