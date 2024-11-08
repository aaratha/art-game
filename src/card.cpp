#include "card.hpp"
#include "utils.hpp"
#include <raylib.h>

Card::Card(vec2 pos) : PhysObj(pos) {
  rectangle = {pos.x, pos.y, width, height};
}

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
  // Draw shadow
  float distanceFromCenter = getPos().x - (GetScreenWidth() / 2.0f);
  float effectiveShadowOffset =
      shadowOffset * (distanceFromCenter * 1.5 / (GetScreenWidth() / 2.0f));

  width = 100 * scale;
  height = 150 * scale;
  if (isDragging) {
    if (scale < maxScale) {
      scale = lerp1D(scale, maxScale, 0.3);
    }
    if (shadowOffset < 10) {
      shadowOffset = lerp1D(shadowOffset, 10, 0.3);
    }
  } else {
    if (scale > minScale) {
      scale = lerp1D(scale, minScale, 0.3);
    }
    if (shadowOffset > 0)
      shadowOffset = lerp1D(shadowOffset, 0, 0.3);
  }

  angle = lerp1D(angle, getPos().x - getPrev().x, 0.2);

  Rectangle shadowRect = {getPos().x + effectiveShadowOffset,
                          getPos().y + shadowOffset, width, height};

  rectangle = {
      getPos().x, // x adjusted for center
      getPos().y, // y adjusted for center
      width,      // width with current scale
      height      // height with current scale
  };
  // Draw card
  DrawRectanglePro(shadowRect, vec2(width / 2, height / 2), angle, GRAY);
  DrawRectanglePro(rectangle, vec2(width / 2, height / 2), angle, RED);
}
