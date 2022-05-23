#include <SFML/Graphics.hpp>

#include "Epidemic.hpp"

int main() {
  std::srand(std::time(nullptr));
  
  Epidemic c{0.5, 0.3, 1., 10};
  c(1, 1, State::Infected);
  c(2, 3, State::Infected);
  c(3, 2, State::Removed);
  c(1, 9, State::Infected);
  c(9, 1, State::Infected);
  c(9, 9, State::Infected);

  int const num_points = c.size();
  int const fps = 60;

  unsigned const display_width = .9 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .9 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Epidemic evolution");
  window.setFramerateLimit(fps);

  sf::CircleShape circBlue{30.f};
  circBlue.setFillColor(sf::Color::Blue);

  sf::CircleShape circRed{30.f};
  circRed.setFillColor(sf::Color::Red);

  sf::CircleShape circBlack{30.f};
  circBlack.setFillColor(sf::Color::Black);

  auto const min_x{0.};
  auto const max_x = display_width;
  auto const min_y{0.};
  auto const max_y = display_height;
  auto const dist_x = (max_x - min_x) / static_cast<double>(num_points);
  auto const dist_y = (max_y - min_y) / static_cast<double>(num_points);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    window.clear(sf::Color::White);

    for (int i = 1; i <= num_points; ++i) {
      for (int j = 1; j <= num_points; ++j) {
        switch (c(i, j)) {
          case (State::Susceptible): {
            circBlue.setPosition(0 + i * dist_x, 0 + j * dist_y);
            window.draw(circBlue);
            break;
          }

          case (State::Infected): {
            circRed.setPosition(0 + i * dist_x, 0 + j * dist_y);
            window.draw(circRed);
            break;
          }

          case (State::Removed): {
            circBlack.setPosition(0 + i * dist_x, 0 + j * dist_y);
            window.draw(circBlack);
            break;
          }
        }
      }
    }

    window.display();
  }
}

/*
        domande:
        - aggiungendo la funzione evolve la schermata si apre nera?
        - riempimento della board da fare random?
        - quali parametri chiedere da terminale (oltre al numero di persone)?

*/
