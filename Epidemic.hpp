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

#endif