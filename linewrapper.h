/**
 *  @file linewrapper.h
 *  @version 0.1.0-dev0
 *  @date Sun Feb 16, 2020 04:51:18 PM CST
 *  @copyright 2019-2020 John A. Crow <crowja@gmail.com>
 *  @license Unlicense <http://unlicense.org/>
 */

#ifndef LINEWRAPPER_H
#define LINEWRAPPER_H

struct linewrapper;

/**
 *  @brief Create and return a new linewrapper object.
 *  @details FIXME longer description here ...
 */
struct linewrapper *lwrap_new(void);

/**
 *  @brief Clean up and free a linewrapper structure.
 *  @details FIXME longer description here ...
 */
void        lwrap_free(struct linewrapper **pp);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */
const char *lwrap_version(void);

/**
 *  @brief Format a string.
 *  @param p Pointer to a linewrapper object.
 *  @param indent Left indent.
 *  @param width Target width for wrapping.
 *  @param str String to format.
 */
char       *lwrap_format(struct linewrapper *p, const unsigned indent,
                         const unsigned width, const char *str);

#endif
