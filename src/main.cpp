#include "card.hpp"
#include "globals.hpp"
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

  Globals globals(screenWidth, screenHeight);

  rl::Window window(screenWidth, screenHeight,
                    "raylib [shapes] example - collision area");

  // instantiate cards
  std::vector<Card *> cards;
  cards.push_back(new Card(vec2(200, 0), Nation::NONE));
  cards.push_back(new Card(vec2(400, 0), Nation::USA));
  cards.push_back(new Card(vec2(800, 0), Nation::UK));

  // push cards to solver
  Solver solver;
  for (int i = 0; i < cards.size(); i++) {
    solver.objects.push_back(cards[i]);
  }

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
      solver.update(dt, cards);
    }

    window.ClearBackground(RAYWHITE);

    for (auto card : cards) {
      card->update(globals);
    }

    DrawScene(cards);
  }

  // De-Initialization
  for (auto card : cards) {
    card->~Card();
    delete card;
  }

  return 0;
}
