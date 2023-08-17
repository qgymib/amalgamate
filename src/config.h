#ifndef __AMALGAMATE_CONFIG_H__
#define __AMALGAMATE_CONFIG_H__

/**
 * @brief Global amalgamate namespace for Lua
 */
#ifndef AMALGAMATE_NAMESPACE
#define AMALGAMATE_NAMESPACE "am"
#endif

/**
 * @brief Pattern for searching specific code block.
 */
#ifndef AMALGAMATE_PARSER_PATTERN
#define AMALGAMATE_PARSER_PATTERN   \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:BEG\n"         \
    "```(%w+)\n"                    \
    "(.-)\n"                        \
    "```\n"                         \
    " %*/\n"                        \
    "(.-)"                          \
    "/%*%*\n"                       \
    " %* @AMALGAMATE:END\n"         \
    " %*/\n"
#endif

#ifndef AMALGAMATE_DEFAULT_OUTPUT
#define AMALGAMATE_DEFAULT_OUTPUT   ":stdout"
#endif

#ifndef AMALGAMATE_DEFAULT_LOGFILE
#define AMALGAMATE_DEFAULT_LOGFILE  ":stderr"
#endif

#endif
