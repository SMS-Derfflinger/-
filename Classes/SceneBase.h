#ifndef __SCENCEBASE_SCENE_H__
#define __SCENCEBASE_SCENE_H__

#include "LevelScene.h"
#include "cocos2d.h"
#include "Target.h"

USING_NS_CC; //using namespace cocos2d

class SceneBase : public cocos2d::Scene
{
public:
    static SceneBase* createScene(int level, LevelScene* levelScene);

    // ������
    virtual ~SceneBase() {};

    virtual bool init(int level, LevelScene* levelScene);

    virtual void initMonster(int choose) {};    //��ʼ�����chooseѡ���ʼ�����ֹ���

    void takeCarrotDamage(int damage);

    void setButton(bool flag);   // ��Ϸ���ʱ���õķ��ð�ť������Ϊtrue��ʤ��Ϊfalseʧ��

    cocos2d::Vec2 getCarrotPosition() const;

    void setCarrotPosition(cocos2d::Vec2 position);

    void initScene(std::string& mapname);   
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    void createBottle(cocos2d::Ref* sender);     //����ƿ������

    void createStar(cocos2d::Ref* sender);       //������������

    void createSunflower(cocos2d::Ref* sender);  //����̫��������

    void onGameWin();

    void onGameFail();

    void update(float delta);

    void addMoney(int money);

    void updateMoney(int money);

    void updateBottle1(cocos2d::Ref* sender);

    /*void updateBottle2(cocos2d::Ref* sender);

    void removeBottle(cocos2d::Ref* sender);

    void updateStar1(cocos2d::Ref* sender);

    void updateStar2(cocos2d::Ref* sender);

    void removeStar(cocos2d::Ref* sender);

    void updateSunflower1(cocos2d::Ref* sender);

    void updateSunflower1(cocos2d::Ref* sender);

    void removeSunflower(cocos2d::Ref* sender);*/

protected:
    cocos2d::Label* m_lable;            //��ʾ��ǰ��Ǯ
    bool monsterFlag = false;           //�����Ƿ�������ϵı�־��trueΪ�������
    float time = 0.0f;                  //��Ϸ�ĳ���ʱ��
    Sprite* m_carrot;                   //ָ���ܲ���ָ��
    int moneyScene;                     //�����еĵ�Ǯ
    int carrotHP = 10;                  //�ܲ��ĳ�ʼѪ��
    cocos2d::Vec2 carrotPosition;       //�ܲ���λ��
    std::vector<cocos2d::Vec2> path;    //�ƶ�·��
    int m_level;                        //���浱ǰ�Ĺؿ����
    LevelScene* m_levelScene;           //����ؿ�ѡ�񳡾���ָ��
};

#endif  //__SCENCEBASE_SCENE_H__

