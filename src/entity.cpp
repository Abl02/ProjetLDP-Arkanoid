#include "entity.hpp"

#include <allegro5/allegro_primitives.h>
#include <allegro5/drawing.h>

// -------------------------------------------------------------------------
// TestRectangle
// -------------------------------------------------------------------------
TestRectangle::TestRectangle(tpl position, float width, float height,
                             ALLEGRO_COLOR color)
    : pos(position), w(width), h(height), col(color) {}

TestRectangle::~TestRectangle() {}

float TestRectangle::x() { return pos.x; };
float TestRectangle::y() { return pos.y; };

float TestRectangle::width() { return w; };
float TestRectangle::height() { return h; };

ALLEGRO_COLOR TestRectangle::color() { return col; };

void TestRectangle::move(int dx, int dy) {
  pos.x += dx;
  pos.y += dy;
}
