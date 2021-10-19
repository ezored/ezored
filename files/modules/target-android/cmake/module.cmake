if(PROJECT_TARGET_NAME STREQUAL "android")
    # module files
    file(GLOB H_FILES_CXX "${PROJECT_MODULES_PATH}/support-lib/djinni/jni/main-ext/*.hpp")
    file(GLOB S_FILES_CXX "${PROJECT_MODULES_PATH}/support-lib/djinni/jni/main-ext/*.cpp")

    file(GLOB H_FILES_SUPPORT "${PROJECT_MODULES_PATH}/support-lib/djinni/*.hpp")
    file(GLOB S_FILES_SUPPORT "${PROJECT_MODULES_PATH}/support-lib/djinni/*.cpp")

    file(GLOB H_FILES_SUPPORT_PLATFORM "${PROJECT_MODULES_PATH}/support-lib/djinni/jni/*.hpp")
    file(GLOB S_FILES_SUPPORT_PLATFORM "${PROJECT_MODULES_PATH}/support-lib/djinni/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_DOMAIN "${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_DOMAIN "${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_ENUMS "${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_ENUMS "${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_CORE "${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_CORE "${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_DATA_SERVICES "${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_DATA_SERVICES "${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_SYSTEM_SERVICES "${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_SYSTEM_SERVICES "${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_APP_HELPERS "${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_APP_HELPERS "${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_LOGGER "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_LOGGER "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_HTTP_CLIENT "${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_HTTP_CLIENT "${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_HTTP_SERVER "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_HTTP_SERVER "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_FILE_HELPER "${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_FILE_HELPER "${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_SHARED_DATA "${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_SHARED_DATA "${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/jni/*.cpp")

    file(GLOB_RECURSE H_FILES_DATETIME "${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/jni/*.hpp")
    file(GLOB_RECURSE S_FILES_DATETIME "${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/jni/*.cpp")

    if(PROJECT_USE_CXX_HTTP_CLIENT)
        file(GLOB H_FILES_HTTP_CLIENT_CXX "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.hpp")
        file(GLOB S_FILES_HTTP_CLIENT_CXX "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.cpp")
    endif()

    # header files
    project_add_header_files("${H_FILES_CXX}")

    project_add_header_files("${H_FILES_SUPPORT}")
    project_add_header_files("${H_FILES_SUPPORT_PLATFORM}")

    project_add_header_files("${H_FILES_APP_DOMAIN}")
    project_add_header_files("${H_FILES_APP_ENUMS}")
    project_add_header_files("${H_FILES_APP_CORE}")
    project_add_header_files("${H_FILES_APP_DATA_SERVICES}")
    project_add_header_files("${H_FILES_APP_SYSTEM_SERVICES}")
    project_add_header_files("${H_FILES_APP_HELPERS}")

    project_add_header_files("${H_FILES_LOGGER}")
    project_add_header_files("${H_FILES_HTTP_CLIENT}")
    project_add_header_files("${H_FILES_HTTP_SERVER}")
    project_add_header_files("${H_FILES_FILE_HELPER}")
    project_add_header_files("${H_FILES_SHARED_DATA}")
    project_add_header_files("${H_FILES_DATETIME}")

    # source files
    project_add_source_files("${S_FILES_CXX}")

    project_add_source_files("${S_FILES_SUPPORT}")
    project_add_source_files("${S_FILES_SUPPORT_PLATFORM}")

    project_add_source_files("${S_FILES_APP_DOMAIN}")
    project_add_source_files("${S_FILES_APP_ENUMS}")
    project_add_source_files("${S_FILES_APP_CORE}")
    project_add_source_files("${S_FILES_APP_DATA_SERVICES}")
    project_add_source_files("${S_FILES_APP_SYSTEM_SERVICES}")
    project_add_source_files("${S_FILES_APP_HELPERS}")

    project_add_source_files("${S_FILES_LOGGER}")
    project_add_source_files("${S_FILES_HTTP_CLIENT}")
    project_add_source_files("${S_FILES_HTTP_SERVER}")
    project_add_source_files("${S_FILES_FILE_HELPER}")
    project_add_source_files("${S_FILES_SHARED_DATA}")
    project_add_source_files("${S_FILES_DATETIME}")

    # search paths
    project_add_search_path("${PROJECT_MODULES_PATH}/support-lib")

    project_add_search_path("${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/jni")

    project_add_search_path("${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/jni")
    project_add_search_path("${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/jni")
endif()
