#ifndef __AMALGAMATE_H__
#define __AMALGAMATE_H__

#include "utils/str.h"
#include "utils/uuid.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Global runtime, named as `amalgamate` in lua.
 */
typedef struct amalgamate_ctx
{
    char**                      filters;        /**< Filter list. */
    size_t                      filter_sz;      /**< Filter list size. */

    amalgamate_str_t            out_path;       /**< Path to output file. */
    FILE*                       out_file;       /**< Output file handle. */

    char**                      files;          /**< File list. */
    size_t                      file_sz;        /**< File list size. */

    /* The current group we are processing during setup. */
    int                         need_help;
    int                         need_list_filters;
    int                         need_verbose;
    char                        errbuf[1024];
} amalgamate_ctx_t;

/**
 * @brief Make a amalgamate context and push it on top of \p L.
 * @param[in] L     Lua VM.
 * @param[in] argc  Command line argument count.
 * @param[in] argv  Command line arguments.
 * @return          Context.
 */
amalgamate_ctx_t* amalgamate_make(lua_State* L, int argc, char* argv[]);

/**
 * @brief Run amalgamate.
 * @param[in] L     Lua VM.
 * @param[in] ctx   Context.
 * @return          Exit code.
 */
int amalgamate_run(lua_State* L, amalgamate_ctx_t* ctx);

#ifdef __cplusplus
}
#endif
#endif
