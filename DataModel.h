#pragma once

class DataModel
{
public:
    virtual void draw() = 0;
    virtual bool isInsideGeometry(float x, float y) = 0;
    virtual void drag(float x, float y) = 0;
};