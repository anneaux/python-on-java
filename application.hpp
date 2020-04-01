// macht, dass Header, die ich in verschiedenen cpp-Dateien (bzw. in einer
// cpp-Datei durch verschiedene Funktionsaufrufe) brauche, insgesamt nur einmal
// eingebunden/angeschaut werden --> one definition rule
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <game.hpp>
#include <iostream>
#include <list>
#include <random>
#include <vector>

class application {
 public:
  application();
  // das sind die möglichen Aktionen für unsere Klasse = member-functions. die
  // transformieren Elemente aus unserer Klasse in andere Elemente unserer
  // Klasse
  void execute();

 private:
  void process_input();
  void render();
  void failalertwindow();

 private:
  int height = 600;
  int width = 600;
  float origin_x = 0;
  float origin_y = 0;
  float fov = 4;
  int snakelength = 6;
  int boxlength = 10;
  int linewidth = 2;

  std::random_device rd{};
  std::mt19937 rng{rd()};

  std::uniform_int_distribution<int> distcolor{0, 255};
  std::vector<int> foodcolor = {100, 0, 50};
  std::vector<int> snakecolor = {50, 100, 0};
  sf::RenderWindow window{sf::VideoMode(width, height), "Let's play!"};
  game state;
};