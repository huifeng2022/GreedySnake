#ifndef SNAKE_H
#define SNAKE_H

#include <deque>
#include "point.h"
#include "food.h"

class Food;
class Snake
{
public:
    enum Direction {UP, DOWN, LEFT, RIGHT};

    Snake() {
        snake.emplace_back(14, 8);
        snake.emplace_back(15, 8);
        snake.emplace_back(16, 8);
        direction = Direction::DOWN;
    }
    void InitSnake();
    void Move(const Food& cfood);//��AI�ߵļ����ƶ���������
    void Move();
    void NormalMove();
    bool OverEdge();
    bool HitItself();
 //   bool HitOthersnake();
    bool ChangeDirection();
    bool GetFood(const Food&);
    bool GetBigFood(Food&);
    bool GetSpecialFood(Food&);
private:
    std::deque<Point> snake;
    Direction direction;
    friend class Food;//��Food����Ϊ��Ԫ���Ա������˽��Ԫ��
};
#endif // SNAKE_H