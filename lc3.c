#include <stdio.h>
#include <stdint.h>
#include <signal.h>
/* unix only */
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/termios.h>
#include <sys/mman.h>


/* 
* Registers
* A register is a slot for storing a single value on the CPU. Registers are like the “workbench” of the CPU. 
* For the CPU to work with a piece of data, it has to be in one of the registers.
* The LC-3 has 10 total registers, each of which is 16 bits.
*/
enum
{
    R_R0 = 0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC, /* program counter */
    R_COND, /* condition flags */
    R_COUNT
};


/*
* Condition Flags
* The R_COND register stores condition flags which provide information about the most recently executed calculation. 
* This allows programs to check logical conditions such as if (x > 0) { ... }.
* Note: (The << symbol is called the left bitshift operator. (n << k) shifts the bits of n to the left k places. Thus 1 << 2 will equal 4.)
* https://learn.microsoft.com/en-us/cpp/cpp/left-shift-and-right-shift-operators-input-and-output?redirectedfrom=MSDN&view=msvc-170
*/
enum
{
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

uint16_t reg[R_COUNT];


/* 
* Memory Storage
* 65536 locations (the maximum that is addressable by a 16-bit unsigned integer 2^16) 
*/
#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX];  


/*
* Instruction Set (Opcodes)
* An instruction is a command which tells the CPU to do some fundamental task, such as add two numbers.
* Each opcode represents one task that the CPU “knows” how to do. 
* There are just 16 opcodes in LC-3.
*/
enum
{
    OP_BR = 0, /* branch */
    OP_ADD,    /* add  */
    OP_LD,     /* load */
    OP_ST,     /* store */
    OP_JSR,    /* jump register */
    OP_AND,    /* bitwise and */
    OP_LDR,    /* load register */
    OP_STR,    /* store register */
    OP_RTI,    /* unused */
    OP_NOT,    /* bitwise not */
    OP_LDI,    /* load indirect */
    OP_STI,    /* store indirect */
    OP_JMP,    /* jump */
    OP_RES,    /* reserved (unused) */
    OP_LEA,    /* load effective address */
    OP_TRAP    /* execute trap */
};


/*
* Procedure
* 1. Load one instruction from memory at the address of the PC register.
* 2. Increment the PC register.
* 3. Look at the opcode to determine which type of instruction it should perform.
* 4. Perform the instruction using the parameters in the instruction.
* 5. Go back to step 1.
*/
int main(int argc, const char* argv[])
{
    /* handle command line input to make our program usable */
    if (argc < 2) {
            /* show usage string */
            printf("lc3 [image-file1] ...\n");
            exit(2);
        }

        for (int j = 1; j < argc; ++j) {
            if (!read_image(argv[j]))
            {
                printf("failed to load image: %s\n", argv[j]);
                exit(1);
            }
        }

    /* Setup commands: properly handle input to the terminal */
    signal(SIGINT, handle_interrupt);
    disable_input_buffering();

    /* since exactly one condition flag should be set at any given time, set the Z flag */
    reg[R_COND] = FL_ZRO;

    /* set the PC to starting position */
    /* 0x3000 is the default */
    enum { PC_START = 0x3000 };
    reg[R_PC] = PC_START;

    int running = 1;
    while (running)
    {
        /* FETCH */
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op)
        {
            case OP_ADD:
                // @{ADD}
                break;
            case OP_AND:
                // @{AND}
                break;
            case OP_NOT:
                // @{NOT}
                break;
            case OP_BR:
                // @{BR}
                break;
            case OP_JMP:
                // @{JMP}
                break;
            case OP_JSR:
                // @{JSR}
                break;
            case OP_LD:
                // @{LD}
                break;
            case OP_LDI:
                // @{LDI}
                break;
            case OP_LDR:
                // @{LDR}
                break;
            case OP_LEA:
                // @{LEA}
                break;
            case OP_ST:
                // @{ST}
                break;
            case OP_STI:
                // @{STI}
                break;
            case OP_STR:
                // @{STR}
                break;
            case OP_TRAP:
                // @{TRAP}
                break;
            case OP_RES:
            case OP_RTI:
            default:
                // @{BAD OPCODE}
                break;
        }
    }
    // @{Shutdown}
}