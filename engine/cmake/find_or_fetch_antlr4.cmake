# Provides a target named `antlr4_runtime` for capbp_engine to link against.

if(TARGET antlr4_runtime)
    return()
endif()

include(FetchContent)

set(CAPBP_ANTLR4_TAG "4.13.2" CACHE STRING
    "ANTLR4 version used by capbp_engine" FORCE)

# ANTLR4 runtime uses the dynamic MSVC runtime.
# This keeps it compatible with capbp_engine (/MD).
#if(WIN32)
#    set(WITH_STATIC_CRT OFF CACHE BOOL "" FORCE)
#endif()

set(ANTLR4_INSTALL OFF CACHE BOOL "" FORCE)
set(ANTLR_BUILD_CPP_TESTS OFF CACHE BOOL "" FORCE)

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
# without including <chrono>.
if(CAPBP_ANTLR4_TAG STREQUAL "4.13.2")

    set(ANTLR4_PROFILING_CPP
        "${antlr4_upstream_SOURCE_DIR}/runtime/Cpp/runtime/src/atn/ProfilingATNSimulator.cpp"
    )

    if(EXISTS "${ANTLR4_PROFILING_CPP}")

        file(READ
            "${ANTLR4_PROFILING_CPP}"
            _antlr4_profiling_cpp
        )

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
