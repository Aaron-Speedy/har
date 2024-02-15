# `sintr`
`sintr` is a tiny and unrealistic CPU emulator for fun.

## Quick start (POSIX)
```sh
./build.sh
./emul run.bin drive.bin
```

## Overview
For an overview of the existing architecture, read the code
in `emul.c` and `op_mask.h`!  The code can be extended in
various ways, as is outlined in those files.

For an easy way to write programs for `sintr`, see `dump.c`.

## Why is this public?
I needed to have an additional public repo for a contest
and I didn't want to make public any super unfinished
projects.
