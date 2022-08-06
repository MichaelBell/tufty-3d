
.syntax unified
.cpu cortex-m0plus
.thumb

#include "pico/asm_helper.S"
#include "hardware/regs/sio.h"

.section .time_critical.rendering

// void project_vertices(int* v, int* w);
.global project_vertices
.thumb_func
project_vertices:
  push {r4, r5, r6, r7, lr}
  movs r2, #13
  lsls r2, #28  // SIO_BASE
  movs r3, #128
  lsls r3, #23  // 0x40000000
  str r3, [r2, #SIO_DIV_SDIVIDEND_OFFSET]
  ldr r3, [r0, #8]
  str r3, [r2, #SIO_DIV_SDIVISOR_OFFSET]
  movs r5, #5
  lsls r5, #11
  mov ip, r1
  ldmia r0!, {r3, r4}
  ldr r7, [r0, #12]
  ldr r1, [r2, #SIO_DIV_QUOTIENT_OFFSET]
  str r7, [r2, #SIO_DIV_SDIVISOR_OFFSET]
  muls r1, r5

  // r0 = &v[0].z
  // r1 = scale[0]
  // r2 = SIO_BASE
  // r3 = v[0].x
  // r4 = v[0].y

  // Multiply a = v[0].x * scale
  asrs r6, r3, #15 // ah
  lsls r3, r3, #17
  lsrs r3, r3, #17 // al
  asrs r7, r1, #15 // bh
  movs r2, r1
  lsls r1, r1, #17
  lsrs r1, r1, #17 // bl
  movs r5, r1
  muls r5, r3  // al * bl
  muls r1, r6  // ah * bl
  muls r3, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r3, r3, r1
  asrs r3, r3, #3
  adds r3, r3, r5
  lsls r6, #12
  adds r3, r3, r6
  
  // Multiply a = v[0].y * -scale
  negs r2, r2
  asrs r6, r4, #15 // ah
  lsls r4, r4, #17
  lsrs r4, r4, #17 // al
  asrs r7, r2, #15 // bh
  lsls r1, r2, #17
  lsrs r1, r1, #17 // bl
  movs r5, r1
  muls r5, r4  // al * bl
  muls r1, r6  // ah * bl
  muls r4, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r4, r4, r1
  asrs r4, r4, #3
  adds r4, r4, r5
  lsls r6, #12
  adds r4, r4, r6

  // r0 = &v[0].z
  // r3 = v[0].x * scale
  // r4 = v[0].y * -scale

  mov r1, ip
  movs r2, #13
  lsls r2, #28  // SIO_BASE
  movs r5, #15
  lsls r5, #21  // half screen height (fixed point)
  adds r4, r4, r5

  movs r5, #5
  lsls r5, #23  // half screen width (fixed point)
  adds r3, r3, r5
  stmia r1!, {r3, r4}

  ldr r3, [r0, #24]
  ldr r1, [r2, #SIO_DIV_QUOTIENT_OFFSET]
  str r3, [r2, #SIO_DIV_SDIVISOR_OFFSET]
  
  lsrs r5, #12
  muls r1, r5
  ldr r3, [r0, #4]

  // r0 = &v[0].z
  // r1 = scale[1]
  // r2 = SIO_BASE
  // r3 = v[1].x

  // Multiply a = v[1].x * scale
  asrs r6, r3, #15 // ah
  lsls r3, r3, #17
  lsrs r3, r3, #17 // al
  asrs r7, r1, #15 // bh
  lsls r4, r1, #17
  lsrs r4, r4, #17 // bl
  movs r5, r4
  muls r5, r3  // al * bl
  muls r4, r6  // ah * bl
  muls r3, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r3, r3, r4
  asrs r3, r3, #3
  adds r3, r3, r5
  lsls r6, #12
  adds r3, r3, r6

  // Multiply a = v[1].y * -scale
  negs r1, r1
  ldr r4, [r0, #8]
  asrs r6, r4, #15 // ah
  lsls r4, r4, #17
  lsrs r4, r4, #17 // al
  asrs r7, r1, #15 // bh
  lsls r1, r1, #17
  lsrs r1, r1, #17 // bl
  movs r5, r1
  muls r5, r4  // al * bl
  muls r1, r6  // ah * bl
  muls r4, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r4, r4, r1
  asrs r4, r4, #3
  adds r4, r4, r5
  lsls r6, #12
  adds r4, r4, r6

  // r0 = &v[0].z
  // r2 = SIO_BASE
  // r3 = v[1].x * scale
  // r4 = v[1].y * -scale

  mov r1, ip
  movs r5, #15
  lsls r5, #21  // half screen height (fixed point)
  adds r4, r4, r5
  str r4, [r1, #12]

  movs r5, #5
  lsls r5, #23  // half screen width (fixed point)
  adds r3, r3, r5
  str r3, [r1, #8]

  ldr r1, [r2, #SIO_DIV_QUOTIENT_OFFSET]

  lsrs r5, #12
  muls r1, r5
  ldr r3, [r0, #16]

  // r0 = &v[0].z
  // r1 = scale[2]
  // r2 = SIO_BASE
  // r3 = v[2].x

  // Multiply a = v[2].x * scale
  asrs r6, r3, #15 // ah
  lsls r3, r3, #17
  lsrs r3, r3, #17 // al
  asrs r7, r1, #15 // bh
  lsls r4, r1, #17
  lsrs r4, r4, #17 // bl
  movs r5, r4
  muls r5, r3  // al * bl
  muls r4, r6  // ah * bl
  muls r3, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r3, r3, r4
  asrs r3, r3, #3
  adds r3, r3, r5
  lsls r6, #12
  adds r3, r3, r6

  // Multiply a = v[2].y * -scale
  negs r1, r1
  ldr r4, [r0, #20]
  asrs r6, r4, #15 // ah
  lsls r4, r4, #17
  lsrs r4, r4, #17 // al
  asrs r7, r1, #15 // bh
  lsls r1, r1, #17
  lsrs r1, r1, #17 // bl
  movs r5, r1
  muls r5, r4  // al * bl
  muls r1, r6  // ah * bl
  muls r4, r7  // al * bh
  muls r6, r7  // ah * bh
  lsrs r5, r5, #18
  adds r4, r4, r1
  asrs r4, r4, #3
  adds r4, r4, r5
  lsls r6, #12
  adds r4, r4, r6

  // r0 = &v[0].z
  // r2 = SIO_BASE
  // r3 = v[2].x * scale
  // r4 = v[2].y * -scale

  mov r0, ip
  movs r5, #15
  lsls r5, #21  // half screen height (fixed point)
  adds r4, r4, r5
  str r4, [r0, #20]

  movs r5, #5
  lsls r5, #23  // half screen width (fixed point)
  adds r3, r3, r5
  str r3, [r0, #16]

  // is_back_face
  ldmia r0!, {r1, r2, r5, r6}
  subs r3, r3, r1  // a.x
  subs r4, r4, r2  // a.y
  subs r5, r5, r1  // b.x
  subs r6, r6, r2  // b.y

  // Multiply a.x * b.y
  asrs r2, r3, #15 // ah
  lsls r3, r3, #17
  lsrs r3, r3, #17 // al
  asrs r7, r6, #15 // bh
  lsls r6, r6, #17
  lsrs r6, r6, #17 // bl
  movs r1, r6
  muls r1, r3  // al * bl
  muls r6, r2  // ah * bl
  muls r3, r7  // al * bh
  muls r2, r7  // ah * bh
  lsrs r1, r1, #18
  adds r3, r3, r6
  asrs r3, r3, #3
  adds r3, r3, r1
  lsls r2, #12
  adds r3, r3, r2  

  // Multiply a.y * b.x
  asrs r2, r4, #15 // ah
  lsls r4, r4, #17
  lsrs r4, r4, #17 // al
  asrs r7, r5, #15 // bh
  lsls r5, r5, #17
  lsrs r5, r5, #17 // bl
  movs r1, r5
  muls r1, r4  // al * bl
  muls r5, r2  // ah * bl
  muls r4, r7  // al * bh
  muls r2, r7  // ah * bh
  lsrs r1, r1, #18
  adds r4, r4, r5
  asrs r4, r4, #3
  adds r4, r4, r1
  lsls r2, #12
  adds r4, r4, r2

  // I don't understand this, but apparently it does >=
  asrs r1, r4, #31
  lsrs r0, r3, #31
  cmp r4, r3
  adcs r0, r1
  uxtb r0, r0
  
  pop {r4, r5, r6, r7, pc}