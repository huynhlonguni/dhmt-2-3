all: main

.PHONY: main


main:
	g++ main.cpp -Iinclude/ -L. -lglut -lopengl32 -o main
	./main