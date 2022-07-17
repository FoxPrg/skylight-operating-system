#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define DeclareAssembly(...)			__asm__ __volatile__(__VA_ARGS__)
#define DeclareAttribute(...)			__attribute__((__VA_ARGS__))
#define AlignUp(__value, __alignment)	(((__value) + (__alignment) - 1) & ~((__alignment) - 1))
#define AlignDown(__value, __alignment)	((__value) & ~((__alignment) - 1))

typedef char int8_t, *pint8_t;
typedef unsigned char uint8_t, byte_t, *puint8_t, *pbyte_t;
typedef short int16_t, *pint16_t;
typedef unsigned short uint16_t, word_t, *puint16_t, *pword_t;
typedef int int32_t, *pint32_t;
typedef unsigned int uint32_t, dword_t, *puint32_t, *pdword_t;
typedef long long int64_t, *pint64_t;
typedef unsigned long long uint64_t, qword_t, *puint64_t, *pqword_t;
typedef long int decimal_t, *pdecimal_t;
typedef long unsigned int size_t, *psize_t;

#endif