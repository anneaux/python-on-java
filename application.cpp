#include <algorithm>  //brauch ich für CLAMP
#include <application.hpp>
application::application() {}
void application::execute() {
  int speed = 500;  // sleep time of gameloop in ms
  int snakex;
  int snakey;
  snakex = startx;
  snakey = starty;
  int foodred = 100;
  int foodgreen = 0;
  int foodblue = 50;
  int snakered = 50;
  int snakegreen = 100;
  int snakeblue = 0;

  int movement = rand() % 3;
  std::vector<int> snakevector(2 * snakelength);
  snakevector[0] = rasterbreite / 2;
  snakevector[1] = rasterhoehe / 2;

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

    // Kaestchen zeichnen
    for (int i = 0; i < rasterbreite; ++i) {
      for (int j = 0; j < rasterhoehe; ++j) {
        sf::RectangleShape box(sf::Vector2f(kaestchenlaenge, kaestchenlaenge));
        box.setPosition(i * (kaestchenlaenge + gitterdicke),
                        j * (kaestchenlaenge + gitterdicke));
        box.setFillColor(sf::Color(100, 100, 100));
        window.draw(box);
      }
    }

    // Futter zeichnen
    sf::CircleShape food(kaestchenlaenge / 2);
    food.setPosition(foodx * (kaestchenlaenge + gitterdicke),
                     foody * (kaestchenlaenge + gitterdicke));
    food.setFillColor(sf::Color(foodred, foodgreen, foodblue));
    window.draw(food);

    // Schlange berechnen
    for (int k = 1; k <= snakevector.size() - 2; ++k) {
      snakevector[snakevector.size() - k] =
          snakevector[snakevector.size() - k - 2];
    }
    if (movement == 0) {
      snakevector[1] = snakevector[1] - 1;
      if (snakevector[1] == -1) snakevector[1] = rasterhoehe;
    }
    if (movement == 1) {
      snakevector[0] = snakevector[0] + 1;
      if (snakevector[0] == rasterbreite + 1) snakevector[0] = 0;
    }
    if (movement == 2) {
      snakevector[1] = snakevector[1] + 1;
      if (snakevector[1] == rasterhoehe + 1) snakevector[1] = 0;
    }
    if (movement == 3) {
      snakevector[0] = snakevector[0] - 1;
      if (snakevector[0] == -1) snakevector[0] = rasterbreite;
    }

    // std::cout << "vor Schlange zeichnen " << snakevector.size() << "\n";
    for (int l = 1; l <= snakevector.size() / 2; ++l) {
      sf::CircleShape snake(kaestchenlaenge / 2);
      snake.setFillColor(sf::Color(snakered, snakegreen, snakeblue));
      snakex = snakevector[2 * l - 2];
      snakey = snakevector[2 * l - 1];
      snake.setPosition(snakex * (kaestchenlaenge + gitterdicke),
                        snakey * (kaestchenlaenge + gitterdicke));

      window.draw(snake);

      // Fressen
      if (snakex == foodx and snakey == foody) {
        // Farbmischung
        snakered = (snakered + foodred) / 2;
        snakegreen = (snakegreen + foodgreen) / 2;
        snakeblue = (snakeblue + foodblue) / 2;

        snakevector.resize(snakevector.size() + 2);
        speed = speed - 50;

        foodred = rand() % 255;
        foodgreen = rand() % 255;
        foodblue = rand() % 255;
        foodx = rand() % rasterbreite;
        foody = rand() % rasterhoehe;
      }
    }

    sf::sleep(sf::milliseconds(speed));
    window.display();
  }
}
