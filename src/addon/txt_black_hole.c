#define LF "\n"
static const char* black_hole_script = "\n" LF
"local function black_hole_proc(data, args)" LF
"    return \"\"" LF
"end" LF
LF
"return {" LF
"    proc = black_hole_proc," LF
"    brief = \"Eliminate anything.\","
"    desc = " LF
"[[Eliminate anything." LF
LF
"[ATTRIBUTES]" LF
"none." LF
"]]," LF
"}" LF
;

#include "txt_black_hole.h"

static int _am_txt_black_hole(lua_State* L)
{
    return am_addon_call_script(L, black_hole_script, "txt:black_hole.lua");
}

am_addon_t am_addon_txt_black_hole = {
    "txt:black_hole",
    _am_txt_black_hole,
};
