#include "physics.hpp"
#include "card.hpp"
#include <raylib.h>

PhysObj::PhysObj(vec2 pos) : pos(pos), prev(pos), targ(pos) {}

void PhysObj::updatePhysics(float dt) {
  const vec2 vel = pos - prev;
  prev = pos;
  pos += (vel * friction) + acc * dt * dt;
  acc = vec2(0, 0);
}

void PhysObj::accelerate(vec2 a) { acc += a; }

vec2 PhysObj::getPos() { return pos; }

vec2 PhysObj::getPrev() { return prev; }

vec2 PhysObj::getTarg() { return targ; }

void PhysObj::setPos(vec2 p) { pos = p; }

void PhysObj::setTarg(vec2 p) { targ = p; }

void Solver::update(float dt, std::vector<Card *> &cards) {
  applyForces();
  updatePositions(dt);
  applyCollisions(cards);
}

void Solver::updatePositions(float dt) {
  for (auto obj : objects) {
    obj->updatePhysics(dt);
  }
}

void Solver::applyCollisions(std::vector<Card *> &cards) {
  for (int i = 0; i < cards.size(); i++) {
    for (int j = i + 1; j < cards.size(); j++) {
      if (cards[i]->isDragging || cards[j]->isDragging) {
        continue;
      }
      if (CheckCollisionRecs(cards[i]->getRect(), cards[j]->getRect())) {
        Rectangle rectA = cards[i]->getRect();
        Rectangle rectB = cards[j]->getRect();

        float overlapX = std::min(rectA.x + rectA.width - rectB.x,
                                  rectB.x + rectB.width - rectA.x);
        float overlapY = std::min(rectA.y + rectA.height - rectB.y,
                                  rectB.y + rectB.height - rectA.y);

        Vector2 separation;
        if (overlapX < overlapY) {
          separation = {(rectA.x < rectB.x ? -overlapX : overlapX) / 2, 0};
        } else {
          separation = {0, (rectA.y < rectB.y ? -overlapY : overlapY) / 2};
        }

        // Move each card by half the overlap distance
        cards[i]->setPos(cards[i]->getPos() + separation);
        cards[j]->setPos(cards[j]->getPos() - separation);
      }
    }
  }
}

void Solver::applyForces() {
  for (auto obj : objects) {
    // Apply gravity when the mouse button is not down
    obj->accelerate(g);
  }
}
