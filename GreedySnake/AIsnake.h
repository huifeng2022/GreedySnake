#ifndef AISNAKE_H
#define AISNAKE_H

#include <deque>
#include "point.h"
#include "food.h"

class Food;
class AIsnake
{
public:
    enum Direction { UP, DOWN, LEFT, RIGHT };

    AIsnake() {
        msnake.emplace_back(14, 12);
        msnake.emplace_back(15, 12);
        msnake.emplace_back(16, 12);
        mdirection = Direction::DOWN;
    }
    void mInitSnake();
    void mMove(const Food& cfood);
    void mNormalMove(const Food& cfood);
//    bool mOverEdge();
 //   bool mHitItself();
  //  bool mChangeDirection();
    bool mGetFood(const Food&);
    bool mGetBigFood(Food&);
private:
    std::deque<Point> msnake;
    Direction mdirection;
    friend class Food;//��Food����Ϊ��Ԫ���Ա������˽��Ԫ��
};
#endif // SNAKE_H

