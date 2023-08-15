cmake_minimum_required(VERSION 3.12)
project(amalgamate)

###############################################################################
# Functions
###############################################################################

# Enable all warning for target
function(setup_target_wall name)
    if (CMAKE_C_COMPILER_ID STREQUAL "MSVC")
        target_compile_options(${name} PRIVATE /W4 /WX)
    else ()
        target_compile_options(${name} PRIVATE -Wall -Wextra -Werror)
    endif ()
endfunction()

###############################################################################
# Setup executable
###############################################################################

add_executable(${PROJECT_NAME}
    "src/main.c")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src)

setup_target_wall(${PROJECT_NAME})

###############################################################################
# Dependency
###############################################################################

# Lua
include(third_party/lua54.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE lua54)

# cJSON
include(third_party/cJSON.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE cJSON)

# cjson.lua
include(third_party/cjson.lua.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE cjson.lua)

# lua_pcre2
include(third_party/pcre2.cmake)
include(third_party/pcre2.lua.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE pcre2.lua)

###############################################################################
# Amalgamate
###############################################################################
add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_SOURCE_DIR}/amalgamate_all.c
        ${CMAKE_CURRENT_BINARY_DIR}/__always_run.h
    COMMAND $<TARGET_FILE:amalgamate>
        --input=${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
        --output=${CMAKE_CURRENT_SOURCE_DIR}/amalgamate_all.c
        --iquote=${CMAKE_CURRENT_SOURCE_DIR}/src)
add_custom_target(my_custom_target_that_always_runs ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/__always_run.h)
add_executable(${PROJECT_NAME}_all
    ${CMAKE_CURRENT_SOURCE_DIR}/amalgamate_all.c)
setup_target_wall(${PROJECT_NAME}_all)
target_link_libraries(${PROJECT_NAME}_all PRIVATE lua54)
target_link_libraries(${PROJECT_NAME}_all PRIVATE cJSON)
target_link_libraries(${PROJECT_NAME}_all PRIVATE cjson.lua)
target_link_libraries(${PROJECT_NAME}_all PRIVATE pcre2.lua)

###############################################################################
# Test
###############################################################################
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
