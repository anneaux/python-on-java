// macht, dass Header, die ich in verschiedenen cpp-Dateien (bzw. in einer
// cpp-Datei durch verschiedene Funktionsaufrufe) brauche, insgesamt nur einmal
// eingebunden/angeschaut werden --> one definition rule
#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
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
  int snakelength = 1;
  int kaestchenlaenge = 10;
  int gitterdicke = 2;
  int rasterbreite = width / (kaestchenlaenge + gitterdicke);
  int rasterhoehe = height / (kaestchenlaenge + gitterdicke);
  int startx = rasterbreite / 2;
  int starty = rasterhoehe / 2;
  int foodx = rand() % rasterbreite;
  int foody = rand() % rasterhoehe;
  sf::RenderWindow window{sf::VideoMode(width, height), "Let's play!"};
};