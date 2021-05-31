# add module
macro(project_add_module name)
    message(STATUS "Ezored: Adding module: ${name}")
    include(${PROJECT_MODULES_PATH}/${name}/cmake/module.cmake)
endmacro()

# add all modules
macro(project_add_modules)
    message(STATUS "Ezored: Adding modules...")

    project_list_subdirs(modules ${PROJECT_MODULES_PATH} TRUE)

    foreach(module ${modules})
        if(EXISTS "${PROJECT_MODULES_PATH}/${module}/cmake/module.cmake")
            project_add_module(${module})
        endif()
    endforeach()

    message(STATUS "Ezored: Modules added")
endmacro()

# list all subdirs
macro(project_list_subdirs retval curdir return_relative)
    file(
        GLOB sub-dir
        RELATIVE ${curdir}
        ${curdir}/*
    )

    set(${retval} "")

    foreach(dir ${sub-dir})
        if(IS_DIRECTORY ${curdir}/${dir})
            if(${return_relative})
                list(APPEND ${retval} ${dir})
            else()
                list(APPEND ${retval} ${curdir}/${dir})
            endif()
        endif()
    endforeach()
endmacro()

# project add search path
macro(project_add_search_path new_path)
    list(APPEND PROJECT_HEADER_SEARCH_PATHS ${new_path})
endmacro()

# project add header files
macro(project_add_header_files new_file_list)
    list(APPEND PROJECT_HEADER_FILES ${new_file_list})
endmacro()

# project add source files
macro(project_add_source_files new_file_list)
    list(APPEND PROJECT_SOURCE_FILES ${new_file_list})
endmacro()
