#include "graphics.hpp"

void DrawScene(std::vector<Card *> cards) {
  BeginDrawing();

  for (auto card : cards) {
    card->draw();
  }

  DrawFPS(10, 10);
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    DrawText("Left mouse button is pressed", 100, 40, 10, RED);
  }

  EndDrawing();
}
