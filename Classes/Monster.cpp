#include "Monster.h"
#include "SceneBase.h"
USING_NS_CC;




bool Rabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    //// ��ʼ���������ۺ�����
    //this->initWithFile("tuzi1.png");

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    // ��ʼ��HP
    maxHP = HP = 100;
    // ��ʼ����ɱ����
    value = 50;
    // ��ʼ���ٶ�
    speed = 30;
    // ��ʼ���뾶
    radius = 10;

    return true;
}

void Rabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
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

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 8; i >= 1; i--) {
        char filename[100];
        sprintf(filename, "tuzi%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.08f);
    animation->setLoops(-1);

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate,sequence,nullptr)); // ִ�����ж���
}

bool FlyingRabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���������ۺ�����
    // ��ʼ��HP
    maxHP = HP = 100;
    // ��ʼ����ɱ����
    value = 50;
    // ��ʼ���ٶ�
    speed = 30;
    // ��ʼ���뾶
    radius = 10;

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    return true;
}

void FlyingRabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
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

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 1; i <= 5; i++) {
        char filename[100];
        sprintf(filename, "fei%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 110, 110));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.08f);
    animation->setLoops(-1);

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate, sequence, nullptr)); // ִ�����ж���
}

bool FastrRabbit::init() {
    if (!Sprite::init()) {
        return false;
    }

    // ��ʼ���������ۺ�����
    // ��ʼ��HP
    maxHP = HP = 100;
    // ��ʼ����ɱ����
    value = 50;
    // ��ʼ���ٶ�
    speed = 50;
    // ��ʼ���뾶
    radius = 10;

    cocos2d::ui::Button* BUTTON = cocos2d::ui::Button::create("cat.png");
    BUTTON->setOpacity(0);
    BUTTON->addClickEventListener([this](Ref* sender) {
        // ����ť����¼�
        setAllTarget();
        });
    BUTTON->setPosition(Vec2(50, 50));
    addChild(BUTTON);

    return true;
}

void FastrRabbit::moveToSequence(const std::vector<cocos2d::Vec2>& positions)
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

    // ����һ���յĶ�������
    auto animation = Animation::create();
    // ��Ӷ���֡
    for (int i = 1; i <= 2; i++) {
        char filename[100];
        sprintf(filename, "fastr%d.png", i);
        auto frame = SpriteFrame::create(filename, Rect(0, 0, 100, 100));
        animation->addSpriteFrame(frame);
    }

    // ���ö�������
    animation->setDelayPerUnit(0.2f);
    animation->setLoops(-1);

    // ����������������
    auto animate = Animate::create(animation);

    // ����������Ӧ�õ����������
    this->runAction(Spawn::create(animate, sequence, nullptr)); // ִ�����ж���
}