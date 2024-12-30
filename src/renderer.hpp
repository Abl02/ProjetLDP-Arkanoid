#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Entity;
class Level;
class BrickHolder;
class Brick;

typedef std::shared_ptr<const Level> ConstLevelSPtr;

class Renderer {
 private:
  ConstLevelSPtr lvl;

 public:
  Renderer(ConstLevelSPtr);
  ~Renderer();
  void refresh();

  void drawnBackground();
  void renderType(Entity*);
  void render(BrickHolder*);
  void render(Brick*);
  // add new render methodes with other parameters
};

#endif
