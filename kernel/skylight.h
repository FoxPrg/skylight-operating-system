#ifndef SKYLIGHT_H
#define SKYLIGHT_H

#include <drivers/terminal.h>
#include <drivers/gdt.h>
#include <drivers/idt.h>
#include <drivers/exceptions.h>
#include <drivers/hardware_interrupts.h>
#include <drivers/pit.h>
#include <drivers/acpi.h>
#include <drivers/memory.h>

extern void* SkylightBegin;
extern void* SkylightEnd;

#define KERNEL_CODE_SEGMENT		0x08

#define IVT_BEGIN				0x000
#define IVT_LENGTH				0x400
#define BDA_BEGIN				0x400
#define BDA_LENGTH				0x100
#define KERNEL_BEGIN			((size_t)&SkylightBegin)
#define KERNEL_END				((size_t)&SkylightEnd)
#define KERNEL_LENGTH			(KERNEL_END - KERNEL_BEGIN)
#define EBDA_BEGIN				0xa0000
#define EBDA_LENGTH				0x60000
#define ISA_HOLE_BEGIN			0xf00000
#define ISA_HOLE_LENGTH			0x100000

#endif