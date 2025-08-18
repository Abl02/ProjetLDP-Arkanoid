#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <string>
#include <sys/types.h>
#include <unordered_set>
#include <vector>

#include "entity.hpp"
#include "utils.hpp"

struct CollisionGroup { // Represents a group of entities that can collide with each other
  std::vector<Entity*> group;
  std::vector<Entity*> masked;
};

class Level { // Represents a game level containing bricks, paddle, ball, and bonuses
  friend class LevelLoader; // <--- Give LevelLoader access to private members

private:
  int _lives;
  int _score;

  // Here add all Game Entities
  std::unique_ptr<BrickHolder> bricks;
  std::unique_ptr<Paddle> paddle;
  std::unique_ptr<Ball> ball;
  std::vector<Bonus*> activeBonuses;
  std::vector<std::unique_ptr<Ball>> extraBalls;
  struct TimedBonus {
    char type;
    float remainingTime;
};
std::vector<TimedBonus> activeTimedBonuses;

public:
  std::string levelName;
  void setDefaults();
  void addToScore(int);
  void gainLive();
  void loseLive();
  void update(float deltaTime);
  void applyBonus(Bonus* bonus);
  void addActiveBonus(Bonus* bonus); // Adds a bonus to the active bonuses list
  Paddle& getPaddle(); // allows modification to paddle
  const Paddle& getPaddle() const; // read-only access to paddle

  

  int getScore() const;
  int& getScoreRef();
  int getLives() const;
  int& getLivesRef();

  // Public interface to control game entities
  void movePaddleLeft();
  void movePaddleRight();
  void launchBall();

  // Access to read-only entity 
  const BrickHolder& getBricks() const;
  const Ball& getBall() const;
  bool allBricksDestroyed() const;
  void checkAllCollision();

  std::vector<Entity*> all() const;
  std::vector<CollisionGroup> getCollisionMasks() const;
  // Access to active bonuses (read-only)
const std::vector<Bonus*>& getActiveBonuses() const;

};

class LevelLoader { // Loads levels from files and provides level data
  // This class is responsible for reading level files, validating their format,
  // and extracting the necessary data to create a Level object.
  // It also provides methods to load default levels and reload level files.
 private:
  std::vector<std::string> levelNames;
  std::vector<std::vector<BRICK_CONST::Param>> levelDatas;
  void registerLevelFiles();
  bool isValidLevelFormat(const std::string& levelPath);
  std::vector<BRICK_CONST::Param>
    extractLevelData(const std::string& levelPath);
 public:
  LevelLoader();
  ~LevelLoader();
  void load(size_t levelIndex, Level* lvl, bool resetFlag);
  void loadDefault(Level* lvl);
  size_t levelCount();
  bool isEmpty();
  void reloadFiles();
 private:
  const std::unordered_set<std::string> validColor = {
    "white","orange","cyan","green","red","blue","magenta","yellow","silver","gold"};
  const std::unordered_set<std::string> validBonus = {
    "none","laser","bigger","capture","slow","interruption","player"};
  bool validateRow(int row);
  bool validateCol(int col);
  bool validateColor(std::string color);
  bool validateBonus(std::string bonus);
};

#endif
