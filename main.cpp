#include "Epidemic.hpp"

int main() {
  Epidemic c{0.5, 0.3, 1., 10};
  c(1, 1, State::Infected);
  c(2, 3, State::Infected);
  c(3, 2, State::Removed);
  c(1, 10, State::Infected);
  c(10, 1, State::Infected);
  c(10, 10, State::Infected);

  c.print();
  std::cout << "size() = " << c.size() << std::endl
            << "size board = " << c.size_b() << std::endl;

  print(c);

  return 0;
}