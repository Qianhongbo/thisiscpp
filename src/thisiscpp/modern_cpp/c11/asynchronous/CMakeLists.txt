SET(TARGET_NAME ${MODULE_NAME}_future)

add_executable(${TARGET_NAME}
    future_demo.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

SET(TARGET_NAME ${MODULE_NAME}_async)

add_executable(${TARGET_NAME}
    async_demo.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

SET(TARGET_NAME ${MODULE_NAME}_promise)

add_executable(${TARGET_NAME}
    promise_demo.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)

SET(TARGET_NAME ${MODULE_NAME}_packaged_task)

add_executable(${TARGET_NAME}
    packaged_task_demo.cc
)

target_include_directories(${TARGET_NAME} PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)