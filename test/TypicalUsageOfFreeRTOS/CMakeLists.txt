cmake_minimum_required(VERSION 3.16)

project(TypicalUsageOfFreeRTOS)

include(FetchContent)

FetchContent_Declare(
    cmake_helpers
    GIT_REPOSITORY https://github.com/KKoovalsky/CMakeHelpers.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cmake_helpers)

JunglesHelpers_DownloadAndPopulateFreeRTOSKernel(freertos V10.4.1-kernel-only heap_1)
target_include_directories(freertos PUBLIC 
    ${CMAKE_SOURCE_DIR}
    ${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/Posix
    ${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/Posix/utils
)
target_sources(freertos PRIVATE 
    ${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/Posix/port.c
    ${FREERTOS_SOURCE_DIR}/portable/ThirdParty/GCC/Posix/utils/wait_for_event.c
)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE freertos)
