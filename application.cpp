#include <algorithm>  //brauch ich für CLAMP
#include <application.hpp>
#include <button.hpp>
#include <chrono>

application::application() {
  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  state.gridwidth = width / (boxlength + linewidth);
  state.gridheight = height / (boxlength + linewidth);
}

void application::execute() {
  int speed = 300;  // sleep time of gameloop in ms
  auto starttime = std::chrono::system_clock::now();

  while (window.isOpen()) {
    process_input();

    const auto newtime = std::chrono::system_clock::now();
    const auto duration =
        std::chrono::duration<float>(newtime - starttime).count();
    const float frametime = speed / (float)1000;

    if (duration >= frametime) {
      starttime = newtime;
      state.move_snake();

      if (state.foodeaten()) {
        // Farbmischung
        snakecolor[0] =
            (state.snakelist.size() * snakecolor[0] + foodcolor[0]) /
            (state.snakelist.size() + 2);
        snakecolor[1] =
            (state.snakelist.size() * snakecolor[1] + foodcolor[1]) /
            (state.snakelist.size() + 2);
        snakecolor[2] =
            (state.snakelist.size() * snakecolor[2] + foodcolor[2]) /
            (state.snakelist.size() + 2);

        speed = speed - 50;

        foodcolor = {distcolor(rng), distcolor(rng), distcolor(rng)};
      }
    }

    // Break condition
    if (state.gamebreak()) {
      failalertwindow();
    }
    render();
  }
}

void application::process_input() {
  sf::Event event;
  while (window.pollEvent(
      event)) {  // die Eingabe-Liste event wird vom window abgefragt. Das ist
                 // true, solange es neue events (Benutzereingaben) gibt.
    if (event.type == sf::Event::Closed)
      window.close();
    else if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Escape) window.close();
      if (event.key.code == sf::Keyboard::Up) state.movement = 0;
      if (event.key.code == sf::Keyboard::Right) state.movement = 1;
      if (event.key.code == sf::Keyboard::Down) state.movement = 2;
      if (event.key.code == sf::Keyboard::Left) state.movement = 3;
    }
  }
}

void application::render() {
  window.clear(sf::Color(200, 200, 200));
  // Draw grid
  for (int i = 0; i < state.gridwidth; ++i) {
    for (int j = 0; j < state.gridheight; ++j) {
      sf::RectangleShape box(sf::Vector2f(boxlength, boxlength));
      box.setPosition(i * (boxlength + linewidth), j * (boxlength + linewidth));
      box.setFillColor(sf::Color(255, 255, 255));
      window.draw(box);
    }
  }
  // Make food
  sf::CircleShape food(boxlength / 2);
  food.setPosition(state.foodx * (boxlength + linewidth),
                   state.foody * (boxlength + linewidth));
  food.setFillColor(sf::Color(foodcolor[0], foodcolor[1], foodcolor[2]));

  window.draw(food);

  // Draw snake
  int snakex;
  int snakey;
  std::list<int>::iterator it2;
  it2 = state.snakelist.begin();
  while (it2 != state.snakelist.end()) {
    // int currentitem = *it2;
    sf::CircleShape snake(boxlength / 2);
    snake.setFillColor(sf::Color(snakecolor[0], snakecolor[1], snakecolor[2]));
    snakex = *it2;
    it2++;
    snakey = *it2;
    snake.setPosition(snakex * (boxlength + linewidth),
                      snakey * (boxlength + linewidth));

    window.draw(snake);

    it2++;
  }
  window.display();
}

void application::failalertwindow() {
  int failwindowwidth = 300;
  int failwindowheight = 300;
  sf::RenderWindow failalert{sf::VideoMode(failwindowwidth, failwindowheight),
                             "You failed!"};
  // failalert.clear(sf::Color(255, 0, 0, 255));
  sf::RectangleShape backgroundcheatsheet(
      sf::Vector2f(failwindowwidth, failwindowheight));
  backgroundcheatsheet.setFillColor(sf::Color(255, 0, 0, 255));
  failalert.draw(backgroundcheatsheet);

  while (failalert.isOpen()) {
    sf::Event eventfail;
    while (failalert.pollEvent(eventfail)) {
      if (eventfail.type == sf::Event::Closed)
        failalert.close();
      else if (eventfail.type == sf::Event::KeyPressed) {
        if (eventfail.key.code == sf::Keyboard::Escape) failalert.close();
      }
    }

    button ButtonClose("Close", failalert, (failwindowwidth) / 2.0f, 100);
    if (ButtonClose.buttonPressed == true) {
      failalert.close();
      window.close();
    }

    button ButtonRestart("Restart", failalert, (failwindowwidth) / 2.0f, 150);
    if (ButtonRestart.buttonPressed == true) {
      failalert.close();
    }

    failalert.display();
  }
}