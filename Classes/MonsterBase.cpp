#include "MonsterBase.h"
#include "SceneBase.h"
#include "Tower.h"

USING_NS_CC;



void Monster::moveTo(cocos2d::Vec2 position)
{
    this->stopAllActions(); // ֹͣ��ǰ�����еĶ���
    auto distance = position - this->getPosition(); // �����ƶ�����
    auto duration = distance.length() / speed; // �����ƶ�ʱ��

    auto move = cocos2d::MoveTo::create(duration, position); // �����ƶ�����
    this->runAction(move); // ִ���ƶ�����
}

void Monster::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
{
    this->stopAllActions(); // ֹͣ��ǰ�����еĶ���

    Vector<FiniteTimeAction*> actions; // ����һ����������
    cocos2d::Vec2 thisPosition = this->getPosition();
    for (cocos2d::Vec2 position : positions)
    {
        auto distance = position - thisPosition; // �����ƶ�����
        thisPosition = position;
        auto duration = distance.length() / speed; // �����ƶ�ʱ��
        auto move = MoveTo::create(duration, position); // �����ƶ�����
        actions.pushBack(move); // ���ƶ�������ӵ�������
    }

    auto attacked = CallFunc::create([=]() {
        auto target = this->getParent();
        auto scene = dynamic_cast<SceneBase*>(target);
        scene->takeCarrotDamage(1);
        this->setHP(0);

        });
    auto sequenceAction = Sequence::create(actions); // �������ж���
    auto sequence = Sequence::create(sequenceAction, attacked, nullptr);

    this->runAction(sequence); // ִ�����ж���
}
