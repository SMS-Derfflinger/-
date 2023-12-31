#include "Tower.h"
USING_NS_CC;

bool BottleTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 200;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 100;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool BottleTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 150;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool BottleTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("BottleLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "BottleBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 300;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 250;
    rotateSpeed = 180;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool SunflowerTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 10;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool SunflowerTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool SunflowerTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("SunflowerLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "SunflowerBullet.png";
    // ��ըЧ��
    Explosion = "BottleBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool StarTower_1::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel1.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel1.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 200;
    damage = 15;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool StarTower_2::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel2.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel2.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 250;
    damage = 20;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}

bool StarTower_3::init() {
    if (!Sprite::init()) {
        return false;
    }

    //������ͼƬ
    this->initWithFile("StarLevel3.png");
    // �ӵ���ͼƬ
    Bullet = "StarBulletLevel3.png";
    // ��ըЧ��
    Explosion = "StarBoom.png";
    // ������̡��������͹������
    range = 300;
    damage = 25;
    attackInterval = 1.0f;

    consumption = 200;
    bulletRange = 500;
    cooldownTimer = 0.0f;
    attackDuration = 0.0f;
    target = nullptr;
    // ������ʱ������ʱ��������״̬
    scheduleUpdate();

    return true;
}