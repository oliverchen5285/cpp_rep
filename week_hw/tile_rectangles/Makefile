.PHONY: all clean test

all: area_wasted pack_rects gen_rect_cases

clean:
	rm -f area_wasted pack_rects gen_rect_cases

test: all
	for F in cases/* ; do cat $$F | ./pack_rects | ./area_wasted; done

CC=g++ -std=c++11 -O2 -g 

area_wasted: area_wasted.cpp base.cpp
	$(CC) -o area_wasted area_wasted.cpp

pack_rects: pack_rects.cpp base.cpp
	$(CC) -o pack_rects pack_rects.cpp

gen_rect_cases: gen_rect_cases.cpp base.cpp
	$(CC) -o gen_rect_cases gen_rect_cases.cpp	
