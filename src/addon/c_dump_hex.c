#define LF "\n"
static const char* dump_hex_script = "\n" LF
LF
"local function dump_hex_proc(data, args)" LF
"    local src_data = data" LF
"    local ret = \"\"" LF
LF
"    -- Format arguments" LF
"    if args.include_stdint == nil then" LF
"        args.include_stdint = false" LF
"    end" LF
"    if args.append_eol == nil then" LF
"        args.append_eol = true" LF
"    end" LF
LF
"    -- Handle args.source_file" LF
"    if args.source_file ~= nil then" LF
"        src_data = am.load_file(args.source_file)" LF
"        ret = ret .. data" LF
"    end" LF
LF
"    -- Handle args.include_stdint" LF
"    if args.include_stdint then" LF
"        ret = ret .. \"#include <stdint.h>\\n#include <stddef.h>\\n\"" LF
"    end" LF
LF
"    -- Handle args.name_of_array" LF
"    if args.name_of_array == nil then" LF
"        error(\"missing argument `name_of_array`.\")" LF
"    end" LF
"    ret = ret .. \"const uint8_t \" .. args.name_of_array .. \" = {\\n\"" LF
"    local print_idx = 1" LF
"    for b in string.gmatch(src_data, '.') do" LF
"        if print_idx == 1 then" LF
"            ret = ret .. \"    \"" LF
"        end" LF
"        ret = ret .. string.format(\"0x%02x,\", string.byte(b))" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"            print_idx = 1" LF
"        else" LF
"            print_idx = print_idx + 1" LF
"        end" LF
"    end" LF
"    if args.append_eol then" LF
"        if print_idx == 16 then" LF
"            ret = ret .. \"\\n\"" LF
"        end" LF
"        ret = ret .. \"0x00\"" LF
"    end" LF
"    ret = ret .. \"\\n};\\n\"" LF
LF
"    -- Handle args.name_of_array_size" LF
"    if args.name_of_array_size ~= nil then" LF
"        ret = ret .. \"const size_t \" .. args.name_of_array_size .. \" = sizeof(\" .. args.name_of_array .. \")\"" LF
"        if args.append_eol then" LF
"            ret = ret .. \" - 1;\\n\"" LF
"        else" LF
"            ret = ret .. \";\\n\"" LF
"        end" LF
"    end" LF
LF
"    return ret" LF
"end" LF
LF
"return {" LF
"    proc = dump_hex_proc," LF
"    desc = " LF
"[[DESCRIPTION:" LF
"    Dump anything into C array." LF
LF
"ATTRIBUTES:" LF
"    \"name_of_array\": [string]" LF
"        The name of dumped array variable." LF
"    \"name_of_array_size\": [string]" LF
"        The name of dumped array size variable. If not specificed, the array" LF
"        size is not generated." LF
"    \"source_file\": [string]" LF
"        The source file to dump. If not specificed, dump amalgamate content as" LF
"        hex array." LF
"    \"include_stdint\": true|false. Default: false." LF
"        Set to true if need to include header file `stdint.h` and `stddef.h`." LF
"    \"append_eol\": true|false. Default: true." LF
"        Whether append NULL terminal character to end of dumped array." LF
"]]," LF
"}" LF
;

#include "c_dump_hex.h"

static int _am_c_dump_hex(lua_State* L)
{
	return am_addon_call_script(L, dump_hex_script, "c:dump_hex.lua");
}

am_addon_t am_addon_c_dump_hex = {
	"c:dump_hex",
	_am_c_dump_hex,
};
