#pragma once
#include <list>
#include <random>

class game {
 public:
  void move_snake();
  bool gamebreak();
  bool foodeaten();

  int gridwidth = 20;
  int gridheight = 20;
  std::list<int> snakelist = {gridwidth / 2, gridheight / 2};
  int movement = 1;
  bool gotfood = false;
  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> distx{0, gridwidth - 1};
  int foodx = distx(rng);
  std::uniform_int_distribution<int> disty{0, gridheight - 1};
  int foody = disty(rng);

 private:
};