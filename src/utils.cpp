#include "utils.hpp"

vec2 lerp(vec2 a, vec2 b, float t) {
  a.x += (b.x - a.x) * t;
  a.y += (b.y - a.y) * t;
  return a;
}
