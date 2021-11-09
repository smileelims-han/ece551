#include "point.hpp"

class Circle {
  Point cp;
  const double radius;

 public:
  Circle(Point p, const double r);
  void move(double dx, double dy);
  double intersectionArea(const Circle & otherCircle);
};
