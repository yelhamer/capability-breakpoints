cmake_minimum_required(VERSION 3.15)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

option(CAPBP_BUILD_X64DBG "Build x64dbg debugger backend" OFF)
#option(CAPBP_BUILD_WINDBG "Build WinDbg debugger backend" OFF)
#option(CAPBP_BUILD_IDA    "Build IDA debugger backend"    OFF)

# Each debugger backend may expect a different MSVC runtime:
# - x64dbg's PluginTemplate forces static (/MT)
# - windbg/ida likely need dynamic (/MD) - update once you know
# If multiple backends are enabled and they conflict, x64dbg wins (static).
# Must be set before project() for CMP0091 to actually take effect.
if(CAPBP_BUILD_X64DBG)
    set(CAPBP_MSVC_RUNTIME "MultiThreaded$<$<CONFIG:Debug>:Debug>")     # static  (/MT)
else()
    set(CAPBP_MSVC_RUNTIME "MultiThreadedDLL$<$<CONFIG:Debug>:Debug>") # dynamic (/MD)
endif()
set(CMAKE_MSVC_RUNTIME_LIBRARY "${CAPBP_MSVC_RUNTIME}" CACHE STRING "")

project(UniversalDebuggerProject C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Always built regardless of which backend(s) are selected - the backends
# link against it.
add_subdirectory(engine)

# Each backend's own CMakeLists.txt is a checked-in, already-generated file
# (see debuggers/x64dbg/README or however you note this) - this project
# never invokes cmkr itself, it just consumes whatever's already there.
if(CAPBP_BUILD_X64DBG)
    add_subdirectory(debuggers/x64dbg)
endif()
#[[
if(CAPBP_BUILD_WINDBG)
    add_subdirectory(debuggers/windbg)
endif()
if(CAPBP_BUILD_IDA)
    add_subdirectory(debuggers/ida)
endif()]]