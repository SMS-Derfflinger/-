#ifndef __TARGET_H__
#define __TARGET_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class Target : public cocos2d::Sprite {
public:
    // ������
    virtual ~Target() {};
    // ����
    virtual void takeDamage(int damage);
    // �ж��Ƿ���
    bool isAlive() const;
    // ����Ѫ��
    void setHP(int HP);
    // ��ȡ�뾶
    int getRadius();
    void setAllTarget();


protected:
    int HP;  // Ѫ��
    int maxHP; // ���Ѫ��
    int value;// ��ɱ����
    int radius;// �뾶
    cocos2d::ProgressTimer* Progress = nullptr;// �����������ָ��
    Target() {};// �ܱ����Ĺ��캯��
};

#endif // __TARGET_H__