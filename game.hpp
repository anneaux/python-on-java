#pragma once
#include <list>
#include <random>

struct datapoint {
  int x;
  int y;
};
// inline int operator[](datapoint d, int i) noexcept {
//   if (i == 0) return d.x;
//   if (i == 1) return d.y;
// }

inline bool operator==(datapoint d1, datapoint d2) noexcept {
  return (d1.x == d2.x) && (d1.y == d2.y);
}

class game {
 public:
  void move_snake();
  bool gamebreak();
  bool foodeaten();

  int gridwidth = 20;
  int gridheight = 20;

  datapoint snake_startposition = {gridwidth / 2.0f, gridheight / 2.0f};

  std::list<datapoint> snakelist = {snake_startposition};
  int movement = 1;
  bool gotfood = false;
  std::mt19937 rng{std::random_device{}()};
  std::uniform_int_distribution<int> distx{0, gridwidth - 1};
  std::uniform_int_distribution<int> disty{0, gridheight - 1};
  datapoint food = {distx(rng), disty(rng)};

 private:
};