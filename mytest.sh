#!/bin/bash
make
valgrind ./a.out 3 < tests/test01.txt