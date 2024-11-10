#pragma once

#include "globals.hpp"
#include "physics.hpp"
#include "raylib-cpp.hpp"
#include "utils.hpp"

#include <iostream>

// Define nation types
enum class Nation {
  NONE,
  USA,
  USSR,
  UK,
  FRANCE,
  GERMANY,
  ITALY,
  JAPAN,
  CHINA,
  INDIA,
  BRAZIL,
  MEXICO,
  CANADA,
  AUSTRALIA,
  SOUTH_AFRICA,
  EGYPT,
  SAUDI_ARABIA,
  IRAN,
  IRAQ,
  TURKEY,
  ISREAL
};

class Card : public PhysObj {
  float width = 100;
  float height = 150;
  float shadowWidth = 100;
  float shadowHeight = 150;
  float shadowOffset = 20;
  float scale = 1;
  vec2 dragOffset = {0, 0}; // Offset between card center and mouse position
  float maxScale = 1.2;
  float minScale = 1.0;
  float angle = 0;
  Rectangle rectangle;

  Nation nation = Nation::NONE;
  Color color = GRAY;

  Texture2D texture;
  Texture2D shadowTexture;
  bool textureLoaded = false;

public:
  bool isDragging = false;

  Card(vec2 pos, Nation nation);

  void setNation(Nation nation);
  Nation getNation();
  Rectangle getRect();
  void applyNationProperties();

  void update(Globals &globals);

  void loadTexture(const std::string &filename);
  void draw();
};
