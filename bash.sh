#!/bin/bash

cat test.asm | cs241.linkasm > output.merl
cs241.linker output.merl print.merl alloc.merl > linked.merl
cs241.merl 0 < linked.merl > test.mips
#mips.array foo.mips
mips.twoints test.mips
