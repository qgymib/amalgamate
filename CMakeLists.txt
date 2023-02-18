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
    "src/filter/__init__.c"
    "src/filter/c_comment_user_include.c"
    "src/filter/c_file_information.c"
    "src/utils/lua_api.c"
    "src/utils/lua_file.c"
    "src/utils/lua_json.c"
    "src/utils/lua_substitute.c"
    "src/utils/str.c"
    "src/utils/uuid.c"
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

# PCRE2
include(third_party/pcre2.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE pcre2)

###############################################################################
# Test
###############################################################################
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(CTest)
endif()
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME AND BUILD_TESTING)
    add_subdirectory(test)
endif()
