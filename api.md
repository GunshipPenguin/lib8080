# lib8080 API

This file contains a complete reference of lib8080's external API.

## Getting Started

Include `i8080.h` in your project and compile `i8080.c` with the rest of your
source files.

```C
#include "i8080.h"
```

## Creating an emulated 8080

You'll mainly be working with an `i8080` struct when using lib8080, which
has all the information in it needed to represent an Intel 8080 CPU.

```C
struct i8080 *cpu = malloc(sizeof(struct i8080));
```

The layout of the `i8080` struct is as follows:

```C
struct i8080 {
  /* General purpose registers (8 bits) */
  uint A, B, C, D, E;

  /* High and low address registers (8 bits) */
  uint H, L;

  /* 8080 status flags (8 bits) */
  uint flags;

  /* Stack pointer (16 bits) */
  uint SP;

  /* Program counter (16 bits) */
  uint PC;

  /* Is the CPU currently halted? (see HLT instruction) (boolean) */
  int halted;

  /* Pointer to memory */
  char *memory;

  /* Size of memory in bytes */
  size_t memsize;

  /* Interrupt enable/disable flag (boolean) */
  int INTE;

  /* Does the CPU have a pending interrupt? (boolean) */
  int pending_interrupt;

  /* If the CPU does have a pending interrupt, what is the address placed
   * on the data bus by the interrupting device? (8 bits)
   */
  uint interrupt_opcode;

  /* IO handling callbacks (see section below) */
  i8080_in_handler input_handler;
  i8080_out_handler output_handler;

  /* Number of CPU cycles since reset_cpu was last called */
  uint cyc;
};
```

Generally, `uint` is used to represent CPU data and addresses, while `int` is
used to represent boolean values.

## Initializing the CPU

The `i8080_reset` function resets the i8080 struct to a powered on state.

```C
reset_cpu(cpu);
```

## Loading Memory

lib8080 handles memory a character array. Memory is allocated separately to
the i8080 struct. Additionally, the `memsize` property of the i8080 struct must
be set to the size of the character array for internal use by lib8080.

```C
/* Load 32 KiB of memory */
cpu->memory = malloc(sizeof(char) * 32768)
cpu->memsize = 2**32;
```

Memory can then be initialized from a file using the `i8080_load_memory`
convenience function.

```C
/* Load the entirety of PROGRAM.COM into memory at offset 0x100 */
i8080_load_memory(cpu->memory, "PROGRAM.COM", 0x100);
```

## Reading and Writing Memory

Individual bytes of memory can be read/read using the `i8080_read_byte` and
`i8080_write_byte` functions.

```C
/* Write 0xFF to memory at address 0x100 */
i8080_write_byte(cpu, 0x100, 0xFF);

char byte = i8080_read_byte(cpu, 0x100);
/* byte now contains 0xFF */
```

Since the 8080 uses a little endian architechure, you can use the
`i8080_read_word` and `i8080_write_word` convenience functions to write 2 byte
words low byte first.

```C
/* Write 0x34 to address 0x100 and 0x12 to address 0x101 */
i8080_write_word(0x100, 0x1234);

uint *word = i8080_read_word(cpu, 0x100);
/* word now contains 0x1234 */
```

## Executing Instructions

Use the `i8080_step` function to execute a single instruction.

```C
i8080_step(cpu);
```

Note that if there is a pending interrupt, the opcode provided by the
interrupting device will be executed instead of the opcode pointed to by the
program counter.

Also note that if the CPU is halted, `i8080_step` will do nothing.

## Setting and Getting CPU Flags

The 8080 has five status flags: sign, zero, auxiliary carry, parity and carry.
These flags are stored in the `flags` property of the `i8080` struct in the same
order they are pushed to the stack by the `PUSH PSW` instruction, specifically:

```
bit 7                   bit 0
|                           |
v                           v
S   Z   0   A   0   P   1   C
```

Note that bit 1 is always set (equal to 1), and bits 3 and 5 are always reset
(equal to 0).

To see if a flag is set, you can check directly against the `flags` resister,
but you'll probably find it easier to use the `i8080_set_flag` and
`i8080_get_flag` convenience functions.

```C
/* Reset all flags */
cpu->flags = 0x02;

/* Set the zero flag */
i8080_set_flag(cpu, FLAG_Z, 1);
/* cpu->flags now equals 0x42 */

int z_flag_set = i8080_get_flag(cpu, FLAG_Z);
/* z_flag_set is now 1 */
```

## Manipulating the Stack

If you need to push data to or pop data from the stack outside normal
instruction execution, you can use the `i8080_push_stackb` and
`i8080_pop_stackb` functions to push or pop a single byte to or from the stack.

```C
/* Set cpu->SP to a sane value */
i8080_push_stackb(cpu, 0xFF);
char *data = i8080_pop_stackb(cpu);
/* data now contains 0xFF */
```

Since the 8080 uses a little endian architecture, `i8080_push_stackw` and
`i8080_pop_stackw` convenience functions are provided to do the same thing with
2 byte words using the proper byte ordering.

```C
i8080_push_stackw(cpu, 0x1234);

uint *data = i8080_pop_stackw(cpu);
/* data now contains 0x1234 */
```

## Requesting interrupts

An interrupt can be requested using the `i8080_request_interrupt` function.

```C
i8080_request_interrupt(cpu, I8080_RST_0);
```

Provided the `INTE` flag was true in the cpu struct, the next time
`i8080_set_flag` is called on cpu, the instruction `RST 0` will be executed
instead of whatever `cpu->PC` points to.

Note that the second argument is the opcode to place on the 8080's data bus.
While this can be any value in the range `0x00` - `0xFF`, in practise, it's
almost always going to be one of the `RST` (restart) instructions. Because of
this, lib8080 provides the macros `I8080_RST_[0-7]`, which expand to the opcodes
for each `RST` instruction.

## Hooking IN and OUT instructions

The 8080 provides two instructions for interfacing with external devices, `IN`
(input) and `OUT` (output). When an `IN` instruction is executed, the device
number to read from is placed on the 8080's address bus, the cpu's DBIN (data
bus in) line is pulled high, and one byte is read from the 8080's data bus into
the accumulator.

Similarity, when when an `OUT` instruction is executed, the contents of the
accumulator are placed on the 8080's data bus, the cpu's WR (write) line is
pulled low (WR is active low) and the device number to write to is placed on the
address bus.

lib8080 emulates this functionality using function pointers. If the
`cpu->input_handler` and `cpu->output_handler` properties of an i8080 struct are
not `NULL` when an `IN` or `OUT` instruction is executed, these callback
functions will be invoked to handle input or output of data respectively.

As a simple example, here's how you could emulate a device that always writes
the byte 0x12 on IO port 0 and reads the latest byte written on IO port 0 into
to a global variable.

```C
uint last_byte_written;

uint handle_input(struct i8080 *cpu, uint dev) {
  if (dev == 0) {
    return 0x12; /* Return the byte 0x12 to the cpu */
  } else {
    /* Handle other devices */
  }
}

void handle_output(struct i8080 *cpu, uint dev, uint val) {
  if (dev == 0) {
    last_byte_written = val;
  } else {
    /* Handle other devices */
  }
}

/* Initialize i8080 cpu struct and memory */

cpu->input_handler = handle_input;
cpu->output_handler = handle_output;
```

In the above example:

- Whenever an `IN` instruction is executed, the `handle_input` function will be
  invoked with the i8080 struct that executed the instruction, the device number
  and the contents of the 8080's accumulator. You can call emulation
  code for your external device here. The 8080's accumulator will be set to the
  value returned.

- Whenever an `OUT` instruction is executed, the `handle_output` function will
  be invoked with the i8080 struct that executed the instruction, the device
  number and contents of the 8080's accumulator. You can call emulation code for
  your external device here.
