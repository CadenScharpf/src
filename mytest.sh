#!/bin/bash
make
valgrind ./a.out 4 < tests/test01.txt