#pragma once
class Bullet
{
private:
    POINT _position;
    
    float _speedX;
    float _speedY;

    float _angleD;
    float _angleR;

    float _speed;

public:
    Bullet();
    ~Bullet();

    void setPosition(POINT p) { _position = p; }
    POINT getPosition(){ return _position; }

    void setAngleD(float angleD);
    float getAngleD();

    void setAngleR(float angleR);
    float getAngleR();

    void setSpeedX(float speedX);
    float getSpeedX();

    void setSpeedY(float speedY);   
    float getSpeedY();

    void setSpeed(float speed);
    float getSpeed();

    void move();
    void moveGravity();

    bool isFire = false;
};

