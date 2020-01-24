# Configurations
cmake_minimum_required(VERSION 3.1)
get_filename_component(CMAKE_SOURCE_REALPATH "${CMAKE_SOURCE_DIR}/../../../../" REALPATH)

set(PROJECT_CONFIG_NAME "Ezored" CACHE STRING "Project name")
set(PROJECT_CONFIG_VERSION "1.0.0" CACHE STRING "")
set(PROJECT_CONFIG_CPP_STANDARD "11" CACHE STRING "11")
set(PROJECT_TARGET_NAME "ios_framework" CACHE STRING "Target name")
set(PROJECT_CONFIG_ARCH "" CACHE STRING "Architecture")
set(PROJECT_ROOT_PATH ${CMAKE_SOURCE_REALPATH})
set(PROJECT_BUILD_DIR ${PROJECT_ROOT_PATH}/build/${PROJECT_TARGET_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_CONFIG_GROUP}/${PROJECT_CONFIG_ARCH} CACHE INTERNAL "")

# Platform configurations
set(CMAKE_MACOSX_BUNDLE YES)
set(CMAKE_OSX_ARCHITECTURES "${PROJECT_CONFIG_ARCH}")

set(DEVELOPMENT_TEAM_ID "" CACHE STRING "Development Team ID")
set(CODE_SIGN_IDENTITY "" CACHE STRING "Sign Identity")
set(FRAMEWORK_NAME "${PROJECT_CONFIG_NAME}" CACHE STRING "Framework Name")
set(FRAMEWORK_BUNDLE_IDENTIFIER "com.ezored.library" CACHE STRING "Bundle Identifier")
set(DEVICE_FAMILY "1,2" CACHE STRING "Device Family")

# Suppress macOS X RPATH warnings and adopt new related behaviors
if(NOT CMAKE_VERSION VERSION_LESS 3.9)
    cmake_policy(SET CMP0068 NEW)
endif()

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
    "${PROJECT_ROOT_PATH}/files/djinni/support-lib/objc"

    "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/objc"

    "${PROJECT_ROOT_PATH}/files/djinni/core/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/objc"
    "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/objc"

    "${PROJECT_ROOT_PATH}/files/src/logger/objc"
    "${PROJECT_ROOT_PATH}/files/src/file-helper/objc"
    "${PROJECT_ROOT_PATH}/files/src/shared-data/objc"
    "${PROJECT_ROOT_PATH}/files/src/datetime/objc"

    CACHE INTERNAL ""
)

# Header files
file(GLOB H_FILES_SUPPORT_LIB_CPP "${PROJECT_ROOT_PATH}/files/djinni/support-lib/*.hpp")
file(GLOB H_FILES_SUPPORT_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/support-lib/objc/*.h")

file(GLOB_RECURSE H_FILES_APP_DOMAIN_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/objc/*.h")
file(GLOB_RECURSE H_FILES_APP_ENUMS_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/objc/*.h")
file(GLOB_RECURSE H_FILES_APP_CORE_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/objc/*.h")
file(GLOB_RECURSE H_FILES_APP_DATA_SERVICES_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/objc/*.h")
file(GLOB_RECURSE H_FILES_APP_SYSTEM_SERVICES_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/objc/*.h")
file(GLOB_RECURSE H_FILES_APP_HELPERS_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/objc/*.h")

file(GLOB_RECURSE H_FILES_LOGGER_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/objc/*.h")
file(GLOB H_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/objc/ezored/util/*.h")

file(GLOB_RECURSE H_FILES_HTTP_CLIENT_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/objc/*.h")
file(GLOB H_FILES_HTTP_CLIENT_LIB_IMPL_OBJC "${PROJECT_ROOT_PATH}/files/src/http-client/objc/ezored/net/http/*.h")

# uncomment only if you want use C++ http client instead of native android http client
#file(GLOB H_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.hpp")

file(GLOB_RECURSE H_FILES_FILE_HELPER_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/objc/*.h")
file(GLOB H_FILES_FILE_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/file-helper/objc/ezored/io/*.h")

file(GLOB_RECURSE H_FILES_SHARED_DATA_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/objc/*.h")
file(GLOB H_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/objc/ezored/data/*.h")

file(GLOB_RECURSE H_FILES_DATETIME_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/objc/*.h")

# Source files
file(GLOB S_FILES_SUPPORT_LIB_CPP "${PROJECT_ROOT_PATH}/files/djinni/support-lib/*.cpp")
file(GLOB S_FILES_SUPPORT_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/support-lib/objc/*.mm")

file(GLOB_RECURSE S_FILES_APP_DOMAIN_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-domain/generated-src/objc/*.mm")
file(GLOB_RECURSE S_FILES_APP_ENUMS_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-enums/generated-src/objc/*.mm")
file(GLOB_RECURSE S_FILES_APP_CORE_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-core/generated-src/objc/*.mm")
file(GLOB_RECURSE S_FILES_APP_DATA_SERVICES_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-data-services/generated-src/objc/*.mm")
file(GLOB_RECURSE S_FILES_APP_SYSTEM_SERVICES_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-system-services/generated-src/objc/*.mm")
file(GLOB_RECURSE S_FILES_APP_HELPERS_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/app-helpers/generated-src/objc/*.mm")

file(GLOB_RECURSE S_FILES_LOGGER_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/objc/*.mm")
file(GLOB S_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/objc/ezored/util/*.m")

file(GLOB_RECURSE S_FILES_HTTP_CLIENT_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/http-client/generated-src/objc/*.mm")
file(GLOB S_FILES_HTTP_CLIENT_LIB_IMPL_OBJC "${PROJECT_ROOT_PATH}/files/src/http-client/objc/ezored/net/http/*.m")

# uncomment only if you want use C++ http client instead of native android http client
#file(GLOB S_FILES_HTTP_CLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/http-client/cpp/ezored/net/http/Simple*.cpp")

file(GLOB_RECURSE S_FILES_FILE_HELPER_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/objc/*.mm")
file(GLOB S_FILES_FILE_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/file-helper/objc/ezored/io/*.m")

file(GLOB_RECURSE S_FILES_SHARED_DATA_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/objc/*.mm")
file(GLOB S_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/objc/ezored/data/*.m")

file(GLOB_RECURSE S_FILES_DATETIME_LIB_OBJC "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/objc/*.mm")

# Merge lists
set(
    TARGET_HEADER_FILES 
    ${H_FILES_SUPPORT_LIB_CPP}
    ${H_FILES_SUPPORT_LIB_OBJC}
    ${H_FILES_APP_DOMAIN_LIB_OBJC}
    ${H_FILES_APP_ENUMS_LIB_OBJC}
    ${H_FILES_APP_CORE_LIB_OBJC}
    ${H_FILES_APP_DATA_SERVICES_LIB_OBJC}
    ${H_FILES_APP_SYSTEM_SERVICES_LIB_OBJC}
    ${H_FILES_APP_HELPERS_LIB_OBJC}
    ${H_FILES_LOGGER_LIB_OBJC}
    ${H_FILES_LOGGER_LIB_IMPL}
    ${H_FILES_HTTP_CLIENT_LIB_OBJC}
    ${H_FILES_HTTP_CLIENT_LIB_IMPL_OBJC}
    ${H_FILES_HTTP_CLIENT_LIB_IMPL}
    ${H_FILES_FILE_HELPER_LIB_OBJC}
    ${H_FILES_FILE_HELPER_LIB_IMPL}
    ${H_FILES_SHARED_DATA_LIB_OBJC}
    ${H_FILES_SHARED_DATA_LIB_IMPL}
    ${H_FILES_DATETIME_LIB_OBJC}
)

set(
    TARGET_SOURCE_FILES 
    ${S_FILES_SUPPORT_LIB_CPP}
    ${S_FILES_SUPPORT_LIB_OBJC}
    ${S_FILES_APP_DOMAIN_LIB_OBJC}
    ${S_FILES_APP_ENUMS_LIB_OBJC}
    ${S_FILES_APP_CORE_LIB_OBJC}
    ${S_FILES_APP_DATA_SERVICES_LIB_OBJC}
    ${S_FILES_APP_SYSTEM_SERVICES_LIB_OBJC}
    ${S_FILES_APP_HELPERS_LIB_OBJC}
    ${S_FILES_LOGGER_LIB_OBJC}
    ${S_FILES_LOGGER_LIB_IMPL}
    ${S_FILES_HTTP_CLIENT_LIB_OBJC}
    ${S_FILES_HTTP_CLIENT_LIB_IMPL_OBJC}
    ${S_FILES_HTTP_CLIENT_LIB_IMPL}
    ${S_FILES_FILE_HELPER_LIB_OBJC}
    ${S_FILES_FILE_HELPER_LIB_IMPL}
    ${S_FILES_SHARED_DATA_LIB_OBJC}
    ${S_FILES_SHARED_DATA_LIB_IMPL}
    ${S_FILES_DATETIME_LIB_OBJC}
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

# Framework links
set(PROJECT_FRAMEWORK_LINKS
    ${PROJECT_FRAMEWORK_LINKS}
	"-framework Foundation"
	CACHE INTERNAL ""
)

# C flags
set(PROJECT_CMAKE_C_FLAGS "${PROJECT_CMAKE_C_FLAGS} -fobjc-arc -fobjc-abi-version=2" CACHE INTERNAL "")

# CXX flags
set(PROJECT_CMAKE_CXX_FLAGS "${PROJECT_CMAKE_CXX_FLAGS} -fobjc-arc -fvisibility-inlines-hidden -fobjc-abi-version=2 -stdlib=libc++" CACHE INTERNAL "")

# Flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${PROJECT_CMAKE_C_FLAGS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${PROJECT_CMAKE_CXX_FLAGS}" CACHE INTERNAL "")

# Hidden visibilty is required for C++ on iOS.
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g ${CMAKE_CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_MINSIZEREL "${CMAKE_CXX_FLAGS} -DNDEBUG -Os -ffast-math ${CMAKE_CXX_FLAGS_MINSIZEREL}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS} -DNDEBUG -O2 -g -ffast-math ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -DNDEBUG -O3 -ffast-math ${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_C_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_C_LINK_FLAGS}")
set(CMAKE_CXX_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_CXX_LINK_FLAGS}")

# Project
include_directories(${PROJECT_HEADER_SEARCH_PATHS})
link_directories(${PROJECT_LIBRARY_SEARCH_PATHS})

add_library(${PROJECT_CONFIG_NAME} SHARED ${PROJECT_SOURCE_FILES})

target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_LIBRARY_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${PROJECT_FRAMEWORK_LINKS}")
target_link_libraries(${PROJECT_CONFIG_NAME} "${CONAN_LIBS}")

set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES
    CXX_STANDARD "${PROJECT_CONFIG_CPP_STANDARD}"
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_VISIBILITY_PRESET default
    FRAMEWORK TRUE
    FRAMEWORK_VERSION A
    MACOSX_FRAMEWORK_IDENTIFIER "${FRAMEWORK_BUNDLE_IDENTIFIER}"
    MACOSX_FRAMEWORK_BUNDLE_VERSION "${PROJECT_CONFIG_VERSION}"
    MACOSX_FRAMEWORK_SHORT_VERSION_STRING "${PROJECT_CONFIG_VERSION}"
    XCODE_ATTRIBUTE_IPHONEOS_DEPLOYMENT_TARGET "${CMAKE_OSX_DEPLOYMENT_TARGET}"
    XCODE_ATTRIBUTE_CODE_SIGN_IDENTITY "${CODE_SIGN_IDENTITY}"
    XCODE_ATTRIBUTE_CODE_SIGNING_REQUIRED NO
    XCODE_ATTRIBUTE_DEVELOPMENT_TEAM "${DEVELOPMENT_TEAM_ID}"
    XCODE_ATTRIBUTE_TARGETED_DEVICE_FAMILY "${DEVICE_FAMILY}"
    XCODE_ATTRIBUTE_ONLY_ACTIVE_ARCH YES
    XCODE_ATTRIBUTE_SKIP_INSTALL YES
    XCODE_ATTRIBUTE_INSTALL_PATH "@loader_path/Frameworks"

    # Is "current version" in semantic format in Mach-O binary file
    VERSION "${PROJECT_CONFIG_VERSION}"
    # Is "compatibility version" in semantic format in Mach-O binary file
    SOVERSION "${PROJECT_CONFIG_VERSION}"
)

# Adapt install directory to allow distributing dylibs/frameworks in user's frameworks/application bundle
set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES INSTALL_NAME_DIR "@rpath")

if(NOT CMAKE_SKIP_BUILD_RPATH)
    if(CMAKE_VERSION VERSION_LESS 3.9)
        set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE)
    else()
        set_target_properties(${PROJECT_CONFIG_NAME} PROPERTIES BUILD_WITH_INSTALL_NAME_DIR TRUE)
    endif()
endif()

target_compile_options(${PROJECT_CONFIG_NAME} PUBLIC "${PROJECT_COMPILE_OPTIONS}")
