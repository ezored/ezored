# Header search paths
set(PROJECT_HEADER_SEARCH_PATHS
    "${PROJECT_ROOT_PATH}/files/djinni/001-app-domain/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/002-app-core/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/003-app-data-services/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/004-app-system-service/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/005-app-helpers/generated-src/cpp"

    "${PROJECT_ROOT_PATH}/files/djinni/httpclient/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/string-helper/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/cpp"
    "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/cpp"

    "${PROJECT_ROOT_PATH}/files/src/001-app-domain/cpp"
    "${PROJECT_ROOT_PATH}/files/src/002-app-core/cpp"
    "${PROJECT_ROOT_PATH}/files/src/003-app-data-services/cpp"
    "${PROJECT_ROOT_PATH}/files/src/004-app-system-service/cpp"
    "${PROJECT_ROOT_PATH}/files/src/005-app-helpers/cpp"

    "${PROJECT_ROOT_PATH}/files/src/httpclient/cpp"
    "${PROJECT_ROOT_PATH}/files/src/logger/cpp"
    "${PROJECT_ROOT_PATH}/files/src/datetime/cpp"
    "${PROJECT_ROOT_PATH}/files/src/datetime/cpp/ezored/time/date/include"
    "${PROJECT_ROOT_PATH}/files/src/string-helper/cpp"
    "${PROJECT_ROOT_PATH}/files/src/file-helper/cpp"
    "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp"

    CACHE INTERNAL ""
)

# Library search paths
set(PROJECT_LIBRARY_SEARCH_PATHS "" CACHE INTERNAL "")

# Header files
file(GLOB H_FILES_APP_DOMAIN_LIB "${PROJECT_ROOT_PATH}/files/djinni/001-app-domain/generated-src/cpp/ezored/domain/*.hpp")
file(GLOB H_FILES_APP_DOMAIN_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/001-app-domain/cpp/ezored/domain/*.hpp")

file(GLOB H_FILES_APP_CORE_LIB "${PROJECT_ROOT_PATH}/files/djinni/002-app-core/generated-src/cpp/ezored/core/*.hpp")
file(GLOB H_FILES_APP_CORE_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/002-app-core/cpp/ezored/core/*.hpp")

file(GLOB H_FILES_APP_DATA_SERVICES_LIB "${PROJECT_ROOT_PATH}/files/djinni/003-app-data-services/generated-src/cpp/ezored/dataservices/*.hpp")
file(GLOB H_FILES_APP_DATA_SERVICES_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/003-app-data-services/cpp/ezored/dataservices/*.hpp")

file(GLOB H_FILES_APP_SYSTEM_SERVICES_LIB "${PROJECT_ROOT_PATH}/files/djinni/004-app-system-service/generated-src/cpp/ezored/systemservices/*.hpp")
file(GLOB H_FILES_APP_SYSTEM_SERVICES_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/004-app-system-service/cpp/ezored/systemservices/*.hpp")

file(GLOB H_FILES_APP_HELPERS_LIB "${PROJECT_ROOT_PATH}/files/djinni/005-app-helpers/generated-src/cpp/ezored/helpers/*.hpp")
file(GLOB H_FILES_APP_HELPERS_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/005-app-helpers/cpp/ezored/helpers/*.hpp")

file(GLOB H_FILES_HTTPCLIENT_LIB "${PROJECT_ROOT_PATH}/files/djinni/httpclient/generated-src/cpp/ezored/net/http/HttpClient*.hpp")
file(GLOB H_FILES_HTTPCLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/httpclient/cpp/ezored/net/http/HttpClient*.hpp")

file(GLOB H_FILES_LOGGER_LIB "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/cpp/ezored/util/Logger*.hpp")
file(GLOB H_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Logger*.hpp")

file(GLOB H_FILES_DATETIME_LIB "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/cpp/ezored/time/DateTime*.hpp")
file(GLOB H_FILES_DATETIME_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/datetime/cpp/ezored/time/DateTime*.hpp")

file(GLOB H_FILES_STRING_HELPER_LIB "${PROJECT_ROOT_PATH}/files/djinni/string-helper/generated-src/cpp/ezored/helpers/StringHelper*.hpp")
file(GLOB H_FILES_STRING_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/string-helper/cpp/ezored/helpers/StringHelper*.hpp")

file(GLOB H_FILES_FILE_HELPER_LIB "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/cpp/ezored/io/FileHelper*.hpp")
file(GLOB H_FILES_FILE_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/file-helper/cpp/ezored/io/FileHelper*.hpp")

file(GLOB H_FILES_SHARED_DATA_LIB "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/cpp/ezored/data/SharedData*.hpp")
file(GLOB H_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/SharedData*.hpp")

# Source files
file(GLOB S_FILES_APP_DOMAIN_LIB "${PROJECT_ROOT_PATH}/files/djinni/001-app-domain/generated-src/cpp/ezored/domain/*.cpp")
file(GLOB S_FILES_APP_DOMAIN_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/001-app-domain/cpp/ezored/domain/*.cpp")

file(GLOB S_FILES_APP_CORE_LIB "${PROJECT_ROOT_PATH}/files/djinni/002-app-core/generated-src/cpp/ezored/core/*.cpp")
file(GLOB S_FILES_APP_CORE_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/002-app-core/cpp/ezored/core/*.cpp")

file(GLOB S_FILES_APP_DATA_SERVICES_LIB "${PROJECT_ROOT_PATH}/files/djinni/003-app-data-services/generated-src/cpp/ezored/dataservices/*.cpp")
file(GLOB S_FILES_APP_DATA_SERVICES_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/003-app-data-services/cpp/ezored/dataservices/*.cpp")

file(GLOB S_FILES_APP_SYSTEM_SERVICES_LIB "${PROJECT_ROOT_PATH}/files/djinni/004-app-system-service/generated-src/cpp/ezored/systemservices/*.cpp")
file(GLOB S_FILES_APP_SYSTEM_SERVICES_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/004-app-system-service/cpp/ezored/systemservices/*.cpp")

file(GLOB S_FILES_APP_HELPERS_LIB "${PROJECT_ROOT_PATH}/files/djinni/005-app-helpers/generated-src/cpp/ezored/helpers/*.cpp")
file(GLOB S_FILES_APP_HELPERS_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/005-app-helpers/cpp/ezored/helpers/*.cpp")

file(GLOB S_FILES_HTTPCLIENT_LIB "${PROJECT_ROOT_PATH}/files/djinni/httpclient/generated-src/cpp/ezored/net/http/HttpClient*.cpp")
file(GLOB S_FILES_HTTPCLIENT_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/httpclient/cpp/ezored/net/http/HttpClient*.cpp")

file(GLOB S_FILES_LOGGER_LIB "${PROJECT_ROOT_PATH}/files/djinni/logger/generated-src/cpp/ezored/util/Logger*.cpp")
file(GLOB S_FILES_LOGGER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/logger/cpp/ezored/util/Logger*.cpp")

file(GLOB S_FILES_DATETIME_LIB "${PROJECT_ROOT_PATH}/files/djinni/datetime/generated-src/cpp/ezored/time/DateTime*.cpp")
file(GLOB S_FILES_DATETIME_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/datetime/cpp/ezored/time/DateTime*.cpp")

file(GLOB S_FILES_STRING_HELPER_LIB "${PROJECT_ROOT_PATH}/files/djinni/string-helper/generated-src/cpp/ezored/helpers/StringHelper*.cpp")
file(GLOB S_FILES_STRING_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/string-helper/cpp/ezored/helpers/StringHelper*.cpp")

file(GLOB S_FILES_FILE_HELPER_LIB "${PROJECT_ROOT_PATH}/files/djinni/file-helper/generated-src/cpp/ezored/io/FileHelper*.cpp")
file(GLOB S_FILES_FILE_HELPER_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/file-helper/cpp/ezored/io/FileHelper*.cpp")

file(GLOB S_FILES_SHARED_DATA_LIB "${PROJECT_ROOT_PATH}/files/djinni/shared-data/generated-src/cpp/ezored/data/SharedData*.cpp")
file(GLOB S_FILES_SHARED_DATA_LIB_IMPL "${PROJECT_ROOT_PATH}/files/src/shared-data/cpp/ezored/data/SharedData*.cpp")

# Merge lists
set(
    PROJECT_HEADER_FILES 
    ${H_FILES_APP_DOMAIN_LIB}
    ${H_FILES_APP_DOMAIN_LIB_IMPL}
    ${H_FILES_APP_CORE_LIB}
    ${H_FILES_APP_CORE_LIB_IMPL}
    ${H_FILES_APP_DATA_SERVICES_LIB}
    ${H_FILES_APP_DATA_SERVICES_LIB_IMPL}
    ${H_FILES_APP_SYSTEM_SERVICES_LIB}
    ${H_FILES_APP_SYSTEM_SERVICES_LIB_IMPL}
    ${H_FILES_APP_HELPERS_LIB}
    ${H_FILES_APP_HELPERS_LIB_IMPL}
    ${H_FILES_HTTPCLIENT_LIB}
    ${H_FILES_HTTPCLIENT_LIB_IMPL}
    ${H_FILES_LOGGER_LIB}
    ${H_FILES_LOGGER_LIB_IMPL}
    ${H_FILES_DATETIME_LIB}
    ${H_FILES_DATETIME_LIB_IMPL}
    ${H_FILES_STRING_HELPER_LIB}
    ${H_FILES_STRING_HELPER_LIB_IMPL}
    ${H_FILES_FILE_HELPER_LIB}
    ${H_FILES_FILE_HELPER_LIB_IMPL}
    ${H_FILES_SHARED_DATA_LIB}
    ${H_FILES_SHARED_DATA_LIB_IMPL}
    CACHE INTERNAL ""
)

set(
    PROJECT_SOURCE_FILES 
    ${S_FILES_APP_DOMAIN_LIB}
    ${S_FILES_APP_DOMAIN_LIB_IMPL}
    ${S_FILES_APP_CORE_LIB}
    ${S_FILES_APP_CORE_LIB_IMPL}
    ${S_FILES_APP_DATA_SERVICES_LIB}
    ${S_FILES_APP_DATA_SERVICES_LIB_IMPL}
    ${S_FILES_APP_SYSTEM_SERVICES_LIB}
    ${S_FILES_APP_SYSTEM_SERVICES_LIB_IMPL}
    ${S_FILES_APP_HELPERS_LIB}
    ${S_FILES_APP_HELPERS_LIB_IMPL}
    ${S_FILES_HTTPCLIENT_LIB}
    ${S_FILES_HTTPCLIENT_LIB_IMPL}
    ${S_FILES_LOGGER_LIB}
    ${S_FILES_LOGGER_LIB_IMPL}
    ${S_FILES_DATETIME_LIB}
    ${S_FILES_DATETIME_LIB_IMPL}
    ${S_FILES_STRING_HELPER_LIB}
    ${S_FILES_STRING_HELPER_LIB_IMPL}
    ${S_FILES_FILE_HELPER_LIB}
    ${S_FILES_FILE_HELPER_LIB_IMPL}
    ${S_FILES_SHARED_DATA_LIB}
    ${S_FILES_SHARED_DATA_LIB_IMPL}
    CACHE INTERNAL ""
)

set(
    PROJECT_SOURCE_FILES
    ${PROJECT_HEADER_FILES}
    ${PROJECT_SOURCE_FILES} 
    CACHE INTERNAL ""
)

# Framework links
set(PROJECT_FRAMEWORK_LINKS "" CACHE INTERNAL "")

# Library links
set(PROJECT_LIBRARY_LINKS "" CACHE INTERNAL "")

# CFlags
set(PROJECT_CMAKE_C_FLAGS "${PROJECT_CMAKE_C_FLAGS} -Wall" CACHE INTERNAL "")

# CXXFlags
set(PROJECT_CMAKE_CXX_FLAGS "${PROJECT_CMAKE_CXX_FLAGS} -std=c++${PROJECT_CONFIG_CPP_STANDARD} -Wall" CACHE INTERNAL "")

# Compile options
set(PROJECT_COMPILE_OPTIONS "" CACHE INTERNAL "")

# Flags
set(CMAKE_C_FLAGS "${PROJECT_CMAKE_C_FLAGS}" CACHE INTERNAL "")
set(CMAKE_CXX_FLAGS "${PROJECT_CMAKE_CXX_FLAGS}" CACHE INTERNAL "")
