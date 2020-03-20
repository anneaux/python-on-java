// macht, dass Header, die ich in verschiedenen cpp-Dateien (bzw. in einer
// cpp-Datei durch verschiedene Funktionsaufrufe) brauche, insgesamt nur einmal
// eingebunden/angeschaut werden --> one definition rule
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
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
  int height = 600;
  int width = 600;
  float origin_x = 0;
  float origin_y = 0;
  float fov = 4;
  int snakelength = 6;
  int boxlength = 10;
  int linewidth = 2;
  int gridwidth = width / (boxlength + linewidth);
  int gridheight = height / (boxlength + linewidth);
  int startx = gridwidth / 2;
  int starty = gridheight / 2;
  std::random_device rd{};
  std::mt19937 rng{rd()};
  std::uniform_int_distribution<int> distx{0, gridwidth - 1};
  int foodx = distx(rng);
  std::uniform_int_distribution<int> disty{0, gridheight - 1};
  int foody = disty(rng);
  std::uniform_int_distribution<int> distcolor{0, 255};
  sf::RenderWindow window{sf::VideoMode(width, height), "Let's play!"};
};