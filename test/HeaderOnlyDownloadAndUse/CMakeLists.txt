cmake_minimum_required(VERSION 3.16)

project(HeaderOnlyDownloadAndUsage)

include(FetchContent)

FetchContent_Declare(
    cmake_helpers
    GIT_REPOSITORY https://github.com/KKoovalsky/CMakeHelpers.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cmake_helpers)

JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary(
    baduit_timer
    https://github.com/Baduit/Timer.git
    a1dff706020a8443903a79ca1cbf911a82e701d3
    INCLUDE_RELPATHS src
)
target_compile_features(baduit_timer INTERFACE cxx_std_17)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE baduit_timer)
