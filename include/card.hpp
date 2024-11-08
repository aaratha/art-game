#pragma once

#include "physics.hpp"
#include "raylib-cpp.hpp"

class Card : public PhysObj {
  float width = 100;
  float height = 150;
  float shadowWidth = 100;
  float shadowHeight = 150;
  float shadowOffset = 20;
  float scale = 1;
  bool isDragging = false;
  vec2 dragOffset = {0, 0}; // Offset between card center and mouse position
  float maxScale = 1.2;
  float minScale = 1.0;
  float angle = 0;
  Rectangle rectangle;

public:
  Card(vec2 pos);
  void update();
  void draw();
};
