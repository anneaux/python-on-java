#include <game.hpp>

void game::move_snake() {
  if (gotfood == true) {
    snakelist.push_back(food);
    gotfood = false;
  }

  // Calculate snake
  datapoint next;
  if (movement == 0) {
    next = {snakelist.front().x,
            (gridheight + snakelist.front().y - 1) % (gridheight)};
  } else if (movement == 1) {
    next = {(snakelist.front().x + 1) % gridwidth, snakelist.front().y};
  } else if (movement == 2) {
    next = {snakelist.front().x, (snakelist.front().y + 1) % gridheight};
  } else if (movement == 3) {
    next = {(gridwidth + snakelist.front().x - 1) % gridwidth,
            snakelist.front().y};
  }

  snakelist.push_front(next);
  snakelist.pop_back();
}

bool game::gamebreak() {
  auto iter = snakelist.begin();
  ++iter;
  for (; iter != snakelist.end(); ++iter) {
    if (snakelist.front() == *iter) return true;
  }
  return false;
}

bool game::foodeaten() {
  for (const auto p : snakelist) {
    if (p == food) {
      gotfood = true;
      food = {distx(rng), disty(rng)};
      return true;
    }
  }

  // for (auto it = snakelist.begin(); it != snakelist.end(); ++it) {
  //   if (*it == food) {
  //     gotfood = true;
  //     food = {distx(rng), disty(rng)};
  //     return true;
  //   }
  // }
  return false;
}