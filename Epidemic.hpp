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
  const int n_;
  std::vector<State> board_;

 public:
  Epidemic(double beta, double gamma, int n)
      : beta_{beta}, gamma_{gamma}, n_{n}, board_(n * n) {
    assert(beta >= 0 && beta <= 1);
    assert(gamma >= 0 && gamma <= 1);
    assert(n > 0);
  }

  State operator()(int i, int j) const {
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

  void filling(int num_infected, int num_removed) {
    int dim = this->size() + 1;
    int x, y;

    for (int i = 0; i < num_infected; ++i) {
      do {
        y = rand() % dim;
        x = rand() % dim;
      } while (board_[y * n_ + x] != State::Susceptible);
      board_[y * n_ + x] = State::Infected;
    }

    for (int i = 0; i < num_removed; ++i) {
      do {
        y = rand() % dim;
        x = rand() % dim;
      } while (board_[y * n_ + x] != State::Susceptible);
      board_[y * n_ + x] = State::Removed;
    }
  }

  void evolve() {
    std::vector<State> next = board_;
    double d;
    int c_susc, c_inf, c_rem;
    double beta_si = (beta_ * this->count(State::Susceptible) / (n_ * n_)) *
                     this->count(State::Infected);
    double gamma_i = gamma_ * this->count(State::Infected);

    c_susc = this->count(State::Susceptible) - beta_si;
    c_inf = this->count(State::Infected) - beta_si - gamma_i;
    c_rem = this->count(State::Removed) + gamma_i;

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

    std::cout << "Theorical Susceptible: " << c_susc << std::endl;
    std::cout << "Susceptible: " << this->count(State::Susceptible)
              << std::endl;
    std::cout << "Theorical Infected: " << c_inf << std::endl;
    std::cout << "Infected: " << this->count(State::Infected) << std::endl;
    std::cout << "Theorical Removed: " << c_rem << std::endl;
    std::cout << "Removed: " << this->count(State::Removed) << "\n\n";
  }
};

#endif