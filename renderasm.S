
.syntax unified
.cpu cortex-m0plus
.thumb

#include "pico/asm_helper.S"
#include "hardware/regs/sio.h"

.macro __divider_delay
    // delay 8 cycles
    b 1f
1:  b 1f
1:  b 1f
1:  b 1f
1:
.endm

.section .text

// void get_scales(int z1, int z2, int z3, int* scale);
.global get_scales
.thumb_func
get_scales:
  push {r4, r5, lr}
  ldr r4, =(SIO_BASE)
  movs r5, #128
  lsls r5, #23  // 0x40000000
  str r5, [r4, #SIO_DIV_SDIVIDEND_OFFSET]
  str r0, [r4, #SIO_DIV_SDIVISOR_OFFSET]
  movs r5, #5
  lsls r5, #11  // Display width << 5
    b 1f
1:  b 1f
1:  b 1f
1:
  ldr r0, [r4, #SIO_DIV_QUOTIENT_OFFSET]
  str r1, [r4, #SIO_DIV_SDIVISOR_OFFSET]
  muls r0, r0, r5
  str r0, [r3]
  negs r0, r0
    b 1f
1:  b 1f
1:  
  ldr r0, [r4, #SIO_DIV_QUOTIENT_OFFSET]
  str r2, [r4, #SIO_DIV_SDIVISOR_OFFSET]
  muls r0, r0, r5
  str r0, [r3, #4]
  negs r0, r0
    b 1f
1:  b 1f
1:  
  ldr r0, [r4, #SIO_DIV_QUOTIENT_OFFSET]
  muls r0, r0, r5
  str r0, [r3, #8]
  pop {r4, r5, pc}