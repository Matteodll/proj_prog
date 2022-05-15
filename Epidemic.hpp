#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

enum class State : char { Susceptible, Infected, Removed };

class Epidemic {
  double beta_;
  double gamma_;
  double delta_t_;
  int n_;
  std::vector<State> board_;

 public:
  Epidemic(double beta, double gamma, double delta_t, int n)
      : beta_{beta}, gamma_{gamma}, delta_t_{delta_t}, n_{n}, board_(n * n) {
    assert(beta >= 0 && beta <= 1);
    assert(gamma >= 0 && gamma <= 1);
    assert(delta_t_ > 0);
    assert(n > 0);
  }

  State operator()(int i, int j) {
    return (i > 0 && i <= n_ && j > 0 && j <= n_)
               ? board_[(i - 1) * n_ + (j - 1)]
               : State::Removed;
  }

  void operator()(int i, int j, State s) {
    assert(i >= 0 && i <= n_ && j >= 0 && j <= n_);
    board_[(i - 1) * n_ + (j - 1)] = s;
  }

  int size() { return n_; }

  int size_b() { return board_.size(); }

  int count(State s) { return std::count(board_.begin(), board_.end(), s); }
  /*
    void print() {
      for (int i = 1; i <= n_; i++) {
        std::cout << "R" << i << '\t';
        for (int j = 1; j <= n_; j++) {
          if(board_[(i - 1) * n_ + (j-1) ] == State::Susceptible) std::cout <<
    "+ "; else if (board_[(i - 1) * n_ + (j-1) ] == State::Infected) std::cout
    << "* "; else std::cout << "  ";
        }
      std::cout << "\n";
      }
    }
  */
};
/*
void print(Epidemic c) {
  for (int i = 1; i <= c.size(); i++) {
    std::cout << "R" << i << '\t';
    for (int j = 1; j <= c.size(); j++) {
      if(c(i, j) == State::Susceptible) std::cout << "+ ";
      else if (c(i, j) == State::Infected) std::cout << "* ";
      else std::cout << "  ";
    }
  std::cout << "\n";
  }
}
*/
#endif