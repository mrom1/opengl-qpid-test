#pragma once

class Points
{
public:
    float x, y, z;
    Points()
    {
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }

    Points(float _x, float _y) : x(_x), y(_y), z(0.0) {}
    Points(float _x, float _y, float _z) : x(_x), y(_y), z(_z) {}
};