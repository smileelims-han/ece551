#include "point.hpp"

#include "math.h"

Point::Point() : x(0), y(0) {
}
void Point::move(double dx, double dy) {
  x = x + dx;
  y = y + dy;
}

double Point::distanceFrom(const Point & p) {
  double x_dis, y_dis, ans;
  x_dis = x - p.x;
  y_dis = y - p.y;
  ans = sqrt((x_dis * x_dis) + (y_dis * y_dis));
  return ans;
}
