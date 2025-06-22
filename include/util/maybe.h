#ifndef UTIL_MAYBE_H
#define UTIL_MAYBE_H

#include "common/common.h"

/**
 * Expands into a maybe-ified name for the type given, as an identifier.  It does so by prefixing the type name with
 * `Maybe_`.
 *
 * ## Example
 *
 * For a `Maybe` type of `int`, one could use:
 *
 * ```c
 * Maybe(int)
 * ```
 *
 * Resulting in:
 *
 * ```c
 * Maybe_int
 * ```
 *
 * The user must assure themself that the type in question was previously defined using `DEF_MAYBE_TYPE_FOR`.
 */
#define Maybe(type)                 \
    Maybe_##type

/**
 * Expands into a **designated struct initializer** for the corresponding Maybe type.
 *
 * The following properties are given:
 *
 * - `isSome` is set to `true`,
 * -`value` is set to the given value.
 *
 * The user must assure themself that the type in question was previously defined using `DEF_MAYBE_TYPE_FOR`.
 */
#define Some(type, givenValue)      \
    (Maybe(type)){                  \
        .isSome = true,             \
        .value = givenValue         \
    }

/**
 * Expands into a **designated struct initializer** for the Maybe type with the following properties:
 *
 * - `isSome` is set to `false`
 * - `value` is intentionally undefined.  Accessing it may cause undefined behavior.
 *
 * The user must assure themself that the type in question was previously defined using `DEF_MAYBE_TYPE_FOR`.
 */
#define None(type)                  \
    (Maybe(type)){                  \
        .isSome = false             \
    }

/**
 * Expands into a **Maybe struct definition** for the given type.
 *
 * Maybe structs are defined as follows:
 *
 * ```c
 * typedef struct {
 *     bool isSome;
 *     {type} value;
 * } Maybe_{type};
 * ```
 *
 * Where `{type}` refers to the type given.
 */
#define DEF_MAYBE_TYPE_FOR(type)    \
    typedef struct {                \
        bool isSome;                \
        type value;                 \
    } Maybe(type)


#endif
