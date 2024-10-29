SET(TARGET_NAME ${MODULE_NAME}_template)

add_executable(${TARGET_NAME}_trailing_return_type
    trailing_return_type_demo.cc
)

target_include_directories(${TARGET_NAME}_trailing_return_type PUBLIC
    ${PROJECT_SOURCE_DIR}/src
)

install(TARGETS ${TARGET_NAME}_trailing_return_type
    DESTINATION ${PROJECT_SOURCE_DIR}/bin
)