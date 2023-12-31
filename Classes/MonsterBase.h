#ifndef __MONSTERBASE_H__
#define __MONSTERBASE_H__

#include "Target.h"

class Monster : public Target {
public:
    // �ƶ���ָ��λ��
    void moveTo(cocos2d::Vec2 position);
    virtual void moveToSequence(const std::vector<cocos2d::Vec2>& positions);
    // ������
    virtual ~Monster() {};

 

protected:
    int speed;
    Monster() {};// �ܱ����Ĺ��캯��
};

#endif // __MONSTERBASE_H__