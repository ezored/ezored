# module files
file(GLOB H_FILES "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/cpp/ezored/util/Logger*.hpp")
file(GLOB H_FILES_IMPL "${PROJECT_MODULES_PATH}/logger/implementation/cpp/ezored/util/Logger*.hpp")

file(GLOB S_FILES "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/cpp/ezored/util/Logger*.cpp")
file(GLOB S_FILES_IMPL "${PROJECT_MODULES_PATH}/logger/implementation/cpp/ezored/util/Logger*.cpp")

# project files
project_add_header_files("${H_FILES}")
project_add_header_files("${H_FILES_IMPL}")

project_add_source_files("${S_FILES}")
project_add_source_files("${S_FILES_IMPL}")

# search paths
project_add_search_path("${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/cpp")
project_add_search_path("${PROJECT_MODULES_PATH}/logger/implementation/cpp")
