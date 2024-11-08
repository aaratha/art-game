#include "raylib-cpp.hpp"
#include "utils.hpp"

class Globals {
public:
  Globals(int screenWidth, int screenHeight);
  ~Globals();

  int screenWidth;
  int screenHeight;
};
