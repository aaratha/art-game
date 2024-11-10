#pragma once

#include "card.hpp"
#include "physics.hpp"
#include "raylib-cpp.hpp"
#include "utils.hpp"

#include <vector>

void DrawScene(std::vector<Card *> cards);

void loadBackgroundTexture(const std::string &filename);

void unloadBackgroundTexture();

extern Texture2D backgroundTexture;
extern bool backgroundTextureLoaded;
