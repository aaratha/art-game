#include "card.hpp"
#include <raylib.h>

Card::Card(vec2 pos) : PhysObj(pos) {}

void Card::update() {
  Rectangle cardRect = {
      getPos().x - width / 2,  // x position (adjusted to the top-left corner)
      getPos().y - height / 2, // y position (adjusted to the top-left corner)
      width,                   // width of the card
      height                   // height of the card
  };

  vec2 mousePos = GetMousePosition();

  // Start dragging if inside card and button is pressed
  if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) &&
      CheckCollisionPointRec(mousePos, cardRect)) {
    if (!isDragging) {
      isDragging = true;
      dragOffset = getPos() - mousePos; // Set initial offset at drag start
    }
  }

  // Stop dragging on mouse release
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isDragging = false;
  }

  // Update card position if dragging
  if (isDragging) {
    setPos(mousePos + dragOffset); // Update position smoothly with offset
  } else {
    // Apply boundary checks when not dragging
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    vec2 pos = getPos();

    // Horizontal boundaries
    if (pos.x < width / 2) {
      pos.x = width / 2;
    } else if (pos.x > screenWidth - width / 2) {
      pos.x = screenWidth - width / 2;
    }

    // Vertical boundaries
    if (pos.y < height / 2) {
      pos.y = height / 2;
    } else if (pos.y > screenHeight - height / 2) {
      pos.y = screenHeight - height / 2;
    }

    setPos(pos); // Set position after boundary check
  }
}

void Card::draw() {
  DrawRectangle(getPos().x - width / 2, getPos().y - height / 2, width, height,
                RED);
}
