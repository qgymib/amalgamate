#define LF "\n"
static const char* pcre2_substitute_script = "\n" LF
"local pcre2 = require(\"pcre2\")" LF
LF
"local function pcre2_substitute_proc(data, args)" LF
"    -- Check arguments" LF
"    if args.pattern == nil then" LF
"        error(\"missing argument `pattern`.\")" LF
"    end" LF
"    if args.replace == nil then" LF
"        error(\"missing argument `replace`.\")" LF
"    end" LF
LF
"    local code = pcre2.compile(args.pattern, pcre2.PCRE2_MULTILINE)" LF
"    return code:substitute(data, args.replace," LF
"        pcre2.PCRE2_SUBSTITUTE_GLOBAL | pcre2.PCRE2_SUBSTITUTE_EXTENDED)" LF
"end" LF
LF
"return {" LF
"    proc = pcre2_substitute_proc," LF
"    desc = " LF
"[[DESCRIPTION:" LF
"    Find and substituting a replacement string for what was matched." LF
LF
"ATTRIBUTES:" LF
"    \"pattern\": [string]" LF
"        A regex pattern for find match string." LF
"    \"replace\": [string]" LF
"        Replacement string." LF
"]]," LF
"}" LF
;

#include "txt_pcre2_substitute.h"

static int _am_txt_pcre2_substitute(lua_State* L)
{
    return am_addon_call_script(L, pcre2_substitute_script, "txt:pcre2_substitute.lua");
}

am_addon_t am_addon_txt_pcre2_substitute = {
    "txt:pcre2_substitute",
    _am_txt_pcre2_substitute,
};
