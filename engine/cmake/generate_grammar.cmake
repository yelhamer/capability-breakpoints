# Grammar generation requires Java.
find_package(Java QUIET COMPONENTS Runtime)

if(NOT Java_JAVA_EXECUTABLE)
    message(FATAL_ERROR
        "GENERATE_GRAMMAR=ON requires Java, but no Java runtime was found. "
        "Install a JRE/JDK and make sure 'java' is available on PATH."
    )

endif()

set(CAPBP_ANTLR4_JAR_DIR
    "${CMAKE_BINARY_DIR}/antlr")

set(CAPBP_ANTLR4_JAR
    "${CAPBP_ANTLR4_JAR_DIR}/antlr-${CAPBP_ANTLR4_TAG}-complete.jar")

file(MAKE_DIRECTORY
    "${CAPBP_ANTLR4_JAR_DIR}")

if(NOT EXISTS "${CAPBP_ANTLR4_JAR}")

    message(STATUS
        "Downloading ANTLR4 ${CAPBP_ANTLR4_TAG} generator...")

    file(DOWNLOAD
        "https://www.antlr.org/download/antlr-${CAPBP_ANTLR4_TAG}-complete.jar"
        "${CAPBP_ANTLR4_JAR}"
        SHOW_PROGRESS
        STATUS CAPBP_ANTLR4_DOWNLOAD_STATUS
        TLS_VERIFY ON
    )

    list(GET CAPBP_ANTLR4_DOWNLOAD_STATUS 0
        CAPBP_ANTLR4_DOWNLOAD_RESULT)

    if(NOT CAPBP_ANTLR4_DOWNLOAD_RESULT EQUAL 0)
        file(REMOVE "${CAPBP_ANTLR4_JAR}")

        message(FATAL_ERROR
            "Failed to download ANTLR4 ${CAPBP_ANTLR4_TAG} generator: "
            "${CAPBP_ANTLR4_DOWNLOAD_STATUS}")
    endif()

endif()

add_custom_target(capbp_regenerate_grammar
    COMMAND
        ${Java_JAVA_EXECUTABLE}
        -jar
        "${CAPBP_ANTLR4_JAR}"
        -Dlanguage=Cpp
        -visitor
        -o
        "${CMAKE_CURRENT_SOURCE_DIR}/language/generated"
        "${CMAKE_CURRENT_SOURCE_DIR}/CapabilityDSL.g4"

    WORKING_DIRECTORY
        "${CMAKE_CURRENT_SOURCE_DIR}"

    COMMENT
        "Regenerating ANTLR4 grammar using ${CAPBP_ANTLR4_TAG}"

    VERBATIM
)
