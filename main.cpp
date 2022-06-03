#include <SFML/Graphics.hpp>
#include <stdexcept>

#include "Epidemic.hpp"

int main() {
  std::srand(std::time(nullptr));

  int dim;
  double beta;
  double gamma;
  int num_infected;
  int num_removed;

  do {
    std::cout << "Dimension: ";
    std::cin >> dim;
  } while (dim < 0);

  do {
    std::cout << "Probability of infection [0, 1]: ";
    std::cin >> beta;
  } while ((beta < 0) || (beta > 1));

  do {
    std::cout << "Probability of healing [0, 1]: ";
    std::cin >> gamma;
  } while ((gamma < 0) || (gamma > 1));

  do {
    std::cout << "Number of infected: ";
    std::cin >> num_infected;
  } while (num_infected < 0 || num_infected > (dim * dim));

  do {
    std::cout << "Number of removed: ";
    std::cin >> num_removed;
  } while (num_removed < 0 || num_removed > ((dim * dim) - num_infected));

  Epidemic c{beta, gamma, dim};

  c.filling(num_infected, num_removed);

  int const num_points = c.size();
  int fps;
  float point_dim;

  if (num_points <= 15) {
    point_dim = 30.f;
    fps = 1;
  } else if (num_points <= 50) {
    point_dim = 10.f;
    fps = 1;
  } else if (num_points <= 150) {
    point_dim = 5.f;
    fps = 2;
  } else {
    point_dim = 3.f;
    fps = 4;
  }

  unsigned const display_width = .9 * sf::VideoMode::getDesktopMode().width;
  unsigned const display_height = .9 * sf::VideoMode::getDesktopMode().height;

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "Epidemic evolution");
  window.setPosition(sf::Vector2i(50, 50));
  window.setFramerateLimit(fps);

  sf::CircleShape circBlue{point_dim};
  circBlue.setFillColor(sf::Color::Blue);

  sf::CircleShape circRed{point_dim};
  circRed.setFillColor(sf::Color::Red);

  sf::CircleShape circBlack{point_dim};
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
    c.evolve();

    for (int i = 0; i < num_points; ++i) {
      for (int j = 0; j < num_points; ++j) {
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
