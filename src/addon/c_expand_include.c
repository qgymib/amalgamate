#define LF  "\n"
static const char* expand_include_script = "\n" LF
"local pcre2 = require(\"pcre2\")" LF
LF
"local M = {}" LF
"-- This is the pattern to search `#include` statement." LF
"M.pattern = \"#\\\\s*include\\\\s+\\\"([-.\\\\w/]+)\\\"\"" LF
"M.regex = pcre2.compile(M.pattern, pcre2.PCRE2_MULTILINE)" LF
LF
"-- Set default value if not exist" LF
"local function format_default_arguments(args)" LF
"    if args.lineno == nil then" LF
"        args.lineno = true" LF
"    end" LF
"    if args.fileinfo == nil then" LF
"        args.fileinfo = true" LF
"    end" LF
"    if args.displace_include == nil then" LF
"        args.displace_include = true" LF
"    end" LF
"    return args" LF
"end" LF
LF
"-- Get file information for matched regex pattern" LF
"local function generate_file_info(match_data, data)" LF
"    local info = {}" LF
"    info.include_path = match_data:group(data, 1)" LF
"    info.real_path = am.search_file(info.include_path)" LF
"    if info.real_path == nil then" LF
"        local err_msg = \"file `\" .. info.include_path .. \"` not found.\"" LF
"        error(err_msg)" LF
"    end" LF
"    info.txt_data = am.load_txt_file(info.real_path)" LF
"    info.bin_data = am.load_file(info.real_path)" LF
"    info.sha256 = am.sha256(info.bin_data)" LF
"    info.bin_size = string.len(info.bin_data)" LF
"    return info" LF
"end" LF
LF
"-- Generate file header" LF
"local function generate_header_info(info, args)" LF
"    if not args.fileinfo then" LF
"        return \"\"" LF
"    end" LF
"    local ret = \"\"" LF
"    ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
"    ret = ret .. \"// PATH:    \" .. info.include_path .. \"\\n\"" LF
"    ret = ret .. \"// SIZE:    \" .. string.format(\"%q\", info.bin_size) .. \"\\n\"" LF
"    ret = ret .. \"// SHA-256: \" .. info.sha256 .. \"\\n\"" LF
"    ret = ret .. string.rep(\"/\", 80) .. \"\\n\"" LF
"    return ret" LF
"end" LF
LF
"-- Generate file content" LF
"local function generate_file_content(info, args, regex)" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    if args.lineno then" LF
"        ret = ret .. \"#line 1 \\\"\" .. info.include_path .. \"\\\"\\n\"" LF
"    end" LF
"    if args.displace_include then" LF
"        temp = regex:substitute(info.txt_data, \"/* AMALGAMATE_DISPLACE: ${0} */\"," LF
"            pcre2.PCRE2_SUBSTITUTE_GLOBAL | pcre2.PCRE2_SUBSTITUTE_EXTENDED)" LF
"    end" LF
"    ret = ret .. temp .. \"\\n\"" LF
"    return ret" LF
"end" LF
LF
"-- c:expand_include" LF
"local function expand_include_proc(data, args)" LF
"    -- Local variable" LF
"    local ret = \"\"" LF
"    local temp = \"\"" LF
"    local regex = M.regex" LF
LF
"    args = format_default_arguments(args)" LF
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
"            temp = string.sub(data, 1, off)" LF
"            ret = ret .. temp" LF
"        end" LF
LF
"        -- Get file information" LF
"        local info = generate_file_info(match_data, data)"
LF
"        -- Generate header" LF
"        temp = generate_header_info(info, args)" LF
"        ret = ret .. temp" LF
LF
"        -- Append file content" LF
"        temp = generate_file_content(info, args, regex)" LF
"        ret = ret .. temp" LF
LF
"        -- Update data" LF
"        off,len = match_data:group_offset(0)" LF
"        data = string.sub(data, off + len + 1)" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = expand_include_proc," LF
"    brief = \"Replace file content with #include path.\"," LF
"    desc = " LF
"[[Read #include file content and replace the #include statement."LF
LF
"[ATTRIBUTES]" LF
"\"lineno\": true|false. Default: true." LF
"    Enable `#line [path] 1` syntax so that if compile error, you known what" LF
"    is wrong." LF
"\"fileinfo\": true|false. Default: true" LF
"    Add file path, size, SHA-256 information before replacement." LF
"\"displace_include\": true|false. Default: true" LF
"    comment `#include \"foo.h\"`." LF
"]]," LF
"}" LF
;

#include "__init__.h"

static int _am_c_expand_include(lua_State* L)
{
    return am_addon_call_script(L, expand_include_script, "c:expand_include.lua");
}

am_addon_t am_a_c_expand_include = {
    "c:expand_include",
    _am_c_expand_include,
};
