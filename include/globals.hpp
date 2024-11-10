#pragma once

#include "raylib-cpp.hpp"
#include "utils.hpp"

class Globals {
public:
  Globals(int screenWidth, int screenHeight);

  int screenWidth;
  int screenHeight;

  bool isDraggingAnyCard;
};
