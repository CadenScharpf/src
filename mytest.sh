#!/bin/bash
make
valgrind ./a.out 4 < tests/mytest;