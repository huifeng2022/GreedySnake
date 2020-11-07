#include "snake.h"
#include <conio.h>
#include "tools.h"
#include <iostream>
#include "food.h"//ʹ��food���ȡfood/big food������
void Snake::InitSnake()//��ʼ����
{
    for (auto& point : snake)
    {
        point.PrintCircular();
    }
}

void Snake::Move(const Food& cfood)//������
{
    int Xstep,Ystep;//�������ƶ��Ĳ���
    int turnNumber = 2;
    //ʳ������
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
        ����ӣ�
        ��ʳ;���ƹ����snake
        */

        /*
        ����ӣ�
        ��ʳ;���ж��Ƿ�������������������������
        */

        //�״�ת��
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

        //����ԭswitch����
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
                �޸���ɫ����+������4+8=12
                ��--1
                ��--2
                ��--4
                ����--8
                */
    snake.back().PrintCircular();
}

void Snake::NormalMove()//�������ƶ���ͷ������β����
{
    Move();
    snake.front().Clear();
    snake.pop_front();
}

bool Snake::OverEdge()//�����߽�
{
    return snake.back().GetX() < 30 &&
        snake.back().GetY() < 30 &&
        snake.back().GetX() > 1 &&
        snake.back().GetY() > 1;
}

bool Snake::HitItself()//ײ������
{
    std::deque<Point>::size_type cnt = 1;
    Point* head = new Point(snake.back().GetX(), snake.back().GetY());//���ͷ������
    for (auto& point : snake) //���������������ͷ����ͬ�����겻�����߳�������ζ����ͷ��ײ������
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

bool Snake::ChangeDirection()//�ı䷽��
{
    char ch;
    if (_kbhit())//kbhit��������ֵΪ��������ע��
    {
        ch = _getch();
        switch (ch)
        {
        case -32:
            ch = _getch();
            switch (ch)
            {
            case 72:
                if (direction != Direction::DOWN)//��������뵱ǰ�˶������෴����Ч
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
