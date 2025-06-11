cmake_minimum_required(VERSION 3.5)

# Build options:
#   -DRUN_CODEGEN_POST_BUILD=ON  : Run codegen on smbdis.asm after build (default: OFF)
#
# Examples:
#   cmake .                                    # Build without running codegen
#   cmake -DRUN_CODEGEN_POST_BUILD=ON .       # Build and run codegen on smbdis.asm

# Option to control whether to run the post-build command
option(RUN_CODEGEN_POST_BUILD "Run codegen on smbdis.asm after build" OFF)

find_package(BISON)
find_package(FLEX)

BISON_TARGET(parser asm6502.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp)
FLEX_TARGET(scanner asm6502.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

add_executable(codegen
    ${BISON_parser_OUTPUTS}
    ${FLEX_scanner_OUTPUTS}
    ast.cpp 
    translator.cpp
    util.cpp
)

# Only add the custom command if the option is enabled
if(RUN_CODEGEN_POST_BUILD)
    add_custom_command(TARGET codegen
                       POST_BUILD 
                       COMMAND $<TARGET_FILE:codegen> ${PROJECT_SOURCE_DIR}/docs/smbdis.asm ${PROJECT_SOURCE_DIR})
endif()
