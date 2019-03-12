# Configurations
cmake_minimum_required(VERSION 2.8.12)
get_filename_component(CMAKE_SOURCE_REALPATH "${CMAKE_SOURCE_DIR}/../../../../" REALPATH)

set(PROJECT_CONFIG_NAME "Sample" CACHE STRING "Project name")
set(PROJECT_CONFIG_CPP_STANDARD "11" CACHE STRING "11")
set(PROJECT_TARGET_NAME "macos_app" CACHE STRING "Target name")
set(PROJECT_CONFIG_ARCH "" CACHE STRING "Architecture")
set(PROJECT_ROOT_PATH ${CMAKE_SOURCE_REALPATH})
set(PROJECT_BUILD_DIR ${PROJECT_ROOT_PATH}/build/${PROJECT_TARGET_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_CONFIG_ARCH} CACHE INTERNAL "")

# Platform configurations
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.9" CACHE STRING "Minimum macOS deployment version")
set(DEVELOPMENT_TEAM_ID "" CACHE STRING "Development team ID")
set(CODE_SIGN_IDENTITY "Mac Developer" CACHE STRING "Sign identity")

# Include: common
add_subdirectory(
    ${PROJECT_ROOT_PATH}/files/cmake/common
    ${PROJECT_BUILD_DIR}/common
)

# Project
project(${PROJECT_CONFIG_NAME})

# Source files
file(GLOB S_FILES_PROJECT "${PROJECT_ROOT_PATH}/projects/samples/simple/*.cpp")

file(GLOB H_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Simple*.hpp")
file(GLOB S_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Simple*.cpp")

file(GLOB H_FILES_HTTPCLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/httpclient/cpp/ezored/net/http/Simple*.hpp")
file(GLOB S_FILES_HTTPCLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/httpclient/cpp/ezored/net/http/Simple*.cpp")

file(GLOB H_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/Simple*.hpp")
file(GLOB S_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/Simple*.cpp")

# Merge lists
set(
    TARGET_HEADER_FILES     
    ${H_FILES_LOGGER_LIB_IMPL}
    ${H_FILES_HTTPCLIENT_LIB_IMPL}
    ${H_FILES_SHARED_DATA_LIB_IMPL}
)

set(
    TARGET_SOURCE_FILES     
    ${S_FILES_LOGGER_LIB_IMPL}
    ${S_FILES_HTTPCLIENT_LIB_IMPL}
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

# Framework links
set(PROJECT_FRAMEWORK_LINKS
    ${PROJECT_FRAMEWORK_LINKS}
	"-framework Foundation"
    CACHE INTERNAL ""
)

# Conan
include(${PROJECT_BUILD_DIR}/conan/conanbuildinfo.cmake)
conan_basic_setup()

# CXXFlags
set(PROJECT_CMAKE_CXX_FLAGS "${PROJECT_CMAKE_CXX_FLAGS} -stdlib=libc++" CACHE INTERNAL "")

# Project
include_directories(${PROJECT_HEADER_SEARCH_PATHS})
link_directories(${PROJECT_LIBRARY_SEARCH_PATHS})

add_executable(${PROJECT_CONFIG_NAME} ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_LIBRARY_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_FRAMEWORK_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${CONAN_LIBS}")

set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES
    CXX_STANDARD "${PROJECT_CONFIG_CPP_STANDARD}"
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    PUBLIC_HEADER "${PROJECT_HEADER_FILES}"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${CODE_SIGN_IDENTITY}"
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM_ID}"
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH NO
    XCODE_ATTRIBUTE_SKIP_INSTALL YES
)

target_compile_options(${PROJECT_CONFIG_NAME} PUBLIC "${PROJECT_COMPILE_OPTIONS}")
