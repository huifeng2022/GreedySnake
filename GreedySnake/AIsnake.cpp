#include "AIsnake.h"
#include <conio.h>
#include "tools.h"
#include <iostream>
#include "food.h"//ʹ��food���ȡfood/big food������
void AIsnake::mInitSnake()//��ʼ����
{
    for (auto& point : msnake)
    {
        point.PrintCircular();
    }
}

void AIsnake::mMove(const Food& cfood)//������
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
        ����ӣ�
        ��ʳ;���ƹ����snake
        */

        /*
        ����ӣ�
        ��ʳ;���ж��Ƿ�������������������������
        */

        //�״�ת��
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

        //����ԭswitch����
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
                �޸���ɫ����+������4+8=12
                ��--1
                ��--2
                ��--4
                ����--8
*/
 //   SetColor(1);


void AIsnake::mNormalMove(const Food& cfood)//�������ƶ���ͷ������β����
{
    mMove(cfood);
    msnake.front().Clear();
    msnake.pop_front();
}

/*bool Snake::mOverEdge()//�����߽�
{
    return msnake.back().GetX() < 30 &&
        msnake.back().GetY() < 30 &&
        msnake.back().GetX() > 1 &&
        msnake.back().GetY() > 1;
}

bool Snake::mHitItself()//ײ������
{
    std::deque<Point>::size_type cnt = 1;
    Point* mhead = new Point(msnake.back().GetX(), msnake.back().GetY());//���ͷ������
    for (auto& point : msnake) //���������������ͷ����ͬ�����겻�����߳�������ζ����ͷ��ײ������
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

bool Snake::mChangeDirection()//�ı䷽��
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
                if (mdirection != Direction::DOWN)//��������뵱ǰ�˶������෴����Ч
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
