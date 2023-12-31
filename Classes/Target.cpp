#include "Target.h"
#include "SceneBase.h"
#include "Tower.h"

USING_NS_CC;


void Target::setAllTarget() {
    Vector<Node*> enemies = getScene()->getChildren();
    Target* nearestEnemy = nullptr;
    float minDistance = 999999;
    for (auto node : enemies) {
        auto tower = dynamic_cast<Tower*>(node);
        if (tower) {
            tower->setTarget(this);
        }
    }
}

void Target::takeDamage(int damage) {
    HP -= damage;
    if (HP <= 0) {
        auto scene = dynamic_cast<SceneBase*>(this->getParent());
        if (scene)
        {
            scene->updateMoney(value);
        }
        // ���������������Ƴ�Ŀ��
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// ����
            RemoveSelf::create(),
            nullptr
        ));
    }
    if (!Progress) {
        // ����һ������������
        auto progress = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("ProgressAfter.png"));
        Sprite* progressBackground = Sprite::create("ProgressInit.png");
        progress->setType(cocos2d::ProgressTimer::Type::BAR);
        progress->setMidpoint(cocos2d::Vec2(0, 0.5));  // ���ý��������Ϊ����м�λ��
        progress->setBarChangeRate(cocos2d::Vec2(1, 0));  // ���ý������Ŀ����ٷֱȱ仯

        // ��������������ӵ�����ͷ����
        this->addChild(progressBackground);
        this->addChild(progress);
        progress->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        progressBackground->setPosition(cocos2d::Vec2(this->getContentSize().width / 2, this->getContentSize().height));
        this->Progress = progress;
    }
    if (HP < maxHP&& Progress) {
        // ���ý������İٷֱ�
        float percent = static_cast<float>(HP * 100 / maxHP);
        this->Progress->setPercentage(percent);
    }
}

bool Target::isAlive() const {
    return HP > 0;
}

void Target::setHP(int HP) {
    this->HP = HP;
    if (HP <= 0) {
        // ���������������Ƴ�Ŀ��
        this->runAction(Sequence::create(
            FadeOut::create(0.25f),// ����
            RemoveSelf::create(),
            nullptr
        ));

    }
}

int Target::getRadius() {
    return radius;
}