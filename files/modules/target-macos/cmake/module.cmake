if(PROJECT_TARGET_NAME STREQUAL "macos")
    # module
    file(GLOB H_FILES_C "${PROJECT_ROOT_PATH}/projects/others/ezored/include/*.h")
    file(GLOB H_FILES_CXX "${PROJECT_ROOT_PATH}/projects/others/ezored/include/*.hpp")

    file(GLOB S_FILES_CXX "${PROJECT_ROOT_PATH}/projects/others/ezored/src/*.cpp")

    # merge
    project_add_header_files("${H_FILES_C}")
    project_add_header_files("${H_FILES_CXX}")

    project_add_source_files("${S_FILES_CXX}")
endif()
