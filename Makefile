
sort: sort.o
	g++ -g sort.o -o sort

sort.o: sort.cpp
	g++ -g -mavx2 -c sort.cpp

clean:
	rm sort *.o
