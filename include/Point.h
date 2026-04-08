// Point.h
#pragma once
#include <vector>

struct Point {
    float x, y;
    Point(float x = 0, float y = 0);
    bool operator==(const Point& other) const;
    bool operator!=(const Point& other) const;
};

// Геометрические константы
extern const float WORK_AREA_MIN_X;
extern const float WORK_AREA_MAX_X;
extern const float WORK_AREA_MIN_Y;
extern const float WORK_AREA_MAX_Y;

// Геометрические функции
void clampPoint(Point& point);
float orientation(const Point& pivot, const Point& p, const Point& q);
float distSq(const Point& pivot, const Point& p);
// Encoding fix check