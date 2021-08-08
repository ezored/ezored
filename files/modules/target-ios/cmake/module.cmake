if(PROJECT_TARGET_NAME STREQUAL "ios")
    # module files
    file(GLOB H_FILES_SUPPORT "${PROJECT_MODULES_PATH}/support-lib/djinni/*.hpp")
    file(GLOB S_FILES_SUPPORT "${PROJECT_MODULES_PATH}/support-lib/djinni/*.cpp")

    file(GLOB H_FILES_SUPPORT_PLATFORM "${PROJECT_MODULES_PATH}/support-lib/djinni/objc/*.h")
    file(GLOB S_FILES_SUPPORT_PLATFORM "${PROJECT_MODULES_PATH}/support-lib/djinni/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_DOMAIN "${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_DOMAIN "${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_ENUMS "${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_ENUMS "${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_CORE "${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_CORE "${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_DATA_SERVICES "${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_DATA_SERVICES "${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_SYSTEM_SERVICES "${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_SYSTEM_SERVICES "${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_APP_HELPERS "${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_APP_HELPERS "${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_LOGGER "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_LOGGER "${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_HTTP_CLIENT "${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_HTTP_CLIENT "${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_HTTP_SERVER "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_HTTP_SERVER "${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_FILE_HELPER "${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_FILE_HELPER "${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_SHARED_DATA "${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_SHARED_DATA "${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/objc/*.mm")

    file(GLOB_RECURSE H_FILES_DATETIME "${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/objc/*.h")
    file(GLOB_RECURSE S_FILES_DATETIME "${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/objc/*.mm")

    file(GLOB H_FILES_LOGGER_PLATFORM "${PROJECT_MODULES_PATH}/logger/implementation/objc/ezored/util/*.h")
    file(GLOB S_FILES_LOGGER_PLATFORM "${PROJECT_MODULES_PATH}/logger/implementation/objc/ezored/util/*.m")

    file(GLOB H_FILES_FILE_HELPER_PLATFORM "${PROJECT_MODULES_PATH}/file-helper/implementation/objc/ezored/io/*.h")
    file(GLOB S_FILES_FILE_HELPER_PLATFORM "${PROJECT_MODULES_PATH}/file-helper/implementation/objc/ezored/io/*.m")

    file(GLOB H_FILES_HTTP_CLIENT_PLATFORM "${PROJECT_MODULES_PATH}/http-client/implementation/objc/ezored/net/http/*.h")
    file(GLOB S_FILES_HTTP_CLIENT_PLATFORM "${PROJECT_MODULES_PATH}/http-client/implementation/objc/ezored/net/http/*.m")

    file(GLOB H_FILES_SHARED_DATA_PLATFORM "${PROJECT_MODULES_PATH}/shared-data/implementation/objc/ezored/data/*.h")
    file(GLOB S_FILES_SHARED_DATA_PLATFORM "${PROJECT_MODULES_PATH}/shared-data/implementation/objc/ezored/data/*.m")

    if(PROJECT_USE_CXX_HTTP_CLIENT)
        file(GLOB H_FILES_HTTP_CLIENT_CXX "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.hpp")
        file(GLOB S_FILES_HTTP_CLIENT_CXX "${PROJECT_MODULES_PATH}/http-client/implementation/cpp/ezored/net/http/Simple*.cpp")
    endif()

    # header files
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

    project_add_header_files("${H_FILES_LOGGER_PLATFORM}")
    project_add_header_files("${H_FILES_HTTP_CLIENT_PLATFORM}")
    project_add_header_files("${H_FILES_FILE_HELPER_PLATFORM}")
    project_add_header_files("${H_FILES_SHARED_DATA_PLATFORM}")

    if(PROJECT_USE_CXX_HTTP_CLIENT)
        project_add_header_files("${H_FILES_HTTP_CLIENT_CXX}")
    endif()

    # source files
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

    project_add_source_files("${S_FILES_LOGGER_PLATFORM}")
    project_add_source_files("${S_FILES_HTTP_CLIENT_PLATFORM}")
    project_add_source_files("${S_FILES_FILE_HELPER_PLATFORM}")
    project_add_source_files("${S_FILES_SHARED_DATA_PLATFORM}")

    if(PROJECT_USE_CXX_HTTP_CLIENT)
        project_add_source_files("${S_FILES_HTTP_CLIENT_CXX}")
    endif()

    # search paths
    project_add_search_path("${PROJECT_MODULES_PATH}/support-lib")

    project_add_search_path("${PROJECT_MODULES_PATH}/app-domain/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-enumerator/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-core/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-repository/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-system-service/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/app-helper/gluecode/generated-src/objc")

    project_add_search_path("${PROJECT_MODULES_PATH}/logger/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/http-client/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/http-server/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/file-helper/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/shared-data/gluecode/generated-src/objc")
    project_add_search_path("${PROJECT_MODULES_PATH}/datetime/gluecode/generated-src/objc")
endif()
