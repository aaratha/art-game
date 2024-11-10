#include "card.hpp"

Card::Card(vec2 pos, Nation nation) : PhysObj(pos), nation(nation) {
  rectangle = {pos.x, pos.y, width, height};
  applyNationProperties();
  loadShadowTexture("resources/sprites/card_shadow.png");
}

Card::~Card() {
  if (textureLoaded) {
    UnloadTexture(texture);
  }
  if (shadowTextureLoaded) {
    UnloadTexture(shadowTexture);
  }
}

Nation Card::getNation() { return nation; }

Rectangle Card::getRect() {
  return {
      getPos().x - width / 2,  // x position (centered)
      getPos().y - height / 2, // y position (centered)
      width,                   // width of the card
      height                   // height of the card
  };
}

void Card::applyNationProperties() {
  switch (nation) {
  case Nation::NONE:
    color = GRAY;
    loadTexture("resources/sprites/card_usa.png");
    break;
  case Nation::USA:
    color = BLUE;
    loadTexture("resources/sprites/card_usa.png");
    break;
  case Nation::USSR:
    color = RED;
    loadTexture("resources/sprites/card_usa.png");
    break;
  case Nation::UK:
    color = GREEN;
    loadTexture("resources/sprites/card_usa.png");
    break;
  case Nation::GERMANY:
    color = YELLOW;
    loadTexture("resources/sprites/card_usa.png");
    break;
  }
}

void Card::update(Globals &globals) {
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
    if (!isDragging && !globals.isDraggingAnyCard) {
      isDragging = true;
      globals.isDraggingAnyCard = true;
      dragOffset = getPos() - mousePos; // Set initial offset at drag start
    }
  }

  // Stop dragging on mouse release
  if (IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
    isDragging = false;
    globals.isDraggingAnyCard = false;
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

void Card::loadTexture(const std::string &filename) {
  texture = LoadTexture(filename.c_str());
  textureLoaded = true;
}

void Card::loadShadowTexture(const std::string &filename) {
  shadowTexture = LoadTexture(filename.c_str());
  shadowTextureLoaded = true;
}

void Card::draw() {
  // Draw shadow as before
  float distanceFromCenter = getPos().x - (GetScreenWidth() / 2.0f);
  float effectiveShadowOffset =
      shadowOffset * (distanceFromCenter * 1.5 / (GetScreenWidth() / 2.0f));

  width = 100 * scale;
  height = 150 * scale;

  if (isDragging) {
    scale = lerp1D(scale, maxScale, 0.3);
    shadowOffset = lerp1D(shadowOffset, 10, 0.3);
  } else {
    scale = lerp1D(scale, minScale, 0.3);
    shadowOffset = lerp1D(shadowOffset, 0, 0.3);
  }

  angle = lerp1D(angle, getPos().x - getPrev().x, 0.2);
  if (0.5 > angle && angle > -0.5)
    angle = 0;

  Rectangle shadowRect = {getPos().x + effectiveShadowOffset,
                          getPos().y + shadowOffset, width, height};

  // Draw the texture if it's loaded
  if (textureLoaded) {
    Rectangle sourceRect = {0.0f, 0.0f, static_cast<float>(texture.width),
                            static_cast<float>(texture.height)};
    Rectangle destRect = {getPos().x, getPos().y, width, height};
    Rectangle shadowDestRect = {getPos().x + effectiveShadowOffset,
                                getPos().y + shadowOffset, width, height};
    vec2 origin = {width / 2, height / 2}; // Center of rotation

    DrawTexturePro(shadowTexture, sourceRect, shadowDestRect, origin, angle,
                   (Color){0, 0, 0, 70});
    DrawTexturePro(texture, sourceRect, destRect, origin, angle, WHITE);
  } else {
    // Fallback: Draw the rectangle in red if texture isn't loaded
    DrawRectanglePro(rectangle, vec2(width / 2, height / 2), angle, RED);
  }
}
