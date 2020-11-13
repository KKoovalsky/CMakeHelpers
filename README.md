# CMake Helpers

## How to use it

The helpers are intended to be used within CMake scripts. So you can simply make this repository a git submodule
and call `include()` directive from a CMake script.

The preffered way is to use `FetchContent` utility (available from CMake version 3.11), 
from a CMake script file (e.g. `CMakeLists.txt`):

```
include(FetchContent)

FetchContent_Declare(
    cmake_helpers
    GIT_REPOSITORY https://github.com/KKoovalsky/CMakeHelpers.git
    GIT_TAG main
)
FetchContent_MakeAvailable(cmake_helpers)

# Use the API freely - all the functions will be imported now, e.g.:
# JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary( ... )

```


## API

### JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary

```
JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary(<target_name> <git_repository> <git_tag> 
    [INCLUDE_RELPATHS <relative_paths_being_include_directories> )
```

Download and create an INTERFACE library, with `INCLUDE_RELPATHS` that will be included through
`target_include_directories` for the created target.

* `target_name` - the name of the target which will be the created library target to which you can link to.
* `git_repository` and `git_tag` - the URL of the git repository where the library is stored and tag to be checkouted.
* `INCLUDE_RELPATHS <relative_paths_being_include_directories>` - optional list of paths to be included as INTERFACE
include directories. Most probably it will be "include" path or "single_include" path or ".".

Example:

```
JunglesHelpers_DownloadAndPopulateHeaderOnlyLibrary(
    catch2
    https://github.com/catchorg/Catch2.git
    0f129955
    INCLUDE_RELPATHS single_include
)
```

Will download Catch2 library, checkout it to commit `0f129955` and will include the "single_include" as a INTERFACE
include directory for the target. The library target name can be accessed with `catch2` name in the parent scope.

### JunglesHelpers_DownloadAndPopulateFreeRTOSKernel

```
JunglesHelpers_DownloadAndPopulateFreeRTOSKernel(<target_name> <git_tag> <heap_implementation>)
```

Download and create a STATIC library with FreeRTOS. Parameters are:
* `target_name` - the name of the target which will be the created library target to which you can link to.
* `git_tag` - the tag to be checkouted for the FreeRTOS-Kernel repository.
* `heap_implementation` - the FreeRTOS heap implementation, which may be: `heap_1`, `heap_2`, `heap_3`, ... It will
be included in the source list.

After invoking the function a variable `<TARGET_NAME_UPPERCASE>_SOURCE_DIR` will be set, so you could use it
to include specific port build and corresponding include directories:

```
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
```

