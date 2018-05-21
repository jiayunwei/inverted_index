all:invert

test_invert:invert.cpp invert.h test_invert.cpp
	g++ -std=c++11 -g invert.cpp test_invert.cpp -o test_invert

invert:invert.cpp invert.h
	g++ -std=c++11 -fPIC -shared -o invert.so invert.cpp

clean:
	rm -rf *.o
