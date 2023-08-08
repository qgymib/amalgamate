#define LF	"\n"
const char* script = "\n\n\n\n\n" LF // let's align the line number

//////////////////////////////////////////////////////////////////////////
// Script begin
//////////////////////////////////////////////////////////////////////////
"-- @brief Dump any value as string" LF
"-- @param o Any Lua object" LF
"-- @return A string contains value of object \\p o" LF
"local function dump(o)" LF
"    if type(o) == 'table' then" LF
"        local s = '{ '" LF
"        for k,v in pairs(o) do" LF
"            if type(k) ~= 'number' then k = '\"'..k..'\"' end" LF
"            s = s .. '['..k..'] = ' .. dump(v) .. ','" LF
"        end" LF
"        return s .. '} '" LF
"    else" LF
"        return tostring(o)" LF
"    end" LF
"end" LF
"am.dump = dump" LF
LF
"-- @brief Search file in iquote table and return real path" LF
"-- @param path The file that want to search" LF
"-- @return The real path that can be opened or nil if failed" LF
"local function search_file(path)" LF
"    local tmp_path = am.dirname(arg.input) .. \"/\" .. path" LF
"    if am.is_file_exist(tmp_path) then" LF
"        return tmp_path" LF
"    end" LF
"    for _,v in ipairs(arg.iquote) do" LF
"        tmp_path = v .. \"/\" .. path" LF
"        if am.is_file_exist(tmp_path) then" LF
"            return tmp_path" LF
"        end" LF
"    end" LF
"    return nil" LF
"end" LF
"am.search_file = search_file" LF
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
"-- Process json" LF
"local function process_json(code, data)" LF
"    local config = am.json.from_json(code)" LF
"    if am.table_is_array(config) then" LF
"        for _, v in ipairs(config) do" LF
"            data = process_json_addon(data, v)" LF
"        end" LF
"    else" LF
"        data = process_json_addon(data, config)" LF
"    end" LF
"    return data" LF
"end" LF
LF
"-- All runtime information" LF
"local rt = {}" LF
LF
"-- Read input file" LF
"rt.input_content = am.load_txt_file(arg.input)" LF
LF
"-- Split input file into sequence of token" LF
"local payload = am.preproccess(rt.input_content)" LF
LF
"-- For each token let's do the magic" LF
"for _,v in ipairs(payload) do" LF
"    if v.lang == nil then" LF
"        -- do nothing" LF
"    elseif am.strcasecmp(v.lang, \"lua\") == 0 then" LF
"        local func = load(v.code)" LF
"        v.data = func(v.data)" LF
"    elseif am.strcasecmp(v.lang, \"json\") == 0 then" LF
"        v.data = process_json(v.code, v.data)" LF
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
"am.write_file(arg.output, rt.output_content)" LF

//////////////////////////////////////////////////////////////////////////
// Script end
//////////////////////////////////////////////////////////////////////////
;

#include "amalgamate.h"
