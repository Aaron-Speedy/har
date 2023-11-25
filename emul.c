#define TB_IMPL
#include "termbox2.h"

#include "op_mask.h"

void print_bits(uint16_t b) {
  for (int j = 15; j >= 0; j--) {
    printf("%u", (b >> j) & 1);
  }
  printf("\n");
}

int main(int argc, char **argv) {
  if (argc != 3) {
    fprintf(stderr, "Invalid paramaters\n");
    fprintf(stderr, "Usage: %s OP_DRIVE DATA_DRIVE\n", argv[0]);

    exit(EXIT_FAILURE);
  }

  int16_t a = 0, b = 0;
  int16_t mem[MAX_16] = { 0 };
  uint16_t ops[MAX_16] = { 0 };
  uint16_t ip = 0;
  int16_t data_drive[MAX_16] = { 0 };
  uint16_t ops_drive[MAX_16] = { 0 };

  FILE *ops_fp = fopen(argv[1], "rb");
  if (ops_fp != NULL) {
    size_t len = fread(ops, sizeof(uint16_t), MAX_16, ops_fp);
    if (ferror(ops_fp) != 0) {
      fprintf(stderr, "Error reading ops drive file\n");
    } else {
      ops[len++] = 0;
    }

    fclose(ops_fp);
  } else {
    fprintf(stderr, "Unable to access ops drive file\n");
  }

  ops_fp = fopen(argv[1], "rb");
  if (ops_fp != NULL) {
    size_t len = fread(ops_drive, sizeof(uint16_t), MAX_16, ops_fp);
    if (ferror(ops_fp) != 0) {
      fprintf(stderr, "Error reading ops drive file\n");
    } else {
      ops_drive[len++] = 0;
    }

    fclose(ops_fp);
  } else {
    fprintf(stderr, "Unable to access ops drive file\n");
  }

  FILE *data_fp = fopen(argv[2], "rb");
  if (data_fp != NULL) {
    size_t len = fread(data_drive, sizeof(uint16_t), MAX_16, data_fp);
    if (ferror(data_fp) != 0) {
      fprintf(stderr, "Error reading data drive file\n");
    } else {
      data_drive[len++] = 0;
    }

    fclose(data_fp);
  } else {
    fprintf(stderr, "Unable to access data drive file\n");
  }

  tb_init();

  while (ops[ip] != 0) {
    int16_t x = a, y;
    uint16_t instr = ops[ip];
    int16_t out = 0;

    if (instr & CON) {
      a = (instr >> 1);
      ip += 1;
      continue;
    }

    if (instr & SRC_B) y = b;
    else y = mem[a];

    if (instr & ZX) x = 0;
    if (instr & NX) x = -x;
    if (instr & ZY) y = 0;
    if (instr & NY) y = -y;
    if (instr & F) out = x + y;
    else out = x & y;
    if (instr & NO) out = ~out;

    if (instr & M) mem[(unsigned) a] = out;
    if (instr & B) b = out;
    if (instr & A) a = out;
    if (instr & O) ops[(unsigned) a] = out;

    int mod = 0;
    if (instr & JP && out > 0) {
      ip = (unsigned) a;
      mod = 1;
    }
    if (instr & JZ && out == 0) {
      ip = (unsigned) a;
      mod = 1;
    }
    if (instr & JN && out < 0) {
      ip = (unsigned) a;
      mod = 1;
    }
    if (!mod) ip += 1;

    /* Devices */

    if (mem[0]) {
      data_drive[(unsigned) mem[1]] = mem[2];
    }

    if (mem[3]) {
      ops_drive[(unsigned) mem[4]] = (unsigned) mem[5];
    }

    read(0, &mem[6], 1);

    if (mem[7]) {
      tb_set_cell(mem[8], mem[9], mem[10], 0, mem[11]);
      tb_present();
    }
  }

  tb_shutdown();

  ops_fp = fopen(argv[1], "wb");
  data_fp = fopen(argv[2], "wb");
  fwrite(ops_drive, sizeof(uint16_t), MAX_16, ops_fp);
  fwrite(data_drive, sizeof(uint16_t), MAX_16, data_fp);
  fclose(ops_fp);
  fclose(data_fp);

  return 0;
}
