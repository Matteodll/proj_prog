#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

enum class State : char { Susceptible, Infected, Removed };

class Epidemic {
  const double beta_;
  const double gamma_;
  const double delta_t_;
  const int n_;
  std::vector<State> board_;


 public:
  Epidemic(double beta, double gamma, double delta_t, int n)
      : beta_{beta}, gamma_{gamma}, delta_t_{delta_t}, n_{n}, board_(n * n) {
    assert(beta >= 0 && beta <= 1);
    assert(gamma >= 0 && gamma <= 1);
    assert(delta_t > 0);
    assert(n > 0);
  }

  State operator() (int i, int j) {
    return (i > 0 && i <= n_ && j > 0 && j <= n_)
               ? board_[(i - 1) * n_ + (j - 1)]
               : State::Removed;
  }

  void operator()(int i, int j, State s) {
    assert(i >= 0 && i <= n_ && j >= 0 && j <= n_);
    board_[(i - 1) * n_ + (j - 1)] = s;
  }

  int size() const { return n_; }

  int size_board() const { return board_.size(); }

  int count(State s) const { return std::count(board_.begin(), board_.end(), s); }
  /*
    void print() {
      for (int i = 1; i <= n_; i++) {
        std::cout << "R" << i << '\t';
        for (int j = 1; j <= n_; j++) {
          if(board_[(i - 1) * n_ + (j-1) ] == State::Susceptible) std::cout <<"+ ";
          else if (board_[(i - 1) * n_ + (j-1) ] == State::Infected) std::cout << "* "; 
          else std::cout << "  ";
        }
      std::cout << "\n";
      }
    }
  */

  void evolve() {
    std::vector<State> next = board_;
    double d;
    for (int i = 1; i <= n_; i++) {
      for (int j = 1; j <= n_; j++) {
        if(board_[(i - 1) * n_ + (j-1) ] == State::Infected) {
          for(int r = i - 1; r != i +1; ++r) {
            for (int c = j - 1; c != j + 1; ++j) {
              if(board_[(r - 1) * n_ + (c-1)] == State::Susceptible) {
                d = ((double) rand() / (RAND_MAX));
                if(d <= beta_) next[(r - 1) * n_ + (c-1)] = State::Infected;
              }
            }
          }
          d = ((double) rand() / (RAND_MAX));
          if(d <= gamma_) next[(i - 1) * n_ + (j - 1)] = State::Removed;
        }
      }
    }
  }
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