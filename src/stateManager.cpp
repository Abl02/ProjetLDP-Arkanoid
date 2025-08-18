#include "stateManager.hpp"

#include "entity.hpp"
#include "level.hpp"

StateManager::StateManager(LevelSPtr level) : lvl(level) {}

StateManager::~StateManager() {}

void StateManager::movePaddleRight() {
  lvl->movePaddleRight();
}
void StateManager::movePaddleLeft() { 
  lvl->movePaddleLeft();
}
/*void StateManager::launchBall() { //original
  lvl->launchBall();
}*/

void StateManager::launchBall() { // debug
    if (LOG) std::cerr << "|StateManager::launchBall() called\n";
    if (lvl && lvl->getBall().isBallAttached()) {
        lvl->launchBall();
    } 
}

void StateManager::update(float deltaTime) {
    lvl->update(deltaTime); // Update game entities
    lvl->checkAllCollision(); // No collision logic here
}
bool StateManager::isVictory() const {
    return lvl->allBricksDestroyed();
}
void StateManager::checkAllCollision() {
    for (auto& mask : lvl->getCollisionMasks()) {
        for (auto* entityG : mask.group) {
            if (auto* ball = dynamic_cast<Ball*>(entityG)) {
                for (auto* entityM : mask.masked) {
                    if (auto* other = dynamic_cast<Paddle*>(entityM)) {
                        if (ball->checkCollision(other)) {
                            ball->collisionDetected(other, ball->colPoint);
                            other->collisionDetected(ball, ball->colPoint);
                        }
                    }
                    else if (auto* brick = dynamic_cast<Brick*>(entityM)) {
                        if (ball->checkCollision(brick)) {
                            ball->collisionDetected(brick, ball->colPoint);
                            brick->collisionDetected(ball, ball->colPoint);
                        }
                    }
                }
            }
        }
    }
}
