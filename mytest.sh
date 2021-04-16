#!/bin/bash
make
valgrind ./a.out 2 < tests/test09.txt