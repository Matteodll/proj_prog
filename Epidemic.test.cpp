#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "Epidemic.hpp"
#include "doctest.h"

TEST_CASE("Testing class Epidemic") {
  SUBCASE("Testing Size method") {
    Epidemic c{0.5, 0.3, 5};
    CHECK(c.size() == 5);
  }

  SUBCASE("Testing operator() overloads") {
    Epidemic c{0.5, 0.3, 5};
    c(1, 1, State::Susceptible);
    c(2, 3, State::Infected);
    c(3, 2, State::Removed);
    CHECK(c(1, 1) == State::Susceptible);
    CHECK(c(2, 3) == State::Infected);
    CHECK(c(3, 2) == State::Removed);
    CHECK(c(1, 2) == State::Susceptible);
    CHECK(c(1, 5) == State::Removed);
    CHECK(c(-10, 2) == State::Removed);
    CHECK(c(2, -10) == State::Removed);
    CHECK(c(-10, -10) == State::Removed);
    CHECK(c(20, 2) == State::Removed);
    CHECK(c(3, 20) == State::Removed);
    CHECK(c(20, 20) == State::Removed);
    CHECK(c(0, 0) == State::Susceptible);
  }

  SUBCASE("Testing count()") {
    Epidemic c{0.5, 0.3, 5};
    c(1, 1, State::Susceptible);
    c(1, 3, State::Infected);
    c(4, 3, State::Infected);
    c(4, 4, State::Infected);
    c(2, 3, State::Infected);
    c(3, 2, State::Removed);
    c(3, 3, State::Removed);
    c(3, 4, State::Removed);
    CHECK(c.count(State::Susceptible) == 18);
    CHECK(c.count(State::Removed) == 3);
    CHECK(c.count(State::Infected) == 4);
  }

}