set(LUA_PCRE2_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua_pcre2)

add_library(lpcre2
    ${LUA_PCRE2_ROOT}/src/pcre2.lua.c)

target_include_directories(lpcre2
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${LUA_PCRE2_ROOT}/include>
    PRIVATE
        ${LUA_PCRE2_ROOT}/src)

target_link_libraries(lpcre2
    PRIVATE
        lua54
        pcre2)

target_compile_options(lpcre2 PRIVATE -DPCRE2_STATIC)
