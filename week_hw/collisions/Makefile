compile:
	g++ -std=c++11 cd3_base.cpp cd3_bf.cpp cd3_sh.cpp cd3_qt.cpp cd3_main.cpp -o cd3 >& tt

compile_test:
	g++ -std=c++11 cd3_base.cpp cd3_bf.cpp cd3_sh.cpp cd3_qt.cpp cd3_all_test.cpp -o cd3 >& tt

run:
	./cd3

watch:
	fswatch -e ".*" -i "\\.cpp" -i "\\.h" -0 -o -l 10 . | xargs -0 -n1 -I{} go.sh &
