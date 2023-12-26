all: main

.PHONY: main


main:
	g++ main.cpp app.cpp -Iinclude/ -L. -lglut -lopengl32 -o main
	./main