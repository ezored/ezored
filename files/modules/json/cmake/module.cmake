# module files
file(GLOB H_FILES "${PROJECT_MODULES_PATH}/json/implementation/cpp/ezored/json/*.hpp")

# project files
project_add_header_files("${H_FILES}")

# search paths
project_add_search_path("${PROJECT_MODULES_PATH}/json/implementation/cpp")
