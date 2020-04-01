#include <game.hpp>

void game::move_snake() {
  if (gotfood == true) {
    snakelist.push_back(foodx);
    snakelist.push_back(foody);
    gotfood = false;
  }

  // Calculate snake
  std::list<int>::iterator it = snakelist.begin();
  std::advance(it, 1);
  int nextx;
  int nexty;
  if (movement == 0) {
    nextx = snakelist.front();
    nexty = (gridheight + (*it) - 1) % (gridheight);
  } else if (movement == 1) {
    nextx = (snakelist.front() + 1) % gridwidth;
    nexty = *it;
  } else if (movement == 2) {
    nexty = (*it + 1) % gridheight;
    nextx = snakelist.front();
  } else if (movement == 3) {
    nextx = (gridwidth + snakelist.front() - 1) % gridwidth;
    nexty = *it;
  }

  snakelist.push_front(nexty);
  snakelist.push_front(nextx);
  snakelist.pop_back();
  snakelist.pop_back();
}

bool game::gamebreak() {
  std::list<int>::iterator iter = snakelist.begin();
  auto headx = *iter;
  std::advance(iter, 1);
  auto heady = *iter;
  std::advance(iter, 1);

  while (iter != snakelist.end()) {
    auto iterx = *iter;
    std::advance(iter, 1);
    auto itery = *iter;
    ++iter;
    if ((headx == iterx and heady == itery)) {
      return true;
    }
  }
  return false;
}

bool game::foodeaten() {
  std::list<int>::iterator it2;
  it2 = snakelist.begin();
  while (it2 != snakelist.end()) {
    auto snakex = *it2;
    it2++;
    auto snakey = *it2;
    it2++;

    if (snakex == foodx and snakey == foody) {
      gotfood = true;
      foodx = distx(rng);
      foody = disty(rng);
      return true;
    }
  }
  return false;
}