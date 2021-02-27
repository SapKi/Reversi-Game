a.out: compileAll
	g++ *.o -o ../../exe/server.out -pthread
	rm -f *.o

compileAll: src/*.h src/*.cpp
	g++ -c src/*.cpp
