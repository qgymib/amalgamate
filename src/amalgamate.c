#define LF  "\n"
const char* amalgamate_script = "\n\n\n\n\n" LF // let's align the line number

//////////////////////////////////////////////////////////////////////////
// Script begin
//////////////////////////////////////////////////////////////////////////
"local cjson = require(\"cjson\")" LF
LF
"-- Process data with addon configuration" LF
"local function process_json_addon(data, config)" LF
"    config.args = config.args or {}" LF
"    if config.name == nil then" LF
"        local errmsg = \"missing field `name` in json\"" LF
"        error(errmsg)" LF
"    end" LF
"    local addon = require(config.name)" LF
"    return addon.proc(data, config.args)" LF
"end" LF
LF
"-- Process json block" LF
"local function process_json_block(v)" LF
"    local config = cjson.from_json(v.code)" LF
"    local data = v.data" LF
"    if am.table_is_array(config) then" LF
"        for _, e in ipairs(config) do" LF
"            data = process_json_addon(data, e)" LF
"        end" LF
"    else" LF
"        data = process_json_addon(data, config)" LF
"    end" LF
"    return data" LF
"end" LF
LF
"-- Process lua block" LF
"local function process_lua_block(v)" LF
"    local trunk, errmsg = load(v.code)" LF
"    if not trunk then" LF
"        error(errmsg)" LF
"    end" LF
"    local b,addon = pcall(trunk)" LF
"    if b ~= true then" LF
"        error(addon)" LF
"    end" LF
"    return addon.proc(v.data, {})" LF
"end" LF
LF
"-- Preprocess file" LF
"local function preprocess(data)" LF
"    local ret = {}" LF
"    local split_ret = am.split_line_by_pattern(data, am.config.parser_pattern)" LF
"    for _,v in ipairs(split_ret) do" LF
"        local tmp = {" LF
"            data = v.data," LF
"            line_beg = v.line_beg," LF
"            line_end = v.line_end," LF
"        }" LF
"        if v.group ~= nil then" LF
"            tmp.lang = v.group[1]" LF
"            tmp.code = v.group[2]" LF
"            tmp.data = v.group[3]" LF
"        end" LF
"        ret[#ret + 1] = tmp" LF
"    end" LF
"    return ret" LF
"end" LF
LF
"-- All runtime information" LF
"local rt = {}" LF
LF
"-- Read input file" LF
"rt.input_content = am.load_txt_file(am.config.input)" LF
LF
"-- Split input file into sequence of token" LF
"local payload = preprocess(rt.input_content)" LF
LF
"-- For each token let's do the magic" LF
"for _,v in ipairs(payload) do" LF
"    if v.lang == nil then" LF
"        -- do nothing" LF
"    elseif am.strcasecmp(v.lang, \"lua\") == 0 then" LF
"        v.data = process_lua_block(v)" LF
"    elseif am.strcasecmp(v.lang, \"json\") == 0 then" LF
"        v.data = process_json_block(v)" LF
"    else" LF
"        local err_msg = \"unknown lang `\" .. v.lang .. \"`.\"" LF
"        error(err_msg)" LF
"    end" LF
LF
"    if v.data == nil then" LF
"        v.data = \"\"" LF
"    end" LF
"end" LF
LF
"-- Generate content" LF
"rt.output_content = \"\"" LF
"for _,v in ipairs(payload) do" LF
"    rt.output_content = rt.output_content .. v.data .. \"\\n\"" LF
"end" LF
LF
"-- Write file" LF
"am.write_file(am.config.output, rt.output_content)" LF

//////////////////////////////////////////////////////////////////////////
// Script end
//////////////////////////////////////////////////////////////////////////
;

#include "amalgamate.h"
