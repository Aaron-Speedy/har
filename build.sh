#!/bin/sh

set -xe

CC="${CXX:-cc}"

$CC emul.c -o emul -Wall -ggdb -O3 -std=c99 -pedantic
$CC dump.c -o dump -Wall -ggdb -O3 -std=c99 -pedantic
./dump > run.bin
