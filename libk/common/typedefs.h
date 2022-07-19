#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define ALIGN_UP(__value, __alignment)		(((__value) + (__alignment) - 1) & ~((__alignment) - 1))
#define ALIGN_DOWN(__value, __alignment)	((__value) & ~((__alignment) - 1))

#ifdef __attribute__
#define PACKED	__attribute__((packed))
#else
#define PACKED	__declspec(align(1))
#endif

#ifdef __asm__
#define ASSEMBLY(...)	__asm__ __volatile__(__VA_ARGS__)
#else
#define ASSEMBLY(...)
#endif

typedef char int8_t, *pint8_t;
typedef unsigned char uint8_t, *puint8_t;
typedef short int16_t, *pint16_t;
typedef unsigned short uint16_t, *puint16_t;
typedef int int32_t, *pint32_t;
typedef unsigned int uint32_t, *puint32_t;
typedef long long int64_t, *pint64_t;
typedef unsigned long long uint64_t, *puint64_t;
typedef long int decimal_t, *pdecimal_t;
typedef long unsigned int size_t, *psize_t;

#endif