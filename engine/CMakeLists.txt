cmake_minimum_required(VERSION 3.15)
project(capbp_engine CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Resolves (or fetches) the antlr4 C++ runtime, defines `antlr4_runtime`
# either way. Unchanged from the cmkr version - always was plain CMake.
include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_or_fetch_antlr4.cmake")

find_package(Java QUIET COMPONENTS Runtime)
set(CAPBP_ANTLR4_JAR "" CACHE FILEPATH
    "Path to antlr4-*-complete.jar (only needed to regenerate the grammar)")

file(GLOB CAPBP_ENGINE_HEADERS CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB CAPBP_ENGINE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/language/generated/*.cpp")

add_library(capbp_engine STATIC ${CAPBP_ENGINE_SOURCES} ${CAPBP_ENGINE_HEADERS})

target_include_directories(capbp_engine PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
    "${CMAKE_CURRENT_SOURCE_DIR}/language/generated"
)
target_compile_features(capbp_engine PUBLIC cxx_std_17)
target_link_libraries(capbp_engine PUBLIC antlr4_runtime)
set_target_properties(capbp_engine PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

# ---------------------------------------------------------------------
# Optional: enable ANTLR4 grammar regeneration from CapabilityDSL.g4.
# Disabled by default. When enabled, configures the ANTLR4 generator and
# provides the capbp_regenerate_grammar target:
#
#   cmake -B build -DGENERATE_GRAMMAR=ON
#   cmake --build build --target capbp_regenerate_grammar
#
# Generated sources are written to language/generated/.
# ---------------------------------------------------------------------
if(GENERATE_GRAMMAR)
    include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/find_or_fetch_antlr4.cmake")
endif()