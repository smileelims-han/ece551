#include "circle.hpp"

#include "math.h"
Circle::Circle(Point p, const double r) : cp(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  cp.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dis_cp = cp.distanceFrom(otherCircle.cp);
  double angle_1 =
      acos((radius * radius + dis_cp * dis_cp - otherCircle.radius * otherCircle.radius) /
           (2 * radius * dis_cp));
  double angle_2 =
      acos((otherCircle.radius * otherCircle.radius + dis_cp * dis_cp - radius * radius) /
           (2 * otherCircle.radius * dis_cp));
  double area = angle_1 * radius * radius +
                angle_2 * otherCircle.radius * otherCircle.radius -
                radius * dis_cp * sin(angle_1);
  return area;
}
