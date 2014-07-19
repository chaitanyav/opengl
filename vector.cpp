#include <iostream>
#include <cmath>
#include <cassert>

class Vector {

public:

  float x;
  float y;

  Vector(float x_, float y_) : x(x_), y(y_) {
  }

  void add(Vector &v) {
    y = y + v.y;
    x = x + v.x;
  }

  void sub(Vector &v) {
    x = x - v.x;
    y = y - v.y;
  }

  void mult(float n) {
    x = n * x;
    y = n * y;
  }

  void div(float n) {
    x = x / n;
    y = y / n;
  }

  float magnitude() {
    return (float)sqrt(x * x + y * y);
  }

  void normalize() {
    float m = magnitude();
    if(m != 0) {
      div(m);
    }
  }

  void limit(float max) {
    if (this->magnitude() > max) {
      normalize();
      mult(max);
    }
  }
};

int main(int argc, char *argv[]) {
  Vector v(1, 2);
  Vector a(3, 4);
  assert(v.x == 1.0f);
  assert(v.y == 2.0f);
  assert(a.x == 3.0f);
  assert(a.y == 4.0f);

  a.limit(5.0f);
  assert(a.x == 3.0f);
  assert(a.y == 4.0f);
  
  assert(a.magnitude() == 5.0f);
  v.add(a);
  assert(v.x == 4.0f);
  assert(v.y == 6.0f);

  v.sub(a);
  assert(v.x == 1.0f);
  assert(v.y == 2.0f);

  Vector b(6,6);
  b.div(6.0f);
  assert(b.x == 1.0f);
  assert(b.y == 1.0f);

  v.mult(3);
  assert(v.x == 3.0f);
  assert(v.y == 6.0f);

  a.normalize();
  assert(a.x == 0.6f);
  assert(a.y == 0.8f);
  return 0;
}
