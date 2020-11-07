#include "snake.h"
#include <conio.h>
#include "tools.h"
#include <iostream>
#include "food.h"//使用food类获取food/big food的坐标
void Snake::InitSnake()//初始化蛇
{
    for (auto& point : snake)
    {
        point.PrintCircular();
    }
}

void Snake::Move(const Food& cfood)//蛇增长
{
    int Xstep,Ystep;//方向上移动的步长
    int turnNumber = 2;
    //食物坐标
    Point* head = new Point(snake.back().GetX(), snake.back().GetY());
    while (turnNumber) {
        int target_x, target_y, source_x = head->GetX(), source_y = head->GetY();
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
            direction = RIGHT;
            Xstep = Xlength;
        }
        else if (Xlength < 0 && abs(Xlength) >= abs(Ylength)) {
            direction = LEFT;
            Xstep = Xlength;
        }
        else if (Ylength > 0 && abs(Xlength) < abs(Ylength)) {
            direction = UP;
            Ystep = Ylength;
        }
        else {
            direction = DOWN;
            Ystep = Ylength;
        }

        //保持原switch不变
        switch (direction)
        {
        case Direction::UP:
            while (turnNumber)
                snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() - 1));
            break;
        case Direction::DOWN:
            snake.emplace_back(Point(snake.back().GetX(), snake.back().GetY() + 1));
            break;
        case Direction::LEFT:
            snake.emplace_back(Point(snake.back().GetX() - 1, snake.back().GetY()));
            break;
        case Direction::RIGHT:
            snake.emplace_back(Point(snake.back().GetX() + 1, snake.back().GetY()));
            break;
        default:
            break;
        }
        turnNumber--;
    }
    SetColor(12);/*
                修改颜色：红+高亮：4+8=12
                蓝--1
                绿--2
                红--4
                高亮--8
                */
    snake.back().PrintCircular();
}

void Snake::NormalMove()//蛇正常移动，头增长，尾缩短
{
    Move();
    snake.front().Clear();
    snake.pop_front();
}

bool Snake::OverEdge()//超出边界
{
    return snake.back().GetX() < 30 &&
        snake.back().GetY() < 30 &&
        snake.back().GetX() > 1 &&
        snake.back().GetY() > 1;
}

bool Snake::HitItself()//撞到自身
{
    std::deque<Point>::size_type cnt = 1;
    Point* head = new Point(snake.back().GetX(), snake.back().GetY());//获得头部坐标
    for (auto& point : snake) //如果整条蛇中与蛇头不相同的坐标不等于蛇长，则意味着蛇头碰撞到自身
    {
        if (!(point == *head))
            ++cnt;
        else
            break;
    }
    delete head;
    if (cnt == snake.size())
        return true;
    else
        return false;
}

bool Snake::ChangeDirection()//改变方向
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
                if (direction != Direction::DOWN)//如果方向与当前运动方向相反，无效
                    direction = Direction::UP;
                break;
            case 80:
                if (direction != Direction::UP)
                    direction = Direction::DOWN;
                break;
            case 75:
                if (direction != Direction::RIGHT)
                    direction = Direction::LEFT;
                break;
            case 77:
                if (direction != Direction::LEFT)
                    direction = Direction::RIGHT;
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

bool Snake::GetFood(const Food& cfood)
{
    if (snake.back().GetX() == cfood.x && snake.back().GetY() == cfood.y)
        return true;
    else
        return false;
}

bool Snake::GetBigFood(Food& cfood)
{
    if (snake.back().GetX() == cfood.big_x && snake.back().GetY() == cfood.big_y)
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
