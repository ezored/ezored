def run(proj_path, target_name, params):
    return {
        "cpp_namespace_prefix": "ezored",
        "cpp_include_prefix": "ezored",
        "objc_prefix": "EZR",
        "java_package_prefix": "com.ezored",
        "jni_class_prefix": "EZR",
        "jni_file_prefix": "EZR",
        "modules": [
            "app-enumerator",
            "app-domain",
            "app-core",
            "app-repository",
            "app-system-service",
            "app-helper",
            "datetime",
            "file-helper",
            "http-client",
            "logger",
            "shared-data",
            "string-helper",
        ],
    }
