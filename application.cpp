#include <algorithm>  //brauch ich für CLAMP
#include <application.hpp>
application::application() {}
void application::execute() {
  int speed = 300;  // sleep time of gameloop in ms
  int snakex;
  int snakey;
  snakex = startx;
  snakey = starty;
  std::vector<int> foodcolor(3);
  foodcolor = {100, 0, 50};
  std::vector<int> snakecolor(3);
  snakecolor = {50, 100, 0};

  int movement = rand() % 3;
  std::list<int> snakelist;
  snakelist = {gridwidth / 2, gridheight / 2};
  std::clock_t starttime = std::clock();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(
        event)) {  // die Eingabe-Liste event wird vom window abgefragt. Das ist
                   // true, solange es neue events (Benutzereingaben) gibt.
      if (event.type == sf::Event::Closed)
        window.close();
      else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) window.close();
        if (event.key.code == sf::Keyboard::Up) movement = 0;
        if (event.key.code == sf::Keyboard::Right) movement = 1;
        if (event.key.code == sf::Keyboard::Down) movement = 2;
        if (event.key.code == sf::Keyboard::Left) movement = 3;
      }
    }

    window.clear();

    // Draw grid
    for (int i = 0; i < gridwidth; ++i) {
      for (int j = 0; j < gridheight; ++j) {
        sf::RectangleShape box(sf::Vector2f(boxlength, boxlength));
        box.setPosition(i * (boxlength + linewidth),
                        j * (boxlength + linewidth));
        box.setFillColor(sf::Color(100, 100, 100));
        window.draw(box);
      }
    }

    // Make food
    sf::CircleShape food(boxlength / 2);
    food.setPosition(foodx * (boxlength + linewidth),
                     foody * (boxlength + linewidth));
    food.setFillColor(sf::Color(foodcolor[0], foodcolor[1], foodcolor[2]));

    window.draw(food);

    double duration = (std::clock() - starttime) / (double)CLOCKS_PER_SEC;
    float elapsedtime = speed / (float)1000;

    if (duration >= elapsedtime) {
      // Calculate snake
      starttime = std::clock();
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

    // // Break condition

    // // HIER WEITERMACHEN
    // for (int i = 2; i <= snakevector.size() / 2; ++i) {
    //   if (snakevector[0] == snakevector[2 * i - 2] and
    //       snakevector[1] == snakevector[2 * i - 1]) {
    //     std::cout << "jetzt ists vorbei! \n";
    //     sf::RenderWindow failalert{sf::VideoMode(300, 300), "You failed!"};
    //     // failalert.clear(sf::Color(255, 0, 0, 255));
    //     sf::RectangleShape backgroundcheatsheet(sf::Vector2f(300, 300));
    //     backgroundcheatsheet.setFillColor(sf::Color(255, 0, 0, 255));
    //     while (failalert.isOpen()) {
    //       sf::Event eventfail;
    //       while (failalert.pollEvent(eventfail)) {
    //         if (eventfail.type == sf::Event::Closed)
    //           failalert.close();
    //         else if (eventfail.type == sf::Event::KeyPressed) {
    //           if (eventfail.key.code == sf::Keyboard::Escape)
    //           failalert.close();
    //         }
    //       }

    //       sf::RectangleShape buttonbox(sf::Vector2f(50, 60));
    //       buttonbox.setPosition(100, 100);
    //       failalert.draw(backgroundcheatsheet);
    //       failalert.draw(buttonbox);
    //       auto MousePosition = sf::Mouse::getPosition(failalert);
    //       sf::Vector2f MousePositionF(static_cast<float>(MousePosition.x),
    //                                   static_cast<float>(MousePosition.y));
    //       if (buttonbox.getGlobalBounds().contains(MousePositionF) and
    //           sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    //         failalert.close();
    //         window.close();
    //       };

    //       failalert.display();
    //     }
    //   }
    // }

    // Draw snake
    std::list<int>::iterator it2;
    it2 = snakelist.begin();
    // alternativ könnte ich auch direkt auto it2 = snakelist.begin() usw.
    // schreiben, dann überlegt er sich selbst was das für ein iterator sein
    // muss
    while (it2 != snakelist.end()) {
      int currentitem = *it2;
      sf::CircleShape snake(boxlength / 2);
      snake.setFillColor(
          sf::Color(snakecolor[0], snakecolor[1], snakecolor[2]));
      snakex = *it2;
      it2++;
      snakey = *it2;
      snake.setPosition(snakex * (boxlength + linewidth),
                        snakey * (boxlength + linewidth));
      window.draw(snake);

      // Got food
      if (snakex == foodx and snakey == foody) {
        // Farbmischung
        snakecolor[0] = (snakelist.size() * snakecolor[0] + foodcolor[0]) /
                        (snakelist.size() + 2);
        snakecolor[1] = (snakelist.size() * snakecolor[1] + foodcolor[1]) /
                        (snakelist.size() + 2);
        snakecolor[2] = (snakelist.size() * snakecolor[2] + foodcolor[2]) /
                        (snakelist.size() + 2);

        // snakelist.resize(snakelist.size() + 2);
        // WAS SOLL DAS HIER MACHEN? ICH  RAFFS NCHT UND WEI? DESHALB NICHT; WIE
        // ICHS AUF NE LISTE UMSCHREIBEN SOLL
        snakelist.push_back(foodx);  // snakelist[snakelist.size() - 1]);
        snakelist.push_back(foody);  // snakelist[snakelist.size()]);
        speed = speed - 50;

        foodcolor = {distcolor(rng), distcolor(rng), distcolor(rng)};
        foodx = distx(rng);
        foody = disty(rng);
      }
      it2++;
    }
    window.display();
  }
}
