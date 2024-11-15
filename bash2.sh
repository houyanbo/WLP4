#!/bin/bash

cat foo.wlp4 | wlp4scan | wlp4parse | ./wlp4gen > foo.asm
