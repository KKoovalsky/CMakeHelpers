cmake_minimum_required(VERSION 3.16)

function(JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary target_name git_repository git_tag)

    set(src_dir ${CMAKE_BINARY_DIR}/${target_name})

    include(FetchContent)

    FetchContent_Declare(header_only_lib
        GIT_REPOSITORY ${git_repository}
        GIT_TAG ${git_tag}
        GIT_PROGRESS 1
        SOURCE_DIR ${src_dir}
        CONFIGURE_COMMAND "" 
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
    )
    FetchContent_MakeAvailable(header_only_lib)

    set(options "")
    set(one_value_keywords "")
    set(multi_value_keywords INCLUDE_RELPATHS)
    cmake_parse_arguments(HELPERS "${options}" "${one_value_keywords}" "${multi_value_keywords}" ${ARGN})

    list(TRANSFORM HELPERS_INCLUDE_RELPATHS PREPEND "${src_dir}/" OUTPUT_VARIABLE absolute_include_paths)

    add_library(${target_name} INTERFACE)
    target_include_directories(${target_name} INTERFACE ${absolute_include_paths})

endfunction()
