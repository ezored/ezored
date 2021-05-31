if(PROJECT_TARGET_NAME STREQUAL "tests")
    # module files
    file(GLOB_RECURSE H_FILES_CXX "${PROJECT_MODULES_PATH}/target-tests/tests/include/*.hpp")
    file(GLOB_RECURSE S_FILES_CXX "${PROJECT_MODULES_PATH}/target-tests/tests/src/*.cpp")

    file(GLOB H_FILES_LOGGER_IMPL "${PROJECT_MODULES_PATH}/logger/implementation/cpp/ezored/util/Simple*.hpp")
    file(GLOB S_FILES_LOGGER_IMPL "${PROJECT_MODULES_PATH}/logger/implementation/cpp/ezored/util/Simple*.cpp")

    file(GLOB H_FILES_HTTP_CLIENT_IMPL "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.hpp")
    file(GLOB S_FILES_HTTP_CLIENT_IMPL "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.cpp")

    file(GLOB H_FILES_SHARED_DATA_IMPL "${PROJECT_MODULES_PATH}/shared-data/implementation/cpp/ezored/data/Simple*.hpp")
    file(GLOB S_FILES_SHARED_DATA_IMPL "${PROJECT_MODULES_PATH}/shared-data/implementation/cpp/ezored/data/Simple*.cpp")

    file(GLOB H_FILES_FILE_HELPER_IMPL "${PROJECT_MODULES_PATH}/file-helper/implementation/cpp/ezored/io/Simple*.hpp")
    file(GLOB S_FILES_FILE_HELPER_IMPL "${PROJECT_MODULES_PATH}/file-helper/implementation/cpp/ezored/io/Simple*.cpp")

    # header files
    project_add_header_files("${H_FILES_CXX}")

    project_add_header_files("${H_FILES_LOGGER_IMPL}")
    project_add_header_files("${H_FILES_HTTP_CLIENT_IMPL}")
    project_add_header_files("${H_FILES_SHARED_DATA_IMPL}")
    project_add_header_files("${H_FILES_FILE_HELPER_IMPL}")

    # source files
    project_add_source_files("${S_FILES_CXX}")

    project_add_source_files("${S_FILES_LOGGER_IMPL}")
    project_add_source_files("${S_FILES_HTTP_CLIENT_IMPL}")
    project_add_source_files("${S_FILES_SHARED_DATA_IMPL}")
    project_add_source_files("${S_FILES_FILE_HELPER_IMPL}")

    # search paths
    project_add_search_path("${PROJECT_MODULES_PATH}/target-tests/tests/include")
endif()
