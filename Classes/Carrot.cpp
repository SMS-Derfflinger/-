#include "Carrot.h"

bool Carrot::init()
{
    if (!Sprite::init())
    {
        return false;
    }

    // ��ʼ���ϰ������ۺ�����
    this->initWithFile("luobo.png");

    // ��ʼ��HP
    HP = 10;

    return true;
}

void Carrot::takeDamage(int damage)
{
    if (HP > damage)
        HP -= damage;
    else
        HP = 0;
}

void Carrot::setCarrotPosition(cocos2d::Vec2 pos)
{
    this->position = pos;
}

Vec2 Carrot::getCarrotPosition() const
{
    return position;
}


