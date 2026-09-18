cmake_minimum_required(VERSION 3.15)

if(POLICY CMP0091)
    cmake_policy(SET CMP0091 NEW)
endif()

option(CAPBP_BUILD_X64DBG "Build x64dbg debugger backend" OFF)
option(CAPBP_BUILD_WINDBG "Build WinDbg debugger backend" OFF)
option(CAPBP_BUILD_IDA    "Build IDA debugger backend"    OFF)

project(UniversalDebuggerProject C CXX)

# C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Always built regardless of which backend(s) are selected.
add_subdirectory(engine)

# Each backend's own CMakeLists.txt is a checked-in, already-generated file.
if(CAPBP_BUILD_X64DBG)
    add_subdirectory(debuggers/x64dbg)
endif()

if(CAPBP_BUILD_WINDBG)
    add_subdirectory(debuggers/windbg)
endif()

if(CAPBP_BUILD_IDA)
    add_subdirectory(debuggers/ida)
endif()
