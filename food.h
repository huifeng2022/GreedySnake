#ifndef FOOD_H
#define FOOD_H

#include "snake.h"
#include "AIsnake.h"
class Snake;
class AIsnake;
class Food
{
public:
    Food() : cnt(0), flash_flag(false), big_flag(false), x(0), y(0), big_x(0), big_y(0),special_x(0),special_y(0), progress_bar(0) {}
    void DrawFood(Snake&);
    void DrawBigFood(Snake&);
    void DrawSpecialFood(Snake&);
    int GetCnt();
    void FlashBigFood();
    bool GetBigFlag();
    int GetProgressBar();
private:
    int cnt;
    int cntt;
    bool flash_flag;//��˸���
    bool big_flag;//�Ƿ�����ʱʳ����
    int x, y;
    int big_x, big_y;
    int special_x, special_y;
    int progress_bar;//��ʱʳ�������
    friend class Snake;
    friend class AIsnake;
};
#endif // FOOD_H
