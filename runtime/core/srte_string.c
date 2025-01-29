#include "srte_string.h"
#include "own.h"
#include "rtalias.h"
#include <stdio.h>
#include <stdlib.h>
#include <unicode/urename.h>
#include <unicode/ustring.h>
#include <unicode/utf8.h>
#include <unicode/utypes.h>

static SrStr SrCreateUtf8Str(uint32_t len, uint8_t *bytes) {
    UErrorCode errc = U_ZERO_ERROR;
    u_strFromUTF8(NULL, 0, NULL, (const char *)bytes, len, &errc);

    // Because the output buffer is NULL (pre-flighting) the error code changes to something
    // that still indicates an error but our function call was semantically valid according to
    // ICU documentation. So cannot check for U_SUCCESS(errc) here.
    if (errc == U_INVALID_CHAR_FOUND) {
        // For now, we abort.
        fprintf(stderr, "Invalid UTF-8 data: %s\n", u_errorName(errc));
        abort();
    }

    return (SrStr){.bytes = TAKE_N(uint8_t, len, bytes), .len = len};
}

static SrStr SrCreateUtf16Str(uint32_t len, uint16_t *bytes, uint8_t is_be) {
    // Pre-flight the string length
    int32_t utf8_len;
    UErrorCode errc;
    u_strToUTF8(NULL, 0, &utf8_len, bytes, len, &errc);

    if (!U_SUCCESS(errc) || errc != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "Error transforming UTF-16: %s\n", u_errorName(errc));
        abort();
    } else {
        errc = U_ZERO_ERROR;
    }

    // Now do the actual transformation
    uint8_t *dst_buf = malloc(sizeof(uint8_t) * utf8_len);
    u_strToUTF8((char *)dst_buf, utf8_len, NULL, bytes, len, &errc);

    return (SrStr){.bytes = TAKE_N(uint8_t, utf8_len, dst_buf), .len = len};
}

static SrStr SrCreateUtf32Str(uint32_t len, uint32_t *bytes) {
    // Again, pre-flight the string length
    int32_t utf16_len;
    UErrorCode errc;
    u_strFromUTF32(NULL, 0, &utf16_len, (const UChar32 *)bytes, len, &errc);

    if (!U_SUCCESS(errc) || errc != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "Error transforming UTF-32: %s\n", u_errorName(errc));
        abort();
    } else {
        errc = U_ZERO_ERROR;
    }

    // Now transform to UTF-16
    UChar *dst_buf = malloc(sizeof(UChar) * utf16_len);
    int32_t real_utf16_len; // since passing to CreateUtf16Str
    u_strFromUTF32(dst_buf, utf16_len, &real_utf16_len, (const UChar32 *)bytes, len, &errc);

    // Do another check since another conversion will come
    if (!U_SUCCESS(errc) || errc != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "Error transforming UTF-32: %s\n", u_errorName(errc));
        abort();
    } else {
        errc = U_ZERO_ERROR;
    }

    // Now make the 16 -> 8 transformation
    return SrCreateUtf16Str(real_utf16_len, dst_buf, 0);
}

/* Internal defintions as specified in strdefs.ll */

SR_STRONG_ALIAS(SrStr, _SrCreateUtf32Str_, SrCreateUtf32Str, uint32_t len, uint32_t *bytes);
SR_STRONG_ALIAS(SrStr, _SrCreateUtf16Str_, SrCreateUtf16Str, uint32_t len, uint16_t *bytes, uint8_t is_be);
SR_STRONG_ALIAS(SrStr, _SrCreateUtf8Str_, SrCreateUtf8Str, uint32_t len, uint8_t *bytes);
