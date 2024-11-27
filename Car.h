#ifndef CAR_H
#define CAR_H

#include <GL/freeglut.h>
#include <cmath>

class Car
{
    private:
        float posX, posZ, angleY, speed;
    float wheelRotation;
    static constexpr float maxSpeed = 0.2f;
    static constexpr float acceleration = 0.01f;
    static constexpr float friction = 0.005f;

    void drawBody();
    void drawWheels();
    void drawHeadlights();

public:
    Car();
    void moveForward();
    void moveBackward();
    void rotate(float angle);
    void applyFriction();
    void draw();



};

#endif