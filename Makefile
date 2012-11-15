all: clean
	g++ parse.cpp -o parse
	cc error.c -o error
	g++ -c types.cpp -o types.o
clean:
	rm -rf parse
	rm -rf out
	rm -rf types.o
