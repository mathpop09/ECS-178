output: source.o algo.o
	g++ source.o algo.o -Wno-narrowing -lglut -lGL -o source.out

source.o: source.cpp
	g++ -c -Wno-narrowing source.cpp

algo.o: algo.cpp algo.h
	g++ -c -Wno-narrowing algo.cpp

clean:
	rm *.o source.out
