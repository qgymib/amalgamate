set(LUA_PCRE2_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/pcre2.lua)

add_library(pcre2.lua
    ${LUA_PCRE2_ROOT}/src/pcre2.lua.c)

target_include_directories(pcre2.lua
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${LUA_PCRE2_ROOT}/include>
    PRIVATE
        ${LUA_PCRE2_ROOT}/src)

target_link_libraries(pcre2.lua
    PRIVATE
        lua54
        pcre2)

target_compile_options(pcre2.lua PRIVATE -DPCRE2_STATIC)
