set(CJSON_LUA_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/third_party/cjson.lua)

add_library(cjson.lua
	${CJSON_LUA_ROOT}/src/cjson.lua.c)

target_include_directories(cjson.lua
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CJSON_LUA_ROOT}/include>
    PRIVATE
        ${CJSON_LUA_ROOT}/src)

target_link_libraries(cjson.lua
    PRIVATE
        lua54
        cJSON)
