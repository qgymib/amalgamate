#define LF	"\n"
static const char* expand_include_script = "\n" LF
LF
"local M = {}" LF
"M.pattern = \"^\\\\s*#\\\\s*include\\\\s+\\\"([-.\\\\w/]+)\\\".*?$\"" LF
"M.regex = am.pcre2.compile(M.pattern)" LF
LF
"local function expand_include_proc(data, args)" LF
"    -- Local variable" LF
"    local ret = \"\"" LF
"    local regex = M.regex" LF
LF
"    -- Argument format" LF
"    if args.lineno == nil then" LF
"        args.lineno = true" LF
"    end" LF
LF
"    while true do" LF
"        local match_data = regex:match(data)" LF
"        if match_data == nil then" LF
"            ret = ret .. data" LF
"            break" LF
"        end" LF
LF
"        -- Append data before pattern" LF
"        local off,len = match_data:group_offset(0)" LF
"        if off >= 2 then" LF
"            ret = ret .. string.sub(data, 1, off)" LF
"        end" LF
LF
"        -- Get include file path" LF
"        local inc_file_path = match_data:group(data, 1)" LF
"        local real_file_path = am.search_file(inc_file_path)" LF
"        if real_file_path == nil then" LF
"            local err_msg = \"file `\" .. inc_file_path .. \"` not found.\"" LF
"            error(err_msg)" LF
"        end" LF
LF
"        -- Get file information" LF
"        local file_data_txt = am.load_txt_file(real_file_path)" LF
"        io.write(am.dumphex(file_data_txt))" LF
"        local file_data_bin = am.load_file(real_file_path)" LF
"        local file_sha256 = am.sha256(file_data_bin)" LF
"        local file_len = string.len(file_data_bin)" LF
LF
"        -- Generate header" LF
"        ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
"        ret = ret .. \"// PATH:    \" .. inc_file_path .. \"\\n\"" LF
"        ret = ret .. \"// SIZE:    \" .. string.format(\"%q\", file_len) .. \"\\n\"" LF
"        ret = ret .. \"// SHA-256: \" .. file_sha256 .. \"\\n\"" LF
"        ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
LF
"        -- Append file content" LF
"        if args.lineno then" LF
"            ret = ret .. \"#line \" .. inc_file_path .. \" 1\\n\"" LF
"        end" LF
"        ret = ret .. file_data_txt .. \"\\n\"" LF
LF
"        -- Update data" LF
"        off,len = match_data:group_offset(0)" LF
"        data = string.sub(data, off + len)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = expand_include_proc," LF
"    desc = " LF
"[[DESCRIPTION:"LF
"    Expand user include." LF
LF
"ATTRIBUTES:" LF
"    \"lineno\": true|false. Default: true." LF
"        Enable `#line [path] 1` syntax so that if compile error, you known what" LF
"        is wrong." LF
"]]," LF
"}" LF
;

#include "c_expand_include.h"

static int _am_c_expand_include(lua_State* L)
{
    return am_addon_call_script(L, expand_include_script, "expand_include.lua");
}

am_addon_t am_addon_c_expand_include = {
    "c:expand_include",
    _am_c_expand_include,
};
