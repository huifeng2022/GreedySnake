#include "AIsnake.h"
#include <conio.h>
#include "tools.h"
#include <iostream>
#include "food.h"//使用food类获取food/big food的坐标
#include "controller.h"
int AIsnake::flag_special = 0;
void AIsnake::mInitSnake()//初始化蛇
{
    for (auto& point : msnake)
    {
        point.PrintCircular();
    }
}

int AIsnake::mMove(const Food& cfood)//蛇增长
{
    if (!flag_special) {
        Point* mhead = new Point(msnake.back().GetX(), msnake.back().GetY());
        int target_x, target_y, source_x = mhead->GetX(), source_y = mhead->GetY();
        if (cfood.big_flag) {
            target_x = cfood.big_x, target_y = cfood.big_y;
        }
        else {
            target_x = cfood.x, target_y = cfood.y;
        }
        int Xlength = target_x - source_x, Ylength = target_y - source_y;

        //首次转向
        if (Xlength > 0 && abs(Xlength) >= abs(Ylength)) {
            mdirection = RIGHT;
        }
        else if (Xlength < 0 && abs(Xlength) >= abs(Ylength)) {
            mdirection = LEFT;
        }
        else if (Ylength > 0 && abs(Xlength) < abs(Ylength)) {
            mdirection = DOWN;
        }
        else if (Ylength < 0 && abs(Xlength) < abs(Ylength)) {
            mdirection = UP;
        }
        //保持原switch不变
        switch (mdirection)
        {
        case Direction::UP:
            msnake.emplace_back(Point(msnake.back().GetX(), msnake.back().GetY() - 1));
            break;
        case Direction::DOWN:
            msnake.emplace_back(Point(msnake.back().GetX(), msnake.back().GetY() + 1));
            break;
        case Direction::LEFT:
            msnake.emplace_back(Point(msnake.back().GetX() - 1, msnake.back().GetY()));
            break;
        case Direction::RIGHT:
            msnake.emplace_back(Point(msnake.back().GetX() + 1, msnake.back().GetY()));
            break;
        default:
            break;
        }
    }
    else {
        switch (flag_special)
        {
        case 1:case 5: case 9: case 13:case 17:case 21: case 25: case 29://up
            msnake.emplace_back(Point(msnake.back().GetX(), msnake.back().GetY() - 1));
            flag_special--;
            break;
        case 3:case 7: case 11: case 15:case 19:case 23: case 27: case 31://down
            msnake.emplace_back(Point(msnake.back().GetX(), msnake.back().GetY() + 1));
            flag_special--;
            break;
        case 2:case 6: case 10: case 14:case 18:case 22: case 26: case 30://left
            msnake.emplace_back(Point(msnake.back().GetX() - 1, msnake.back().GetY()));
            flag_special--;
            break;
        case 4:case 8: case 12: case 16:case 20:case 24: case 28: case 32://right
            msnake.emplace_back(Point(msnake.back().GetX() + 1, msnake.back().GetY()));
            flag_special--;
            break;
        default:
            break;
        }

    }
        SetColor(4);
        msnake.back().PrintCircular();
        return flag_special;
 }
/*
                修改颜色：红+高亮：4+8=12
                蓝--1
                绿--2
                红--4
                高亮--8
*/
 //   SetColor(1);


void AIsnake::mNormalMove(const Food& cfood)//蛇正常移动，头增长，尾缩短
{
    mMove(cfood);
    msnake.front().Clear();
    msnake.pop_front();
}

/*bool Snake::mOverEdge()//超出边界
{
    return msnake.back().GetX() < 30 &&
        msnake.back().GetY() < 30 &&
        msnake.back().GetX() > 1 &&
        msnake.back().GetY() > 1;
}

bool Snake::mHitItself()//撞到自身
{
    std::deque<Point>::size_type cnt = 1;
    Point* mhead = new Point(msnake.back().GetX(), msnake.back().GetY());//获得头部坐标
    for (auto& point : msnake) //如果整条蛇中与蛇头不相同的坐标不等于蛇长，则意味着蛇头碰撞到自身
    {
        if (!(point == *head))
            ++cnt;
        else
            break;
    }
    delete head;
    if (cnt == msnake.size())
        return true;
    else
        return false;
}

bool Snake::mChangeDirection()//改变方向
{
    char ch;
    if (_kbhit())//kbhit函数返回值为两个，需注意
    {
        ch = _getch();
        switch (ch)
        {
        case -32:
            ch = _getch();
            switch (ch)
            {
            case 72:
                if (mdirection != Direction::DOWN)//如果方向与当前运动方向相反，无效
                    mdirection = Direction::UP;
                break;
            case 80:
                if (mdirection != Direction::UP)
                    mdirection = Direction::DOWN;
                break;
            case 75:
                if (mdirection != Direction::RIGHT)
                    mdirection = Direction::LEFT;
                break;
            case 77:
                if (mdirection != Direction::LEFT)
                    mdirection = Direction::RIGHT;
                break;
            default:
                break;
            }
            return true;

        case 27://ESC
            return false;

        default:
            return true;

        }
    }
    return true;
}
*/
bool AIsnake::mGetFood(const Food& cfood)
{
    if (msnake.back().GetX() == cfood.x && msnake.back().GetY() == cfood.y)
        return true;
    else
        return false;
}

bool AIsnake::mGetBigFood(Food& cfood)
{
    if (msnake.back().GetX() == cfood.big_x && msnake.back().GetY() == cfood.big_y)
    {
        cfood.big_flag = false;
        cfood.big_x = 0;
        cfood.big_y = 0;
        SetCursorPosition(1, 0);
        std::cout << "                                                            ";
        return true;
    }
    else
        return false;
}

int AIsnake::special(int a )
{
    return flag_special=a;
}



