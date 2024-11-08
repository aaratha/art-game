#include "card.hpp"
#include <raylib.h>

Card::Card(vec2 pos) : PhysObj(pos) {}

void Card::update() {
  // Set target position if mouse button is down
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
    setTarg(GetMousePosition());
  }

  // Window boundary checks
  const int screenWidth = GetScreenWidth();
  const int screenHeight = GetScreenHeight();

  vec2 pos = getPos();

  // Horizontal boundaries
  if (pos.x < width / 2) {
    pos.x = width / 2;
  } else if (pos.x > screenWidth - width / 2) { // Assuming 100 is card width
    pos.x = screenWidth - width / 2;
  }

  // Vertical boundaries
  if (pos.y < height / 2) {
    pos.y = height / 2;
  } else if (pos.y > screenHeight - height / 2) { // Assuming 150 is card height
    pos.y = screenHeight - height / 2;
  }

  // Set position after boundary check
  setPos(pos);
}

void Card::draw() {
  DrawRectangle(getPos().x - width / 2, getPos().y - height / 2, 100, 150, RED);
}
