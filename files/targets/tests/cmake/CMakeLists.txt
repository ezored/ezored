# Configurations
cmake_minimum_required(VERSION 3.20.0)
get_filename_component(CMAKE_SOURCE_REALPATH "${CMAKE_SOURCE_DIR}/../../../../" REALPATH)

set(PROJECT_CONFIG_NAME
    "ezored"
    CACHE STRING "Project Name"
)

set(PROJECT_CONFIG_CXX_STANDARD
    "17"
    CACHE STRING "Cpp Standard"
)

set(PROJECT_TARGET_NAME
    "tests"
    CACHE STRING "Target Name"
)

set(PROJECT_CONFIG_VERSION
    "1.0.0"
    CACHE STRING "Version"
)

set(PROJECT_CONFIG_ARCH
    "x86_64"
    CACHE STRING "Architecture"
)

set(PROJECT_ROOT_PATH ${CMAKE_SOURCE_REALPATH})

set(PROJECT_BUILD_PATH
    ${PROJECT_ROOT_PATH}/build/${PROJECT_TARGET_NAME}/${CMAKE_BUILD_TYPE}/${PROJECT_CONFIG_ARCH}
    CACHE INTERNAL ""
)

# Platform configurations (APPLE)
if(PROJECT_SYSTEM_APPLE EQUAL YES)
    set(CMAKE_OSX_ARCHITECTURES "${PROJECT_CONFIG_ARCH}")

    set(DEVELOPMENT_TEAM_ID
        ""
        CACHE STRING "Development Team ID"
    )

    set(CODE_SIGN_IDENTITY
        ""
        CACHE STRING "Sign Identity"
    )
endif()

# Project
project(${PROJECT_CONFIG_NAME})

# Conan
include(${PROJECT_BUILD_PATH}/conan/conanbuildinfo.cmake)
conan_basic_setup()

# Common
include(${PROJECT_ROOT_PATH}/files/common/cmake/common.cmake)

# Test specific configuration by platform
if(${PROJECT_SYSTEM_WINDOWS})
    include(platforms/windows.cmake)
endif()

if(${PROJECT_SYSTEM_APPLE})
    include(platforms/apple.cmake)
endif()

if(${PROJECT_SYSTEM_LINUX})
    include(platforms/linux.cmake)
endif()
