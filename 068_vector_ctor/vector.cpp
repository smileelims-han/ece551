#include "vector.hpp"

#include <cmath>
#include <cstdio>

/* write your class implementation in this file
 */
Vector2D::Vector2D() : x(0), y(0) {
}

Vector2D::Vector2D(double init_x, double init_y) : x(init_x), y(init_y) {
}

void Vector2D::initVector(double init_x, double init_y) {
  x = init_x;
  y = init_y;
}

double Vector2D::getMagnitude() const {
  double temp = x * x + y * y;
  return std::sqrt(temp);
}
Vector2D Vector2D::operator+(const Vector2D & rhs) const {
  Vector2D v_temp;
  v_temp.x = x + rhs.x;
  v_temp.y = y + rhs.y;
  return v_temp;
}
Vector2D & Vector2D::operator+=(const Vector2D & rhs) {
  x += rhs.x;
  y += rhs.y;
  return *this;
}

double Vector2D::dot(const Vector2D & rhs) const {
  return x * rhs.x + y * rhs.y;
}
void Vector2D::print() const {
  printf("<%.2f, %.2f>", x, y);
}
