#include "card.hpp"
#include "graphics.hpp"
#include "raylib-cpp.hpp"
#include "utils.hpp"

#include <cmath>
#include <vector>

int main(void) {
  // Initialization
  //---------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  rl::Window window(screenWidth, screenHeight,
                    "raylib [shapes] example - collision area");

  std::vector<Card *> cards;
  cards.push_back(new Card(vec2(200, 0)));
  Solver solver;
  solver.objects.push_back(cards[0]);

  bool pause = false; // Movement pause

  SetTargetFPS(60); // Set our game to run at 60 frames-per-second
  //----------------------------------------------------------

  // Main game loop
  while (!window.ShouldClose()) { // Detect window close button or ESC key
    // Update
    //-----------------------------------------------------
    // Move box if not paused

    if (IsKeyPressed(KEY_SPACE))
      pause = !pause;

    if (!pause) {
      float dt = GetFrameTime();
      solver.update(dt);
    }

    window.ClearBackground(RAYWHITE);

    for (auto card : cards) {
      card->update();
    }

    DrawScene(cards);
  }

  return 0;
}
