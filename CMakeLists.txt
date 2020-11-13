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

function(JunglesHelpers_DownloadAndPopulateFreeRTOSKernel target_name git_tag heap_implementation)

    include(FetchContent)
    FetchContent_Declare(freertos_kernel_sources
        GIT_REPOSITORY https://github.com/FreeRTOS/FreeRTOS-Kernel.git
        GIT_TAG ${git_tag}
        GIT_PROGRESS 1
        CONFIGURE_COMMAND "" 
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND ""
    )
    FetchContent_MakeAvailable(freertos_kernel_sources)

    set(src_dir ${freertos_kernel_sources_SOURCE_DIR})

    set(_freertos_kernel_source_files
        ${src_dir}/croutine.c
        ${src_dir}/event_groups.c
        ${src_dir}/list.c
        ${src_dir}/queue.c
        ${src_dir}/stream_buffer.c
        ${src_dir}/tasks.c
        ${src_dir}/timers.c
        ${src_dir}/portable/MemMang/${heap_implementation}.c
    )

    add_library(${target_name} STATIC ${_freertos_kernel_source_files})
    target_include_directories(${target_name} PUBLIC ${src_dir}/include)

    string(TOUPPER ${target_name} target_name_upper)
    set(${target_name_upper}_SOURCE_DIR ${src_dir} PARENT_SCOPE)

endfunction()
