#!/bin/bash
set -e
g++ -std=c++11 gen_rect_cases.cpp -o gen_rect_cases
./gen_rect_cases
