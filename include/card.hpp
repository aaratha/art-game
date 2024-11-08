#pragma once

#include "physics.hpp"
#include "raylib-cpp.hpp"

class Card : public PhysObj {
  float width = 100;
  float height = 150;

public:
  Card(vec2 pos);
  void update();
  void draw();
};
