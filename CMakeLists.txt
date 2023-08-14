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
    "src/addon/__init__.c"
    "src/addon/c_dump_hex.c"
    "src/addon/c_expand_include.c"
    "src/addon/txt_black_hole.c"
    "src/addon/txt_pcre2_substitute.c"
    "src/function/__init__.c"
    "src/function/lua_file.c"
    "src/function/lua_sha256.c"
    "src/function/lua_string.c"
    "src/function/lua_table.c"
    "src/preproccess.c"
    "src/amalgamate.c"
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
# Test
###############################################################################
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
