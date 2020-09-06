protect: split.cpp restore.cpp
	g++ -std=c++11 -O2 split.cpp -o split
	g++ -std=c++11 -O2 restore.cpp -o restore
	./split
	./restore
	#I don't know how to run the "restore" recipe (it only checks it when I write "make restore")
restore: restore.cpp
	g++ -std=c++11 -O2 restore.cpp -o restore
	./restore
