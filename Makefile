all: 
	g++ -o main src/main.cpp -lglut -lGLU -lGL -lm
main:
	g++ -o main src/main.cpp -lglut -lGLU -lGL -lm
clean:
	rm main
run:
	./main