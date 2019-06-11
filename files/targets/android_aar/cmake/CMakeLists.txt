# Configurations
cmake_minimum_required(VERSION 3.14)
get_filename_component(CMAKE_SOURCE_REALPATH "${CMAKE_SOURCE_DIR}/../../../../" REALPATH)

set(PROJECT_CONFIG_NAME "Ezored" CACHE STRING "Project name")
set(PROJECT_CONFIG_CPP_STANDARD "11" CACHE STRING "11")
set(PROJECT_TARGET_NAME "android_aar" CACHE STRING "Target name")
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

# Header search paths
set(PROJECT_HEADER_SEARCH_PATHS
    ${PROJECT_HEADER_SEARCH_PATHS}
    "${PROJECT_ROOT_PATH}/files/djinni/support-lib"
    "${PROJECT_ROOT_PATH}/files/djinni/support-lib/jni"

    "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/jni"

    "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/jni"
    "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/jni"

    CACHE INTERNAL ""
)

# Header files
file(GLOB H_FILES_SUPPORT_LIB_CPP "${PROJECT_ROOT_PATH}/files/djinni/support-lib/*.hpp")
file(GLOB H_FILES_SUPPORT_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/support-lib/jni/*.hpp")

file(GLOB_RECURSE H_FILES_APP_DOMAIN_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_APP_ENUMS_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_APP_CORE_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_APP_DATA_SERVICES_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_APP_SYSTEM_SERVICES_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_APP_HELPERS_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/jni/*.h")

file(GLOB_RECURSE H_FILES_LOGGER_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_HTTP_CLIENT_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_FILE_HELPER_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_SHARED_DATA_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/jni/*.h")
file(GLOB_RECURSE H_FILES_DATETIME_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/jni/*.h")

file(GLOB H_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.hpp")

# Source files
file(GLOB S_FILES_SUPPORT_LIB_CPP "${PROJECT_ROOT_PATH}/files/djinni/support-lib/*.cpp")
file(GLOB S_FILES_SUPPORT_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/support-lib/jni/*.cpp")
file(GLOB S_FILES_SUPPORT_MAIN_LIB_CPP "${PROJECT_ROOT_PATH}/files/djinni/support-lib/jni/main-ext/*.cpp")

file(GLOB_RECURSE S_FILES_APP_DOMAIN_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_APP_ENUMS_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_APP_CORE_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_APP_DATA_SERVICES_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_APP_SYSTEM_SERVICES_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_APP_HELPERS_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/jni/*.cpp")

file(GLOB_RECURSE S_FILES_LOGGER_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_HTTP_CLIENT_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_FILE_HELPER_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_SHARED_DATA_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/jni/*.cpp")
file(GLOB_RECURSE S_FILES_DATETIME_LIB_JNI "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/jni/*.cpp")

file(GLOB S_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.cpp")

# Merge lists
set(
    TARGET_HEADER_FILES 
    ${H_FILES_SUPPORT_LIB_CPP}
    ${H_FILES_SUPPORT_LIB_JNI}
    ${H_FILES_APP_DOMAIN_LIB_JNI}
    ${H_FILES_APP_ENUMS_LIB_JNI}
    ${H_FILES_APP_CORE_LIB_JNI}
    ${H_FILES_APP_DATA_SERVICES_LIB_JNI}
    ${H_FILES_APP_SYSTEM_SERVICES_LIB_JNI}
    ${H_FILES_APP_HELPERS_LIB_JNI}
    ${H_FILES_LOGGER_LIB_JNI}
    ${H_FILES_HTTP_CLIENT_LIB_JNI}
    ${H_FILES_FILE_HELPER_LIB_JNI}
    ${H_FILES_SHARED_DATA_LIB_JNI}
    ${H_FILES_DATETIME_LIB_JNI}
    ${H_FILES_HTTP_CLIENT_LIB_IMPL}
)

set(
    TARGET_SOURCE_FILES 
    ${S_FILES_SUPPORT_LIB_CPP}
    ${S_FILES_SUPPORT_MAIN_LIB_CPP}
    ${S_FILES_SUPPORT_LIB_JNI}
    ${S_FILES_APP_DOMAIN_LIB_JNI}
    ${S_FILES_APP_ENUMS_LIB_JNI}
    ${S_FILES_APP_CORE_LIB_JNI}
    ${S_FILES_APP_DATA_SERVICES_LIB_JNI}
    ${S_FILES_APP_SYSTEM_SERVICES_LIB_JNI}
    ${S_FILES_APP_HELPERS_LIB_JNI}
    ${S_FILES_LOGGER_LIB_JNI}
    ${S_FILES_HTTP_CLIENT_LIB_JNI}
    ${S_FILES_FILE_HELPER_LIB_JNI}
    ${S_FILES_SHARED_DATA_LIB_JNI}
    ${S_FILES_DATETIME_LIB_JNI}
    ${S_FILES_HTTP_CLIENT_LIB_IMPL}
)

set(
    PROJECT_HEADER_FILES
    ${PROJECT_HEADER_FILES}
    ${TARGET_HEADER_FILES}
    CACHE INTERNAL ""
)

set(
    PROJECT_SOURCE_FILES
    ${PROJECT_SOURCE_FILES}
    ${TARGET_HEADER_FILES}
    ${TARGET_SOURCE_FILES}
    CACHE INTERNAL ""
)

# CXX flags
set(PROJECT_CMAKE_CXX_FLAGS "${PROJECT_CMAKE_CXX_FLAGS} -stdlib=libc++" CACHE INTERNAL "")

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PROJECT_CMAKE_C_FLAGS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_CMAKE_CXX_FLAGS}" CACHE INTERNAL "")

# Project
include_directories(${PROJECT_HEADER_SEARCH_PATHS})
link_directories(${PROJECT_LIBRARY_SEARCH_PATHS})

add_library(${PROJECT_CONFIG_NAME} SHARED ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_LIBRARY_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_FRAMEWORK_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${CONAN_LIBS}")

set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES
    CXX_STANDARD "${PROJECT_CONFIG_CPP_STANDARD}"
    CXX_STANDARD_REQUIRED true
    CXX_EXTENSIONS false
    CXX_VISIBILITY_PRESET default
    VERSION "${PROJECT_CONFIG_VERSION}"
    SOVERSION "${PROJECT_CONFIG_VERSION}"
    PUBLIC_HEADER "${PROJECT_HEADER_FILES}"    
)

target_compile_options(${PROJECT_CONFIG_NAME} PUBLIC "${PROJECT_COMPILE_OPTIONS}")
