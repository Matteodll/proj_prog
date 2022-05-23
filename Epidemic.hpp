#ifndef EPIDEMIC_HPP
#define EPIDEMIC_HPP

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

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

  State operator()(int i, int j) {
    return (i >= 0 && i < n_ && j >= 0 && j < n_) ? board_[i * n_ + j]
                                                  : State::Removed;
  }

  void operator()(int i, int j, State s) {
    assert(i >= 0 && i < n_ && j >= 0 && j < n_);
    board_[i * n_ + j] = s;
  }

  int size() const { return n_; }

  int size_board() const { return board_.size(); }

  int count(State s) const {
    return std::count(board_.begin(), board_.end(), s);
  }

  void print_() {
    std::cout << "print_\n";
    for (int i = 0; i < n_; i++) {
      std::cout << "R" << i << '\t';
      for (int j = 0; j < n_; j++) {
        if (board_[i * n_ + j] == State::Susceptible)
          std::cout << "+ ";
        else if (board_[i * n_ + j] == State::Infected)
          std::cout << "* ";
        else
          std::cout << "  ";
      }
      std::cout << "\n";
    }
  }
  
  void evolve(char v) {
    if (v == 'v') {
      std::vector<State> next = board_;
      double d;
      State curr;
      State ev;

      std::cout << "Beginning: \n";
      this->print_();

      for (int i = 0; i < n_; ++i) {
        for (int j = 0; j < n_; ++j) {
          curr = board_[i * n_ + j];
          std::cout << "\nanalising: " << static_cast<int>(curr) << "(" << i
                    << ", " << j << ")\n";
          if (curr == State::Infected) {
            d = ((double)rand() / (RAND_MAX));
            std::cout << "infected detected, num = " << d << std::endl;
            if (d <= gamma_) {
              next[i * n_ + j] = State::Removed;
              std::cout << "element removed\n";
            }

            for (int r = i - 1; r <= i + 1; r++) {
              std::cout << "evolving row: " << r << std::endl;
              for (int c = j - 1; c <= j + 1; c++) {
                std::cout << "evolving column: " << c << std::endl;
                if (r >= 0 && r < n_ && c >= 0 && c < n_) {
                  ev = board_[c * n_ + r];
                  std::cout << "state to evolve: " << static_cast<int>(ev)
                            << std::endl;
                  if (ev == State::Susceptible) {
                    d = ((double)rand() / (RAND_MAX));
                    std::cout << "Susceptible detected, num = " << d
                              << std::endl;
                    if (d <= beta_) {
                      next[c * n_ + r] = State::Infected;
                      std::cout << "element infected\n";
                    }
                  }
                }
              }
            }
          }
        }
      }

      board_ = next;

      std::cout << "\nEnd: \n";
      this->print_();
    }
  }

  void evolve() {
    std::vector<State> next = board_;
    double d;

    for (int i = 0; i < n_; ++i) {
      for (int j = 0; j < n_; ++j) {
        if (board_[i * n_ + j] == State::Infected) {
          d = ((double)rand() / (RAND_MAX));
          if (d <= gamma_) {
            next[i * n_ + j] = State::Removed;
          }

          for (int r = i - 1; r <= i + 1; r++) {
            for (int c = j - 1; c <= j + 1; c++) {
              if (r >= 0 && r < n_ && c >= 0 && c < n_) {
                if (board_[c * n_ + r] == State::Susceptible) {
                  d = ((double)rand() / (RAND_MAX));
                  if (d <= beta_) {
                    next[c * n_ + r] = State::Infected;
                  }
                }
              }
            }
          }
        }
      }
    }

    board_ = next;
  }
};

void print(Epidemic c) {
  std::cout << "print\n";
  for (int i = 0; i < c.size(); i++) {
    std::cout << "R" << i << '\t';
    for (int j = 0; j < c.size(); j++) {
      if (c(i, j) == State::Susceptible)
        std::cout << "+ ";
      else if (c(i, j) == State::Infected)
        std::cout << "* ";
      else
        std::cout << "  ";
    }
    std::cout << "\n";
  }
}

#endif