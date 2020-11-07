#include "AIsnake.h"
#include <conio.h>
#include "tools.h"
#include <iostream>
#include "food.h"//使用food类获取food/big food的坐标
void AIsnake::mInitSnake()//初始化蛇
{
    for (auto& point : msnake)
    {
        point.PrintCircular();
    }
}

void AIsnake::mMove(const Food& cfood)//蛇增长
{
    Point* mhead = new Point(msnake.back().GetX(), msnake.back().GetY());
        int target_x, target_y, source_x = mhead->GetX(), source_y = mhead->GetY();
        if (cfood.big_flag) {
            target_x = cfood.big_x, target_y = cfood.big_y;
        }
        else {
            target_x = cfood.x, target_y = cfood.y;
        }
        int Xlength = target_x - source_x, Ylength = target_y - source_y;
        /*
        待添加：
        觅食途中绕过玩家snake
        */

        /*
        待添加：
        觅食途中判断是否能完成阻拦，并尽量完成阻拦
        */

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
        SetColor(1);
        msnake.back().PrintCircular();
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
