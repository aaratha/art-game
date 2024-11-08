#pragma once

#include "physics.hpp"
#include "raylib-cpp.hpp"

class Card : public PhysObj {
  float width = 100;
  float height = 150;
  bool isDragging = false;
  vec2 dragOffset = {0, 0}; // Offset between card center and mouse position

public:
  Card(vec2 pos);
  void update();
  void draw();
};
