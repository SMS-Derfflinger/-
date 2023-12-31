#ifndef __CARROT_H__
#define __CARROT_H__

// ����ͷ�ļ�
#include "cocos2d.h"

USING_NS_CC;

// ����һ���ܲ���
class Carrot : public cocos2d::Sprite
{
private:
    // Ѫ��
    int HP;
    cocos2d::Vec2 position;
public:
    void takeDamage(int damage);
    // ��ʼ������
    void setCarrotPosition(cocos2d::Vec2 pos);
    cocos2d::Vec2 getCarrotPosition() const;
    virtual bool init() override;
    CREATE_FUNC(Carrot);
};

#endif // __CARROT_H__