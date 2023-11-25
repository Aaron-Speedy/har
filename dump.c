#include <unistd.h>
#include <stdint.h>

#include "op_mask.h"

#define SET_A(c) (CON | (c << 1))

#define OUT_B (SRC_B | ZX | F)
#define OUT_M (ZX | F)
#define OUT_A (ZY | F)

int main(void) {
  uint16_t ops[] = {
    // Break if read is 'q'
    //
  };
  write(1, ops, sizeof(ops));

  return 0;
}
