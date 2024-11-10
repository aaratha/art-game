#include "graphics.hpp"

Texture2D backgroundTexture;
bool backgroundTextureLoaded = false;

void loadBackgroundTexture(const std::string &filename) {
  backgroundTexture = LoadTexture(filename.c_str());
  backgroundTextureLoaded = true;
}

void unloadBackgroundTexture() { UnloadTexture(backgroundTexture); }

void DrawScene(std::vector<Card *> cards) {
  BeginDrawing();

  DrawTextureEx(backgroundTexture, vec2(0, 0), 0, 2.0, WHITE);

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
