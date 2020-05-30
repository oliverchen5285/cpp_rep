#!/bin/bash

g++ -std=c++11 cd3_base.cpp cd3_bf.cpp cd3_sh.cpp cd3_qt.cpp cd3_main.cpp -o cd3
if [ $? == 0 ]
then
  ./cd3
fi
