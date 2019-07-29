# Declare constants for the multiboot header.
.set ALIGN,    1<<0                       # align loaded modules on page boundaries
.set MEMINFO,  1<<1                       # provide memory map
.set VIDMODE,  1<<2                       # set up video mode
.set FLAGS,    ALIGN | MEMINFO | VIDMODE  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

.set WIDTH, 1024
.set HEIGHT, 768
.set BPP,     32
.set TEXT,     0

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM
.long 0
.long 0
.long 0
.long 0
.long 0
.long TEXT
.long WIDTH
.long HEIGHT
.long BPP

# Reserve a stack for the initial thread.
.section .bss
.align 16
stack_bottom:
.skip 16777216 # 16 MiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	movl $stack_top, %esp

	# Call the global constructors.
	call _init

	# Provide the Multiboot structure into the main kernel.
	push %ebx

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
1:	hlt
	jmp 1b
.size _start, . - _start
