.PHONY: clean
TARGET = main
HEADERS = game.hpp application.hpp button.hpp
SOURCES = game.cpp application.cpp main.cpp

$(TARGET): $(HEADERS) $(SOURCES)
	g++ -o $(TARGET) $(SOURCES) -I./ -lsfml-graphics -lsfml-window -lsfml-system -std=c++17
	./$(TARGET)

clean:
	rm $(TARGET)
