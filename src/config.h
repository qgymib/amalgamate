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
#ifndef AMALGAMATE_PATTERN
#define AMALGAMATE_PATTERN      \
    "/\\*\\*\\n"                \
    " \\* @AMALGAMATE:BEG\\n"   \
    "```(\\w+)\\n"              \
    "([\\w\\W]*?)\\n"           \
    "```\\n"                    \
    " \\*/\\n"                  \
    "([\\w\\W]*?)\\n"           \
    "/\\*\\*\\n"                \
    " \\* @AMALGAMATE:END\\n"   \
    " \\*/"
#endif

#endif
