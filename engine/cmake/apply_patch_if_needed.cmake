if(NOT EXISTS "${PATCH_FILE}")
    message(FATAL_ERROR "Patch file not found: ${PATCH_FILE}")
endif()

if(NOT EXISTS "${SOURCE_FILE}")
    message(FATAL_ERROR "Source file not found: ${SOURCE_FILE}")
endif()

file(READ "${SOURCE_FILE}" _contents)

if(_contents MATCHES "#include[ \t]+<chrono>")
    message(STATUS "Patch already applied: ${SOURCE_FILE}")
    return()
endif()

execute_process(
    COMMAND git apply "${PATCH_FILE}"
    WORKING_DIRECTORY "${SOURCE_DIR}"
    RESULT_VARIABLE _result
    COMMAND_ERROR_IS_FATAL ANY
)

message(STATUS "Applied patch: ${PATCH_FILE}")