#ifndef OP_MASK_H
#define OP_MASK_H

#define MAX_16 65535

#define CON 1

#define SRC_B 2

typedef enum {
  ZX = 1 << 2,
  NX = 1 << 3,
  ZY = 1 << 4,
  NY = 1 << 5,
  F = 1 << 6,
  NO = 1 << 7,
} ALU_Mask;

typedef enum {
  M = 1 << 8,
  B = 1 << 9,
  A = 1 << 10,
  O = 1 << 11,
} Dest_Mask;

typedef enum {
  JP = 1 << 12,
  JZ = 1 << 13,
  JN = 1 << 14,
} Jump_Mask;

#endif
