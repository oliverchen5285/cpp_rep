#!/bin/bash
while true
do
	g++ -std=c++11 cd3_main.cpp cd3_main_test.cpp cd3_bf.cpp cd3_sh.cpp cd3_qt.cpp -o cd3
	if [ $? == 0 ]
	then
		./cd3
	fi
	sleep 15
done
