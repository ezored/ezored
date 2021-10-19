# module files
file(GLOB H_FILES "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/cpp/ezored/net/http/*.hpp")
file(GLOB H_FILES_IMPL "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/*.hpp")
file(GLOB H_FILES_CONTROLLER "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/controller/*.hpp")
file(GLOB H_FILES_HELPER "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/helper/*.hpp")

file(GLOB S_FILES "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/cpp/ezored/net/http/*.cpp")
file(GLOB S_FILES_IMPL "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/*.cpp")
file(GLOB S_FILES_CONTROLLER "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/controller/*.cpp")
file(GLOB S_FILES_HELPER "${PROJECT_MODULES_PATH}/http-server/implementation/cpp/ezored/net/http/helper/*.cpp")

# project files
project_add_header_files("${H_FILES}")
project_add_header_files("${H_FILES_IMPL}")
project_add_header_files("${H_FILES_CONTROLLER}")
project_add_header_files("${H_FILES_HELPER}")

project_add_source_files("${S_FILES}")
project_add_source_files("${S_FILES_IMPL}")
project_add_source_files("${S_FILES_CONTROLLER}")
project_add_source_files("${S_FILES_HELPER}")

# search paths
project_add_search_path("${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/cpp")
project_add_search_path("${PROJECT_MODULES_PATH}/http-server/implementation/cpp")
