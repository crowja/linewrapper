/**
 *  @file linewrapper.h
 *  @version 0.0.2-dev0
 *  @date Thu Nov  1 08:19:13 CDT 2018
 *  @copyright %COPYRIGHT%
 *  @brief FIXME
 *  @details FIXME
 */

#ifndef _LINEWRAPPER_H_
#define _LINEWRAPPER_H_

#ifdef  _PACKAGE_NAME
#undef  _PACKAGE_NAME
#endif
#define _PACKAGE_NAME "linewrapper"

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

void        lwrap_free(struct linewrapper *p);

/**
 *  @brief Return the version of this package.
 *  @details FIXME longer description here ...
 */

const char *lwrap_version(void);

/**
 *  @brief Initialize a linewrapper object.
 *  @details FIXME longer description here ...
 *  @param p Pointer to a linewrapper object
 *  @param x FIXME
 */

char       *lwrap_format(struct linewrapper *p, const unsigned indent,
                         const unsigned width, const char *str);

#endif
