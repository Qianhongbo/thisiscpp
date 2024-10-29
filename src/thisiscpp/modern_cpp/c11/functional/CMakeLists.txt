SET(TARGET_NAME ${MODULE_NAME}_functional)

add_executable(${TARGET_NAME}_bind
    bind_demo.cc
)

target_include_directories(${TARGET_NAME}_bind PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

target_link_libraries(${TARGET_NAME}_bind
    GTest::GTest
    GTest::Main
)

install(TARGETS ${TARGET_NAME}_bind
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)