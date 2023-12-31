#include "SceneBase.h"
#include "SimpleAudioEngine.h"//Cocos2d-x��Ϸ�����е���Ƶ������ͷ�ļ�
#include "Obstacle.h"
#include "Monster.h"
#include "Tower.h"
#include "TowerPosition.h"
#include "ui/CocosGUI.h"
#include "levelScene.h"

USING_NS_CC; //using namespace cocos2d

Sprite* plusIcon;

SceneBase* SceneBase::createScene(int level, LevelScene* levelScene)
{
    SceneBase* scene = new SceneBase();
    if (scene && scene->init(level, levelScene))
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
    return scene;
}

// ��ӡ���õĴ�����Ϣ�����������ļ�������ʱ�δ���
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

cocos2d::Vec2 SceneBase::getCarrotPosition() const
{
    return this->carrotPosition;
}

void SceneBase::setCarrotPosition(cocos2d::Vec2 position)
{
    this->carrotPosition = position;
}

void SceneBase::update(float delta)
{
    time += delta;
    if (monsterFlag)
    {
        int num = 0;
        // ���������е����нڵ�
        for (auto child : this->getChildren())
        {
            // �жϸýڵ��Ƿ�Ϊ Monster ����
            auto monster = dynamic_cast<Monster*>(child);
            if (monster != nullptr)
            {
                num++;
            }
        }
        if (num == 0 && carrotHP > 0)
        {
            this->setButton(true);
        }
    }
}

void SceneBase::takeCarrotDamage(int damage)
{
    if (carrotHP > damage)
    {
        carrotHP -= damage;
        if (carrotHP == 9)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot7_9 = Sprite::create("luobo7-9.png");
            Carrot7_9->setPosition(carrotPosition);
            this->m_carrot = Carrot7_9;
            this->addChild(Carrot7_9, 1);
        }
        if (carrotHP == 6)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot4_6 = Sprite::create("luobo4-6.png");
            Carrot4_6->setPosition(carrotPosition);
            this->m_carrot = Carrot4_6;
            this->addChild(Carrot4_6, 1);
        }
        if (carrotHP == 3)
        {
            this->removeChild(m_carrot);
            Sprite* Carrot1_3 = Sprite::create("luobo1-3.png");
            Carrot1_3->setPosition(carrotPosition);
            this->m_carrot = Carrot1_3;
            this->addChild(Carrot1_3, 1);
        }
    }
    else
    {
        carrotHP = 0;
        this->setButton(false);
    }
}

/*
* ��ʾ������
* 0�㣺��ͼ����
* 1�㣺�ܲ��������ĵ�����Ǯ
* 2�㣺���õ��������ӵ�
* 3�㣺����λ�õļӺš��Ӻ�����Ŀ�ѡ������ť
* 4�㣺������
* 5�㣺��������
* 6�㣺������������İ�ť
*/
void SceneBase::initScene(std::string& mapName)
{
    auto map = TMXTiledMap::create(mapName);
    this->addChild(map, 0);     // ��ӵ������У���ʾ�ڵ�0��

    // ��ȡ�ܲ������
    TMXObjectGroup* carrotObjects = map->getObjectGroup("Carrot");

    // ��ȡ�ܲ������λ����Ϣ
    const auto& firstCarrotObject = carrotObjects->getObjects().at(0);
    float xC = firstCarrotObject.asValueMap().at("x").asFloat() + 60;
    float yC = firstCarrotObject.asValueMap().at("y").asFloat() + 70;

    // �����ܲ��������ڵ�ͼ�ϵ�λ��
    Vec2 carrotPos = Vec2(xC, yC);
    Sprite* carrot = Sprite::create("luobo.png");
    carrot->setPosition(carrotPos);
    this->addChild(carrot, 1);      // ��ӵ������У���ʾ�ڵ�1�㣬ȷ���ڵ�ͼ�Ϸ���ʾ
    this->carrotPosition = carrotPos;
    this->m_carrot = carrot;

    TMXObjectGroup* towerPositions = map->getObjectGroup("TowerPosition");
    // ����λ�ö���
    ValueVector towerPositionsVector = towerPositions->getObjects();

    for (const auto& towerPosition : towerPositionsVector)
    {
        // ��ȡ����λ�ö����λ����Ϣ
        float xP = towerPosition.asValueMap().at("x").asFloat() + 50;
        float yP = towerPosition.asValueMap().at("y").asFloat() + 50;

        // ��������λ�ò������ڵ�ͼ��
        Vec2 position = Vec2(xP, yP);
        TowerPosition* towerPos = TowerPosition::create();
        towerPos->setPosition(position);
        towerPos->setVisible(false);        // ��ʼ��ʱ����Ϊ����״̬
        this->addChild(towerPos, 3);        // ��ӵ������У���ʾ�ڵ�3�㣬ȷ���ڵ�ͼ�Ϸ���ʾ

    }

    // �������¼������������ڴ�������λ�ö������ʾ������
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [&](Touch* touch, Event* event) {
        auto children = this->getChildren();
        for (Node* child : children)
        {
            TowerPosition* towerPos = dynamic_cast<TowerPosition*>(child);
            // ������ķ���
            if (towerPos && towerPos->getBoundingBox().containsPoint(touch->getLocation()))
            {
                // ��ǰλ������
                if (towerPos->towerofThisPosition)
                {
                   // towerPos->setVisible(false);

                    // ������ť
                    Vec2 positionUp = Vec2(40, 120);
                    Vec2 positionDelete = Vec2(40, -40);

                    if (dynamic_cast<BottleTower_1*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("BottleUpgrade1.png", "BottleUpgrade1.png", "BottleUpgradeUn1.png");
                        towerUp->setPosition(positionUp);
                        //towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::updateBottle1, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 10, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<BottleTower_2*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("BottleUpgrade2.png", "BottleUpgrade2.png", "BottleUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 250)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove2.png", "BottleRemove2.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<BottleTower_3*>(towerPos->towerofThisPosition)) {
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_1*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "StarUpgradeUn1.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_2*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<StarTower_3*>(towerPos->towerofThisPosition)) {
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("StarRemove3.png", "StarRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_1*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade1.png", "StarUpgrade1.png", "BottleUpgradeUn3.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove1.png", "BottleRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_2*>(towerPos->towerofThisPosition)) {
                        // ������ť
                        auto towerUp = cocos2d::ui::Button::create("StarUpgrade2.png", "StarUpgrade2.png", "StarUpgradeUn2.png");
                        towerUp->setPosition(positionUp);
                        towerUp->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerUp, 0, "BottleButton");
                        // ���õ��״̬
                        if (this->moneyScene >= 150)
                        {
                            towerUp->setEnabled(true);
                        }
                        else
                        {
                            towerUp->setEnabled(false);
                        }
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("BottleRemove3.png", "BottleRemove3.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    else if (dynamic_cast<SunflowerTower_3*>(towerPos->towerofThisPosition)) {
                        // ɾ����ť
                        auto towerDelete = cocos2d::ui::Button::create("StarRemove1.png", "StarRemove1.png");
                        towerDelete->setPosition(positionDelete);
                        towerDelete->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                        towerPos->addChild(towerDelete, 0, "BottleButton");
                    }
                    
                }
                // û��������ʾ�������
                else {
                    towerPos->setVisible(true);
                    // ������ť
                    Vec2 positionButtonBottle = Vec2(40, 120);
                    Vec2 positionButtonStar = Vec2(-40, 120);
                    Vec2 positionButtonSunflower = Vec2(120, 120);
                    Vec2 positionCheck = towerPos->getPosition();
                    if (positionCheck.x == 50)      //���λ�ý������Ե���Խ����İ�ť���������д���ʹ��ť��ʾ���Ҳ�
                    {
                        positionButtonBottle = Vec2(120, 40);
                        positionButtonStar = Vec2(120, 120);
                        positionButtonSunflower = Vec2(120, -40);
                    }
                    auto buttonBottle = cocos2d::ui::Button::create("BottleButton.png", "BottleButton.png", "BottleButtonUn.png");
                    buttonBottle->setPosition(positionButtonBottle);
                    buttonBottle->addClickEventListener(CC_CALLBACK_1(SceneBase::createBottle, this));  // ��Ӱ�ť����ص�����
                    towerPos->addChild(buttonBottle, 0, "BottleButton");
                    // ���õ��״̬
                    if (this->moneyScene >= 100) {
                        buttonBottle->setEnabled(true);
                    }
                    else {
                        buttonBottle->setEnabled(false);
                    }

                    towerPos->setVisible(true);
                    // ������ť
                    
                    auto buttonStar = cocos2d::ui::Button::create("StarButton.png", "StarButton.png", "StarButtonUn.png");
                    buttonStar->setPosition(positionButtonStar);
                    buttonStar->addClickEventListener(CC_CALLBACK_1(SceneBase::createStar, this));  // ��Ӱ�ť����ص�����
                    towerPos->addChild(buttonStar, 0, "StarButton");
                    // ���õ��״̬
                    if (this->moneyScene >= 200) {
                        buttonStar->setEnabled(true);
                    }
                    else {
                        buttonStar->setEnabled(false);
                    }

                    towerPos->setVisible(true);
                    // ������ť
                    
                    auto buttonSunflower = cocos2d::ui::Button::create("SunflowerButton.png", "SunflowerButton.png", "SunflowerButtonUn.png");
                    buttonSunflower->setPosition(positionButtonSunflower);
                    buttonSunflower->addClickEventListener(CC_CALLBACK_1(SceneBase::createSunflower, this));  // ��Ӱ�ť����ص�����
                    towerPos->addChild(buttonSunflower, 0, "SunflowerButton");
                    // ���õ��״̬
                    if (this->moneyScene >= 200) {
                        buttonSunflower->setEnabled(true);
                    }
                    else {
                        buttonSunflower->setEnabled(false);
                    }
                }
            }
            // û�б�����ķ���
            else if (towerPos)
            {
                towerPos->setVisible(false);
                
                // ���Һ��Ƴ����еĽ��찴ť
                cocos2d::ui::Button* spriteBottle = static_cast<cocos2d::ui::Button*>(this->getChildByName("BottleButton"));
                if (spriteBottle) {
                    // �ӽڵ���ڣ����Խ����Ƴ�����
                    this->removeChildByName("BottleButton");
                }

                cocos2d::ui::Button* spriteStar = static_cast<cocos2d::ui::Button*>(this->getChildByName("StarButton"));
                if (spriteStar) {
                    // �ӽڵ���ڣ����Խ����Ƴ�����
                    this->removeChildByName("StarButton");
                }

                cocos2d::ui::Button* spriteSunflower = static_cast<cocos2d::ui::Button*>(this->getChildByName("SunflowerButton"));
                if (spriteSunflower) {
                    // �ӽڵ���ڣ����Խ����Ƴ�����
                    this->removeChildByName("SunflowerButton");
                }
            }
        }
        return true;
        };

    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

}

void SceneBase::menuCloseCallback(Ref* pSender)
{
    //���������ֹͣ��Ϸѭ�������ͷ����е���Դ��
    Director::getInstance()->end();

    //���ϣ����iOS�з���ԭ������������˳�Ӧ�ó��򣬿���ע�͵��������������������Ĵ��룬
    //����һ����Ϊ��game_scene_close_event�����Զ����¼�����RootViewController.mm�ļ��еĴ��봦��

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
}

void SceneBase::createBottle(cocos2d::Ref* sender)
{
    // �ڵ�ǰλ�ô�������
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = BottleTower_1::create();  // ������������
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // ��������λ��
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // ��������ӵ�������
            button->getParent()->setVisible(false);

            this->updateMoney(-100);
        }
    }
}

void SceneBase::createStar(cocos2d::Ref* sender)
{
    // �ڵ�ǰλ�ô�����������
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = StarTower_1::create();  // ������������
        if (moneyScene >= tower->getConsumption())
        {
            //auto bottom = Sprite::create("Bottom.png");
            //bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // ��������λ��
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            //this->addChild(bottom, 1);
            this->addChild(tower, 2);  // ��������ӵ�������
            button->getParent()->setVisible(false);

            this->updateMoney(-200);
        }
    }
}

void SceneBase::createSunflower(cocos2d::Ref* sender)
{
    // �ڵ�ǰλ�ô���̫��������
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = SunflowerTower_1::create();  // ������������
        if (moneyScene >= tower->getConsumption())
        {
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // ��������λ��
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // ��������ӵ�������
            button->getParent()->setVisible(false);

            this->updateMoney(-200);
        }
    }
}

// on "init" you need to initialize your instance
bool SceneBase::init(int level, LevelScene* levelScene)
{
    // �����˸���Scene��init()�������г�ʼ���������ʼ��ʧ�ܣ��򷵻�false
    if (!Scene::init())
    {
        return false;
    }

    m_levelScene = levelScene;
    // ������ʱ������ʱ���¹���״̬
    scheduleUpdate();
    return true;
}


void SceneBase::setButton(bool flag)
{
    if (flag)
    {
        auto closeWin = Sprite::create("WinPicture.png");
        closeWin->setPosition(Vec2(650, 400));
        this->addChild(closeWin, 5, "WinBackground");

        auto continueGame = MenuItemImage::create(
            "ContinueGame.png",
            "ContinueGame.png",
            CC_CALLBACK_0(SceneBase::onGameWin, this));
        auto menuContinue = Menu::create(continueGame, nullptr);
        menuContinue->setPosition(Vec2(650, 265));    // ���ð�ťλ��
        this->addChild(menuContinue, 6, "ContinueGame");
        //Director::getInstance()->pause();           // ��ͣ��Ϸ
    }
    else
    {
        auto closeFail = Sprite::create("FailPicture.png");
        closeFail->setPosition(Vec2(650, 420));
        this->addChild(closeFail, 5, "FailBackground");

        auto goBack = MenuItemImage::create(
            "GoBack.png",
            "GoBack.png",
            CC_CALLBACK_0(SceneBase::onGameFail, this));
        auto menuBack = Menu::create(goBack, nullptr);
        menuBack->setPosition(Vec2(650, 265));      // ���ð�ťλ��
        this->addChild(menuBack, 6, "GoBack");
        Director::getInstance()->pause();           // ��ͣ��Ϸ
    }
}

void SceneBase::onGameWin()
{
    // ��Ϸ���ʱ���ô˺���
    if (m_levelScene)
    {
        //Director::getInstance()->resume();          // �ָ���Ϸ
        int nextLevel = m_level + 1;
        m_levelScene->money += 100;
        m_levelScene->unlockLevel(nextLevel);       // ������һ��
        Director::getInstance()->popScene();        // ���ص���һ������
    }
}

void SceneBase::onGameFail()
{
    // ��Ϸ���ʱ���ô˺���
    if (m_levelScene)
    {
        Director::getInstance()->resume();          // �ָ���Ϸ
        Director::getInstance()->popScene();        // ���ص���һ������
    }
}

void SceneBase::addMoney(int money)
{
    this->moneyScene += money;
}

void SceneBase::updateMoney(int money)
{
    moneyScene += money;
    this->removeChild(m_lable);
    std::string text = std::to_string(moneyScene); // ������ת��Ϊ�ַ���
    auto lable = Label::createWithTTF(text, "fonts/arial.ttf", 48);
    lable->setPosition(Vec2(260, 763));
    this->m_lable = lable;
    this->addChild(m_lable, 1);
}

void SceneBase::updateBottle1(cocos2d::Ref* sender)
{
    // �ڵ�ǰλ�ô�������
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    if (button)
    {
        auto tower = BottleTower_2::create();  // ������������
        if (moneyScene >= tower->getConsumption())
        {
            button->getParent()->removeAllChildren();
            auto bottom = Sprite::create("Bottom.png");
            bottom->setPosition(button->getParent()->getPosition());
            tower->setPosition(button->getParent()->getPosition());  // ��������λ��
            auto thisTowerPosition = dynamic_cast<TowerPosition*> (button->getParent());
            if (thisTowerPosition)
            {
                thisTowerPosition->towerofThisPosition = tower;
            }
            this->addChild(bottom, 1);
            this->addChild(tower, 2);  // ��������ӵ�������
            button->getParent()->setVisible(false);

            this->updateMoney(-150);
        }
    }
}