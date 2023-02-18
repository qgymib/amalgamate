set(LUA54_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/lua)

add_library(lua54 STATIC
    ${LUA54_ROOT}/lapi.c
    ${LUA54_ROOT}/lcode.c
    ${LUA54_ROOT}/lctype.c
    ${LUA54_ROOT}/ldebug.c
    ${LUA54_ROOT}/ldo.c
    ${LUA54_ROOT}/ldump.c
    ${LUA54_ROOT}/lfunc.c
    ${LUA54_ROOT}/lgc.c
    ${LUA54_ROOT}/llex.c
    ${LUA54_ROOT}/lmem.c
    ${LUA54_ROOT}/lobject.c
    ${LUA54_ROOT}/lopcodes.c
    ${LUA54_ROOT}/lparser.c
    ${LUA54_ROOT}/lstate.c
    ${LUA54_ROOT}/lstring.c
    ${LUA54_ROOT}/ltable.c
    ${LUA54_ROOT}/ltm.c
    ${LUA54_ROOT}/lundump.c
    ${LUA54_ROOT}/lvm.c
    ${LUA54_ROOT}/lzio.c
    ${LUA54_ROOT}/lauxlib.c
    ${LUA54_ROOT}/lbaselib.c
    ${LUA54_ROOT}/lcorolib.c
    ${LUA54_ROOT}/ldblib.c
    ${LUA54_ROOT}/liolib.c
    ${LUA54_ROOT}/lmathlib.c
    ${LUA54_ROOT}/loadlib.c
    ${LUA54_ROOT}/loslib.c
    ${LUA54_ROOT}/lstrlib.c
    ${LUA54_ROOT}/ltablib.c
    ${LUA54_ROOT}/lutf8lib.c
    ${LUA54_ROOT}/linit.c)

target_include_directories(lua54
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${LUA54_ROOT}/>)

if (UNIX)
    target_compile_options(lua54 PRIVATE -DLUA_USE_LINUX)
    target_link_libraries(lua54 PRIVATE m)
endif ()
