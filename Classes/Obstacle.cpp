#include "Obstacle.h"

bool TestObstacle::init() {
    if (!Sprite::init()) {
        return false;
    }


    // ��ʼ���ϰ������ۺ�����
    this->initWithFile("CloseNormal.png");
    // ��ʼ��HP����ֵ�Ͱ뾶
    maxHP = HP = 100;
    value = 50;
    radius = 50;

    return true;
}