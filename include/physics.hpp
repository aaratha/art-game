#pragma once

#include "utils.hpp"

class PhysObj {
private:
  vec2 pos;
  vec2 prev;
  vec2 targ;
  vec2 vel;

public:
  PhysObj();
  ~PhysObj();

  void Update(float dt);
};
