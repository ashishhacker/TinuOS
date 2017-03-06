#include <boot.h>

tss_entry_t tss_entry;

struct gdt_entry {
		unsigned char base_high;
		unsigned char granularity;
		unsigned char access;
		unsigned char base_middle;
		unsigned short base_low;
		unsigned short limit_low;
} __attribute__((packed));

/* GDT pointer which points to our gdt structure */
struct gdt_ptr {
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

struct gdt_entry gdt[3];
struct gdt_ptr gt;

void set_gdt(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned granularity)
{
	gdt[num].base_low = (base & 0xFFFF);
	gdt[num].base_middle = (base >> 16) & 0xFF;
	gdt[num].base_high = (base >> 24) & 0xFF;

	gdt[num].limit_low = (limit & 0xFFFF);

	gdt[num].access = access;

	/* granularity bit is from 16-24 */
	gdt[num].granularity = (limit >> 16) & 0x0F;
	gdt[num].granularity |= (granularity & 0xF0);
}

static void set_tss(int num, u16 ss0, u32 esp0)
{
	unsigned long base;
	unsigned long limit;

	/* address of tss */
	base = (unsigned long)tss_entry;
	limit = base + sizeof(tss_entry);

	/* Add tss descriptor to gdt */
	set_gdt(3, base, limit, 0xE9, 0xCF);

	memset(&tss_entry, 0, sizeof(tss_entry));

	tss_entry.ss0 = ss0;
	tss_entry.esp0 = esp0;

	tss_entry.cs = 0x0b;
	tss_entry.ss = 
	tss_entry.ds = 
	tss_entry.es = 
	tss_entry.fs = 
	tss_entry.gs = 0x13;
	tss_entry.iomap_base = sizeof(tss_entry);
}

void gdt()
{
	gt.limit = (sizeof(struct gdt_entry)*3)-1;
	gt.base = (unsigned int)&gdt;

	set_gdt(0, 0, 0, 0, 0);
	set_gdt(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	set_gdt(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	set_tss(3, 0x10, 0);

	gdt_flush();
	tss_flush();
}

void set_kernel_stack(unsigned long stack)
{
	tss_entry.esp0 = stack;
}