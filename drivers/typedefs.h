#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#define DeclareAssembly(...)			__asm__ __volatile__(__VA_ARGS__)
#define DeclareAttribute(...)			__attribute__((__VA_ARGS__))
#define AlignUp(__value, __alignment)	(((__value) + (__alignment) - 1) & ~((__alignment) - 1))
#define AlignDown(__value, __alignment)	((__value) & ~((__alignment) - 1))

typedef char CHAR, INT8, *PCHAR, *PINT8;
typedef unsigned char UCHAR, UINT8, BYTE, *PUCHAR, *PUINT8, *PBYTE;
typedef short SHORT, INT16, *PSHORT, *PINT16;
typedef unsigned short USHORT, UINT16, WORD, *PUSHORT, *PUINT16, *PWORD;
typedef int INT, INT32, *PINT, *PINT32;
typedef unsigned int UINT, UINT32, DWORD32, *PUINT, *PUINT32, *PDWORD32;
typedef long long LONGLONG, INT64, *PLONGLONG, *PINT64;
typedef unsigned long long ULONGLONG, UINT64, DWORD64, QWORD, *PULONGLONG, *PUINT64, *PDWORD64, *PQWORD;
typedef long int LONG, ARCH_T, *PLONG, *PARCH_T;
typedef long unsigned int ULONG, DWORD, SIZE_T, *PULONG, *PDWORD, *PSIZE_T;
typedef void VOID, *PVOID;

#define EXTERN_C	extern "C"

#endif