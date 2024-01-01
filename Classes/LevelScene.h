#ifndef __LEVEL_SCENE_H__
#define __LEVEL_SCENE_H__
#include "cocos2d.h"
class GameScene; // ���� GameScene ��
class LevelScene : public cocos2d::Scene
{
public:
    static LevelScene* create();
    void unlockLevel(int level);
    virtual bool init();
    bool m_unlockedLevels[3];
    int m_unlockedLevel1;
    int m_unlockedLevel2 ;
    int m_unlockedLevel3 ;
    void selectLevel1(cocos2d::Ref* sender);
    void selectLevel2(cocos2d::Ref* sender);
    void selectLevel3(cocos2d::Ref* sender);
    int m_unlockLevel ;// �����ѽ����Ĺؿ����
    cocos2d::MenuItemImage* m_level1Button;
    cocos2d::MenuItemImage* m_level2Button;
    cocos2d::MenuItemImage* m_level3Button;
    void updateButtonState();
    cocos2d::Sprite* m_gameImage; // mubu
    int money;//�������
    cocos2d::Label* m_moneyLabel;//��ʾǮ
    void consumeMoney(int n);//��Ǯ
    int getMoney();//����Ǯ
    void enterUpgradeScene(cocos2d::Ref* sender);
    int skill1 = 0;//���ܵȼ�
    //int skill2 = 0;
    void upgradeItem1();//��ȡ���ܵȼ��뷵��
    //void upgradeItem2();
    int getItem1Level();
    //int getItem2Level();
private:
    
    cocos2d::Scene* m_gameScene; // ���� GameScene ������ָ��
};

#endif // __LEVEL_SCENE_H__