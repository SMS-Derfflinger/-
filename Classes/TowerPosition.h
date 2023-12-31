#ifndef __YOUR_GAME_SCENE_H__
#define __YOUR_GAME_SCENE_H__

#include "tower.h"
#include "cocos2d.h"

// ����һ������������
class TowerPosition : public cocos2d::Sprite
{
public:
    CREATE_FUNC(TowerPosition);
    // ������
    virtual ~TowerPosition() {};
    // ��ʼ������
    virtual bool init() override;
    Tower* towerofThisPosition;
};

#endif // __YOUR_GAME_SCENE_H__