#include "circle.hpp"

#include <cmath>
using namespace std;
#define _USE_MATH_DEFINES

Circle::Circle(Point p, const double r) : cp(p), radius(r) {
}

void Circle::move(double dx, double dy) {
  cp.move(dx, dy);
}

double Circle::intersectionArea(const Circle & otherCircle) {
  double dis_cp = cp.distanceFrom(otherCircle.cp);
  //when there is no radius
  if (radius == 0 || otherCircle.radius == 0) {
    return 0;
  }
  //when the two circles share same center point
  if (dis_cp <= fabs(radius - otherCircle.radius)) {
    if (radius >= otherCircle.radius) {
      return M_PI * otherCircle.radius * otherCircle.radius;
    }
    else {
      return M_PI * radius * radius;
    }
  }
  //when the two circles do not intersection each other
  if (dis_cp >= (radius + otherCircle.radius)) {
    return 0;
  }
  else {
    double angle_1 = acos(
        (radius * radius + dis_cp * dis_cp - otherCircle.radius * otherCircle.radius) /
        (2 * radius * dis_cp));
    double angle_2 = acos(
        (otherCircle.radius * otherCircle.radius + dis_cp * dis_cp - radius * radius) /
        (2 * otherCircle.radius * dis_cp));
    double area = angle_1 * radius * radius +
                  angle_2 * otherCircle.radius * otherCircle.radius -
                  radius * dis_cp * sin(angle_1);
    return area;
  }
}
