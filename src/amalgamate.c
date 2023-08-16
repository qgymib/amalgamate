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
"    local trunk = load(v.code)" LF
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
"    while true do" LF
"        local off_beg_0, off_end_0, group_lang, group_code, group_data" LF
"            = string.find(data, am.config.parser_pattern)" LF
"        if off_beg_0 == nil then" LF
"            ret[#ret + 1] = { data = data }" LF
"            break" LF
"        end" LF
"        if off_beg_0 > 1 then" LF
"            ret[#ret + 1] = { data = string.sub(data, 1, off_beg_0 - 1) }" LF
"        end" LF
"        ret[#ret + 1] = {" LF
"            lang = group_lang," LF
"            code = group_code," LF
"            data = group_data," LF
"        }" LF
"        data = string.sub(data, off_end_0 + 1)" LF
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
