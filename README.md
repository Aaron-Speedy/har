# `hemul`
`hemul` is an emulator for the HACK CPU

## Quick start (POSIX)
```sh
./build.sh
./emul run.bin drive.bin
```

## Overview
For an overview of the existing architecture, read the code
in `emul.c` and `op_mask.h`!  The code can be extended in
various ways, as is outlined in those files.

For an easy way to write programs for `hemul`, see `dump.c`.
