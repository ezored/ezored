# Configurations
cmake_minimum_required(VERSION 2.8.12)
get_filename_component(CMAKE_SOURCE_REALPATH "${CMAKE_SOURCE_DIR}/../../../../" REALPATH)

set(PROJECT_CONFIG_NAME "Sample" CACHE STRING "Project name")
set(PROJECT_CONFIG_CPP_STANDARD "11" CACHE STRING "11")
set(PROJECT_TARGET_NAME "linux_app" CACHE STRING "Target name")
set(PROJECT_CONFIG_ARCH "" CACHE STRING "Architecture")
set(PROJECT_ROOT_PATH ${CMAKE_SOURCE_REALPATH})
set(PROJECT_BUILD_DIR ${PROJECT_ROOT_PATH}/build/${PROJECT_TARGET_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_CONFIG_ARCH} CACHE INTERNAL "")

# Project
project(${PROJECT_CONFIG_NAME})

# Conan
include(${PROJECT_BUILD_DIR}/conan/conanbuildinfo.cmake)
conan_basic_setup()

# Include: common
add_subdirectory(
    ${PROJECT_ROOT_PATH}/files/cmake/common
    ${PROJECT_BUILD_DIR}/common
)

# Source files
file(GLOB S_FILES_PROJECT "${PROJECT_ROOT_PATH}/projects/samples/simple/*.cpp")

file(GLOB H_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Simple*.hpp")
file(GLOB S_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Simple*.cpp")

file(GLOB H_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.hpp")
file(GLOB S_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.cpp")

file(GLOB H_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/Simple*.hpp")
file(GLOB S_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/Simple*.cpp")

# Merge lists
set(
    TARGET_HEADER_FILES     
    ${H_FILES_LOGGER_LIB_IMPL}
    ${H_FILES_HTTP_CLIENT_LIB_IMPL}
    ${H_FILES_SHARED_DATA_LIB_IMPL}
)

set(
    TARGET_SOURCE_FILES     
    ${S_FILES_LOGGER_LIB_IMPL}
    ${S_FILES_HTTP_CLIENT_LIB_IMPL}
    ${S_FILES_SHARED_DATA_LIB_IMPL}
    ${S_FILES_PROJECT}    
)

set(
    PROJECT_SOURCE_FILES
    ${PROJECT_SOURCE_FILES}
    ${TARGET_SOURCE_FILES}
    ${TARGET_HEADER_FILES}
    CACHE INTERNAL ""
)

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PROJECT_CMAKE_C_FLAGS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_CMAKE_CXX_FLAGS}" CACHE INTERNAL "")

# Project
include_directories(${PROJECT_HEADER_SEARCH_PATHS})
link_directories(${PROJECT_LIBRARY_SEARCH_PATHS})

add_executable(${PROJECT_CONFIG_NAME} ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_LIBRARY_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_FRAMEWORK_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${CONAN_LIBS}")

set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES
    CXX_STANDARD "${PROJECT_CONFIG_CPP_STANDARD}"
    CXX_STANDARD_REQUIRED true
    CXX_EXTENSIONS false
    PUBLIC_HEADER "${PROJECT_HEADER_FILES}"  
)

target_compile_options(${PROJECT_CONFIG_NAME} PUBLIC "${PROJECT_COMPILE_OPTIONS}")
