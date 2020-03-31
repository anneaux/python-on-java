.PHONY: clean

main: main.cpp application.cpp application.hpp button.hpp
	g++ -o main main.cpp application.cpp -I./ -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
	./main

clean:
	rm main
