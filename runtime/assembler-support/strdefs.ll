; String type for the platform. This header also declares *external* functions (implemented in C code) that are
; used to create, manipulate and manage strings.
%srte.str = type { i32, ptr } ; length in bytes and a byte pointer

; Create a string from a length and pointer of UTF-8 encoded bytes.
declare external %srte.str @_SrCreateUtf8Str_(i32, ptr)

; Create a string from a length and pointer of UTF-16 encoded bytes.
; Also, a third argument: big endian != 0, little endian = 0
declare external %srte.str @_SrCreateUtf16Str_(i32, ptr, i8)

; Create a string from a length and a pointer of UTF-32 encoded bytes.
declare external %srte.str @_SrCreateUtf32Str_(i32, ptr)
