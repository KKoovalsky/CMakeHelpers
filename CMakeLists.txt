cmake_minimum_required(VERSION 3.16)

function(JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary target_name git_repository git_tag)

    include(ExternalProject)

    set(header_only_lib ${target_name}_sources)
    set(src_dir ${PROJECT_BINARY_DIR}/${header_only_lib}) 

    ExternalProject_Add(${header_only_lib}
        GIT_REPOSITORY ${git_repository}
        GIT_TAG ${git_tag}
        GIT_PROGRESS 1
        SOURCE_DIR ${src_dir}
        CONFIGURE_COMMAND "" 
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
    )

    set(options "")
    set(one_value_keywords "")
    set(multi_value_keywords INCLUDE_RELPATHS)
    cmake_parse_arguments(HELPERS "${options}" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

    list(TRANSFORM HELPERS_INCLUDE_RELPATHS PREPEND "${src_dir}/" OUTPUT_VARIABLE absolute_include_paths)

    add_library(${target_name} INTERFACE)
    add_dependencies(${target_name} ${header_only_lib})
    target_include_directories(${target_name} INTERFACE ${absolute_include_paths})

endfunction()
