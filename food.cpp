#include "food.h"
#include "tools.h"
#include <cstdlib>
#include <iostream>


void Food::DrawFood(Snake& csnake)//����ʳ��
{
    /*����rand����������꣬�����䷶Χ������2-29�ڣ����ڵ�ͼ�ڣ������õ������������ص��������»�ȡ��
      ͬʱÿ5��ʳ��ͳ���һ����ʱʳ��*/
    while (true)
    {
        int tmp_x = rand() % 30;
        int tmp_y = rand() % 30;
		if (tmp_x < 3) tmp_x += 4;
		if (tmp_x > 27) tmp_x -= 3;
		if (tmp_y < 3) tmp_y += 4;
		if (tmp_y > 27) tmp_y -= 3;
        bool flag = false;
        for (auto& point : csnake.snake)
        {
            if  ((point.GetX() == tmp_x && point.GetY() == tmp_y) || (tmp_x == big_x && tmp_y == big_y) || (tmp_x == special_x && tmp_y == special_y)){
                flag = true;
                break;
            }
        }
        if (flag)
            continue;
        x = tmp_x;
        y = tmp_y;
        SetCursorPosition(x, y);
        SetColor(13);
        std::cout << "��" ;
        ++cnt;
        cnt %= 5;
        if (cnt == 0)
        {
            DrawBigFood(csnake);
        }
        break;
    }
}

void Food::DrawBigFood(Snake& csnake)//������ʱʳ��
{
    SetCursorPosition(5, 0);
    SetColor(11);
    std::cout << "------------------------------------------" ;//������
    progress_bar = 42;
    while (true)
    {
        int tmp_x = rand() % 30;
        int tmp_y = rand() % 30;
        if(tmp_x < 3) tmp_x += 4;
		if (tmp_x > 27) tmp_x -= 3;
        if(tmp_y < 3) tmp_y += 4; 
		if (tmp_y > 27) tmp_y -= 3;
        bool flag = false;
        for (auto& point : csnake.snake)
        {
            if ((point.GetX() == tmp_x && point.GetY() == tmp_y) || (tmp_x == x && tmp_y == y) || (tmp_x == special_x && tmp_y == special_y))
            {
                flag = true;
                break;
            }
        }
        if (flag)
            continue;

        big_x = tmp_x;
        big_y = tmp_y;
        SetCursorPosition(big_x, big_y);
        SetColor(11);
        std::cout << "��" ;
        big_flag = true;
        flash_flag = true;
        ++cntt;
		if ((cntt %= 2) == 0)
		{
			DrawSpecialFood(csnake);
		}
        break;
    }
}

int Food::GetCnt()
{
    return cnt;
}

void Food::FlashBigFood()//��˸��ʱʳ��
{
    SetCursorPosition(big_x, big_y);
    SetColor(11);
    if (flash_flag)
    {
        std::cout << "  " ;
        flash_flag = false;
    }
    else
    {
        std::cout << "��" ;
        flash_flag = true;
    }

    SetCursorPosition(26, 0);
    SetColor(11);
    for (int i = 42; i >= progress_bar; --i)//����������
        std::cout << "\b \b" ;
    --progress_bar;
    if (progress_bar == 0) {
        SetCursorPosition(big_x, big_y);
        std::cout << "  " ;
        big_flag = false;
        big_x = 0;
        big_y = 0;
    }
}

bool Food::GetBigFlag()
{
    return big_flag;
}

int Food::GetProgressBar()
{
    return progress_bar;
}

void Food::DrawSpecialFood(Snake& csnake)//��������ʳ��
{
	while (true)
	{
		int tmp_x = rand() % 30;
		int tmp_y = rand() % 30;
		if (tmp_x < 2) tmp_x += 2;
		if (tmp_y < 2) tmp_y += 2;
		bool flag = false;
		for (auto& point : csnake.snake)
		{
			if ((point.GetX() == tmp_x && point.GetY() == tmp_y) || (tmp_x == big_x && tmp_y == big_y) || (tmp_x == x && tmp_y == y)) {
				flag = true;
				break;
			}
		}
		if (flag)
			continue;
		special_x = tmp_x;
		special_y = tmp_y;
		SetCursorPosition(special_x, special_y);
		SetColor(30);
		std::cout << "��";
		break;
	}
}
