.PHONY: clean

main: main.cpp application.cpp application.hpp button.hpp game.cpp game.hpp
	g++ -o main main.cpp application.cpp game.cpp -I./ -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
	./main

clean:
	rm main
