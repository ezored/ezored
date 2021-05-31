# System
if(MSVC
   OR MSYS
   OR MINGW
)
    # for detecting Windows compilers
    set(PROJECT_SYSTEM_WINDOWS YES)
endif()

if(APPLE)
    # for MacOS X or iOS, watchOS, tvOS (since 3.10.3)
    set(PROJECT_SYSTEM_APPLE YES)
endif()

if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    set(PROJECT_SYSTEM_LINUX YES)
endif()

# Header files
set(PROJECT_HEADER_FILES
    ""
    CACHE INTERNAL ""
)

# Source files
set(PROJECT_SOURCE_FILES
    ""
    CACHE INTERNAL ""
)

# Header search paths
set(PROJECT_HEADER_SEARCH_PATHS
    ""
    CACHE INTERNAL ""
)

# Source files merged
set(PROJECT_SOURCE_FILES_MERGED
    ""
    CACHE INTERNAL ""
)

# Library search paths
set(PROJECT_LIBRARY_SEARCH_PATHS
    ""
    CACHE INTERNAL ""
)

# Framework links
set(PROJECT_FRAMEWORK_LINKS
    ""
    CACHE INTERNAL ""
)

# Library links
set(PROJECT_LIBRARY_LINKS
    ""
    CACHE INTERNAL ""
)

# C flags
set(PROJECT_CMAKE_C_FLAGS
    "${PROJECT_CMAKE_C_FLAGS} -Wall"
    CACHE INTERNAL ""
)

# CXX flags
set(PROJECT_CMAKE_CXX_FLAGS
    "${PROJECT_CMAKE_CXX_FLAGS} -std=c++${PROJECT_CONFIG_CXX_STANDARD} -Wall"
    CACHE INTERNAL ""
)

# Compile options
set(PROJECT_COMPILE_OPTIONS
    ""
    CACHE INTERNAL ""
)

# Functions
include(${PROJECT_ROOT_PATH}/files/common/cmake/functions.cmake)

# Modules
set(PROJECT_MODULES_PATH
    "${PROJECT_ROOT_PATH}/files/modules"
    CACHE INTERNAL ""
)

project_add_modules()

# Source files merged
list(APPEND PROJECT_SOURCE_FILES_MERGED ${PROJECT_SOURCE_FILES})
list(APPEND PROJECT_SOURCE_FILES_MERGED ${PROJECT_HEADER_FILES})
