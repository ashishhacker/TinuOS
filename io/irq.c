#include <boot.h>
#include <x86.h>
#include <irq.h>

void irq_remap()
{
	outb(0x11, 0x20);
	outb(0x11, 0xA0);
	outb(0x20, 0x21);
	outb(0x28, 0xA1);
	outb(0x04, 0x21);
	outb(0x02, 0xA1);
	outb(0x01, 0x21);
	outb(0x01, 0xA1);
	outb(0x00, 0x21);
	outb(0x00, 0xA1);
}

void set_irq()
{
	set_idt(32, (u32) irq0, 0x08, 0x8E);
	set_idt(33, (u32) irq1, 0x08, 0x8E);
	set_idt(34, (u32) irq2, 0x08, 0x8E);
	set_idt(35, (u32) irq3, 0x08, 0x8E);
	set_idt(36, (u32) irq4, 0x08, 0x8E);
	set_idt(37, (u32) irq5, 0x08, 0x8E);
	set_idt(38, (u32) irq6, 0x08, 0x8E);
	set_idt(39, (u32) irq7, 0x08, 0x8E);
	set_idt(40, (u32) irq8, 0x08, 0x8E);
	set_idt(41, (u32) irq9, 0x08, 0x8E);
	set_idt(42, (u32) irq10, 0x08, 0x8E);
	set_idt(43, (u32) irq11, 0x08, 0x8E);
	set_idt(44, (u32) irq12, 0x08, 0x8E);
	set_idt(45, (u32) irq13, 0x08, 0x8E);
	set_idt(46, (u32) irq14, 0x08, 0x8E);
	set_idt(47, (u32) irq15, 0x08, 0x8E);
}