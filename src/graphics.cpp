#include "graphics.hpp"

void DrawScene(std::vector<Card *> cards) {
  BeginDrawing();

  // Move the dragged card to the back of the cards vector
  for (auto it = cards.begin(); it != cards.end(); ++it) {
    if ((*it)->isDragging) {
      // Rotate the dragged card to the end of the vector
      std::rotate(it, it + 1, cards.end());
      break; // Only one card can be dragged at a time, so break after finding
             // it
    }
  }

  for (auto card : cards) {
    card->draw();
  }

  DrawFPS(10, 10);
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    DrawText("Left mouse button is pressed", 100, 40, 10, RED);
  }

  EndDrawing();
}
