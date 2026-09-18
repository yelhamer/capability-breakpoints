# engine/cmake/find_or_fetch_antlr4.cmake
#
# Provides a target named `antlr4_runtime` for capbp_engine to link against,
# trying three approaches in order and using whichever one succeeds first:
#
#   1. find_package()         - works when antlr4 was installed via vcpkg
#                                (Windows: `vcpkg install antlr4`, then
#                                configure with -DCMAKE_TOOLCHAIN_FILE=
#                                <vcpkg>/scripts/buildsystems/vcpkg.cmake),
#                                or via a from-source `cmake --install`.
#   2. find_path/find_library - works for a plain system package with no
#                                exported CMake config, e.g. Debian/Ubuntu's
#                                libantlr4-runtime-dev - this is what your
#                                `-I/usr/include/antlr4-runtime` setup
#                                actually is, made automatic.
#   3. FetchContent            - downloads and builds antlr4's C++ runtime
#                                from source if neither of the above found
#                                anything at all.
#
# NOTE: I can't compile-test this file - no Windows machine, no antlr4
# install, no cmkr binary in this sandbox. The exact CMake target name(s)
# antlr4's own runtime/Cpp/CMakeLists.txt exports have differed across
# releases, so each tier defensively checks a few plausible names. If none
# match on your setup, the FATAL_ERROR at the bottom tells you exactly
# where to look and fix it - shouldn't take more than a couple of minutes.

if(TARGET antlr4_runtime)
    return()
endif()

# For checking if antlr4 is found on system.
#[[
# ---- Tier 1: find_package() --------------------------------------------
find_package(antlr4-runtime CONFIG QUIET)
if(TARGET antlr4-runtime)
    add_library(antlr4_runtime ALIAS antlr4-runtime)
elseif(TARGET antlr4::antlr4-runtime)
    add_library(antlr4_runtime ALIAS antlr4::antlr4-runtime)
elseif(TARGET antlr4_static)
    add_library(antlr4_runtime ALIAS antlr4_static)
endif()

if(TARGET antlr4_runtime)
    message(STATUS "capbp_engine: using antlr4 runtime found via find_package()")
    return()
endif()

# ---- Tier 2: plain headers/lib on the system search path ---------------
find_path(ANTLR4_RUNTIME_INCLUDE_DIR
    NAMES antlr4-runtime.h
    PATH_SUFFIXES antlr4-runtime
)
find_library(ANTLR4_RUNTIME_LIBRARY
    NAMES antlr4-runtime libantlr4-runtime
)
if(ANTLR4_RUNTIME_INCLUDE_DIR AND ANTLR4_RUNTIME_LIBRARY)
    message(STATUS "capbp_engine: using antlr4 runtime found at ${ANTLR4_RUNTIME_LIBRARY}")
    add_library(antlr4_runtime UNKNOWN IMPORTED)
    set_target_properties(antlr4_runtime PROPERTIES
        IMPORTED_LOCATION "${ANTLR4_RUNTIME_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${ANTLR4_RUNTIME_INCLUDE_DIR}"
    )
    return()
endif()


# ---- Tier 3: not found anywhere - fetch and build it ourselves ---------
message(STATUS "capbp_engine: antlr4 runtime not found locally, fetching from "
               "source (install via vcpkg, or set ANTLR4_RUNTIME_INCLUDE_DIR/"
               "ANTLR4_RUNTIME_LIBRARY yourself, to skip this)")
]]

include(FetchContent)

set(CAPBP_ANTLR4_TAG "4.13.2" CACHE STRING
    "ANTLR4 version used by capbp_engine" FORCE)

set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)
if(WIN32)
    # Derived from CMAKE_MSVC_RUNTIME_LIBRARY, already resolved by the root
    # cmake.toml's cmake-before block to match whichever debugger backend(s)
    # were selected - kept as a single source of truth rather than deciding
    # this a second time here. antlr4's own CMakeLists.txt may check this
    # option in addition to respecting CMP0091, so set both consistently.
    if(CMAKE_MSVC_RUNTIME_LIBRARY MATCHES "DLL")
        set(WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)
    else()
        set(WITH_STATIC_CRT ON CACHE BOOL "" FORCE)
    endif()
endif()

FetchContent_Declare(
    antlr4_upstream
    GIT_REPOSITORY https://github.com/antlr/antlr4
    GIT_TAG        ${CAPBP_ANTLR4_TAG}
    GIT_SHALLOW    ON
    SOURCE_SUBDIR  runtime/Cpp

    PATCH_COMMAND
        ${CMAKE_COMMAND}
        -DPATCH_FILE=${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/antlr4-profiling-chrono.patch
        -DSOURCE_DIR=<SOURCE_DIR>
        -DSOURCE_FILE=<SOURCE_DIR>/runtime/Cpp/runtime/src/atn/ProfilingATNSimulator.cpp
        -P
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/apply_patch_if_needed.cmake
)
FetchContent_MakeAvailable(antlr4_upstream)

# ANTLR 4.13.2's ProfilingATNSimulator.cpp uses std::chrono
# without including <chrono>. MSVC 14.44+ exposes this.
if(CAPBP_ANTLR4_VERSION STREQUAL "4.13.2")
    set(ANTLR4_PROFILING_CPP
        "${antlr4_upstream_SOURCE_DIR}/runtime/Cpp/runtime/src/atn/ProfilingATNSimulator.cpp"
    )

    if(EXISTS "${ANTLR4_PROFILING_CPP}")
        file(READ "${ANTLR4_PROFILING_CPP}" _antlr4_profiling_cpp)

        if(NOT _antlr4_profiling_cpp MATCHES "#include[ \t]+<chrono>")
            string(REPLACE
                "#include \"atn/ProfilingATNSimulator.h\""
                "#include \"atn/ProfilingATNSimulator.h\"\n#include <chrono>"
                _antlr4_profiling_cpp
                "${_antlr4_profiling_cpp}"
            )

            file(WRITE
                "${ANTLR4_PROFILING_CPP}"
                "${_antlr4_profiling_cpp}"
            )
        endif()
    endif()
endif()

if(TARGET antlr4_static)
    add_library(antlr4_runtime ALIAS antlr4_static)
elseif(TARGET antlr4_shared)
    add_library(antlr4_runtime ALIAS antlr4_shared)
endif()

if(NOT TARGET antlr4_runtime)
    message(FATAL_ERROR
        "capbp_engine: fetched antlr4 from source but couldn't find a usable "
        "target - check ${antlr4_upstream_SOURCE_DIR}/runtime/Cpp/CMakeLists.txt "
        "for the actual target name it defines, and add it to the elseif chain "
        "in engine/cmake/find_or_fetch_antlr4.cmake"
    )
endif()