#include <iostream>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "controller.h"
#include "tools.h"
#include "startinterface.h"
#include "map.h"
#include "snake.h"
#include "AIsnake.h"
#include "food.h"
#include "music.h"

void Controller::Start()//��ʼ����
{
    SetWindowSize(41, 32);//���ô��ڴ�С
    SetColor(2);//���ÿ�ʼ������ɫ

    StartInterface *start = new StartInterface();//��̬����һ��StartInterface��start
    start->Action();//��ʼ����
    delete start;//�ͷ��ڴ�ռ�

    /*���ùر�λ�ã��������ʾ��ȴ�������������*/
    SetCursorPosition(13, 26);
    std::cout << "Press any key to start... " ;
    SetCursorPosition(13, 27);
    system("pause");
}

void Controller::Select()//ѡ�����
{
    /*��ʼ������ѡ��*/
    SetColor(3);
    SetCursorPosition(13, 26);
    std::cout << "                          " ;
    SetCursorPosition(13, 27);
    std::cout << "                          " ;
    SetCursorPosition(6, 21);
    std::cout << "��ѡ����Ϸ�Ѷȣ�" ;
    SetCursorPosition(6, 22);
    std::cout << "(���¼�ѡ��,�س�ȷ��)" ;
    SetCursorPosition(27, 22);
    SetBackColor();//��һ��ѡ�����ñ���ɫ�Ա�ʾ��ǰѡ��
    std::cout << "��ģʽ" ;
    SetCursorPosition(27, 24);
    SetColor(3);
    std::cout << "��ͨģʽ" ;
    SetCursorPosition(27, 26);
    std::cout << "����ģʽ" ;
    SetCursorPosition(27, 28);
    std::cout << "����ģʽ" ;
    SetCursorPosition(0, 31);
    score = 0;
	aiscore = 0;

    /*���·����ѡ��ģ��*/
    int ch;//��¼����ֵ
    key = 1;//��¼ѡ�����ʼѡ���һ��
    bool flag = false;//��¼�Ƿ����Enter����ǣ���ʼ��Ϊ��
    while ((ch = _getch()))
    {
        switch (ch)//��������
        {
        case 72://UP�Ϸ����
            if (key > 1)//����ʱѡ����Ϊ��һ��ʱ��UP�Ϸ������Ч
            {
                switch (key)
                {
                case 2:
                    SetCursorPosition(27, 22);//����ѡ�������ñ���ɫ
                    SetBackColor();
                    std::cout << "��ģʽ" ;

                    SetCursorPosition(27, 24);//����ѡ����ȡ���ұ���ɫ
                    SetColor(3);
                    std::cout << "��ͨģʽ" ;

                    --key;
                    break;
                case 3:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "��ͨģʽ" ;

                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    --key;
                    break;
                case 4:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "����ģʽ" ;

                    SetCursorPosition(27, 28);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    --key;
                    break;
                }
            }
            break;

        case 80://DOWN�·����
            if (key < 4)
            {
                switch (key)
                {
                case 1:
                    SetCursorPosition(27, 24);
                    SetBackColor();
                    std::cout << "��ͨģʽ" ;
                    SetCursorPosition(27, 22);
                    SetColor(3);
                    std::cout << "��ģʽ" ;

                    ++key;
                    break;
                case 2:
                    SetCursorPosition(27, 26);
                    SetBackColor();
                    std::cout << "����ģʽ" ;
                    SetCursorPosition(27, 24);
                    SetColor(3);
                    std::cout << "��ͨģʽ" ;

                    ++key;
                    break;
                case 3:
                    SetCursorPosition(27, 28);
                    SetBackColor();
                    std::cout << "����ģʽ" ;
                    SetCursorPosition(27, 26);
                    SetColor(3);
                    std::cout << "����ģʽ" ;

                    ++key;
                    break;
                }
            }
            break;

        case 13://Enter�س���
            flag = true;
            break;
        default://��Ч����
            break;
        }
        if (flag) break;//����Enter�س���ȷ�ϣ��˳��������ѭ��

        SetCursorPosition(0, 31);//������������½ǣ�����ر���˸Ӱ����Ϸ����
    }

    switch (key)//������ѡѡ�������ߵ��ƶ��ٶȣ�speedֵԽС���ٶ�Խ��
    {
    case 1:
        speed = 180;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
        break;
    case 2:
        speed = 120;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
        break;
    case 3:
        speed = 60;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
        break;
    case 4:
        speed = 30;
		PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_ASYNC);
        break;
    default:
        break;
    }
}

void Controller::DrawGame()//������Ϸ����
{
    system("cls");//����

    /*���Ƶ�ͼ*/
    SetColor(3);
    Map *init_map = new Map();
    init_map->PrintInitmap();
    delete init_map;

    /*���Ʋ����*/
    SetColor(3);
    SetCursorPosition(33, 1);
    std::cout << "Greedy Snake" ;
    SetCursorPosition(34, 2);
    std::cout << "̰����" ;
    SetCursorPosition(31, 4);
    std::cout << "�Ѷȣ�" ;
    SetCursorPosition(36, 5);
    switch (key)
    {
    case 1:
        std::cout << "��ģʽ" ;
        break;
    case 2:
        std::cout << "��ͨģʽ" ;
        break;
    case 3:
        std::cout << "����ģʽ" ;
        break;
    case 4:
        std::cout << "����ģʽ" ;
        break;
    default:
        break;
    }
    SetCursorPosition(31, 7); /*�Ʒְ�*/
    std::cout << "��ҵ÷֣�" ;
    SetCursorPosition(37, 8);
    std::cout << "     0" ;
	SetCursorPosition(31, 9); /*�Ʒְ�*/
	std::cout << "�˻��ߵ÷֣�";
	SetCursorPosition(37, 10);
	std::cout << "     0";

    SetCursorPosition(33, 13);
    std::cout << " ������ƶ�" ;
    SetCursorPosition(33, 15);
    std::cout << " ESC����ͣ" ;
}
/*��������*/
void print_smileface() {
	SetCursorPosition(32, 17);
	std::cout << " *        * ";
	SetCursorPosition(32, 18);
	std::cout << "  ********  ";
	SetCursorPosition(32, 19);
	std::cout << "*          *";
	SetCursorPosition(32, 20);
	std::cout << "*  ^    ^  *";
	SetCursorPosition(32, 21);
	std::cout << "*          *";
	SetCursorPosition(32, 22);
	std::cout << "*    ��    *";
	SetCursorPosition(32, 23);
	std::cout << "  ********  ";
	SetCursorPosition(32, 24);
	std::cout << "Good!";
}

void print_face() {
	SetCursorPosition(32, 17);
	std::cout << " *        * ";
	SetCursorPosition(32, 18);
	std::cout << "  ********  ";
	SetCursorPosition(32, 19);
	std::cout << "*          *";
	SetCursorPosition(32, 20);
	std::cout << "*  *    *  *";
	SetCursorPosition(32, 21);
	std::cout << "*          *";
	SetCursorPosition(32, 22);
	std::cout << "*    *     *";
	SetCursorPosition(32, 23);
	std::cout << "  ********  ";
	SetCursorPosition(32, 24);
	std::cout << "Cautious!";
}

int Controller::PlayGame()//��Ϸ����ѭ��
{
    /*��ʼ���ߺ�ʳ��*/
    Snake *csnake = new Snake();
    AIsnake *msnake = new AIsnake();
    Food *cfood = new Food();
    SetColor(6);
    csnake->InitSnake();
    msnake->mInitSnake();
    srand((unsigned)time(NULL));//������������ӣ����û�� ʳ��ĳ���λ�ý���̶�
    cfood->DrawFood(*csnake);

    /*��Ϸѭ��*/
    while (csnake->OverEdge() && csnake->HitItself()) //�ж��Ƿ�ײǽ��ײ�����������Ƿ�������
    {
        /*����ѡ��˵�*/
        if (!csnake->ChangeDirection()) //��Esc��ʱ
        {
            int tmp = Menu();//���Ʋ˵������õ�����ֵ
            switch (tmp)
            {
            case 1://������Ϸ
                break;

            case 2://���¿�ʼ
                delete csnake;
                delete msnake;
                delete cfood;
                return 1;//��1��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ���¿�ʼ

            case 3://�˳���Ϸ
                delete csnake;
                delete msnake;
                delete cfood;
                return 2;//��2��ΪPlayGame�����ķ���ֵ���ص�Game�����У���ʾ�˳���Ϸ

            default:
                break;
            }
        }

        if (csnake->GetFood(*cfood)) //�Ե�ʳ��
        {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE5), NULL, SND_RESOURCE | SND_ASYNC);
			csnake->Move();//������
			print_smileface();//Ц��
            UpdateScore(1);//���·�����1Ϊ����Ȩ��
            RewriteScore();//���»��Ʒ���
            cfood->DrawFood(*csnake);//������ʳ��
        }
        else
        {
            csnake->NormalMove();//�������ƶ�
			print_face();
        }
        //msnake
        
        if (msnake->mGetFood(*cfood))
        {
            msnake->mMove(*cfood);
            UpdateaiScore(1);//���·�����1Ϊ����Ȩ��
            RewriteaiScore();//���»��Ʒ���
            cfood->DrawFood(*csnake);//������ʳ��
        }
        else
        {
            msnake->mNormalMove(*cfood);//�������ƶ�
        }

		if (csnake->GetSpecialFood(*cfood)) //�Ե�����ʳ��
		{
            PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
			csnake->Move();//������
			UpdateScore(2);//���·�����2Ϊ����Ȩ��
			RewriteScore();//���»��Ʒ���
//			cfood->DrawFood(*csnake);
//			cfood->DrawFood(*csnake);//����������ʳ��
            msnake->special(32);
		}

        if (csnake->GetBigFood(*cfood)) //�Ե���ʱʳ��
        {
			PlaySound(MAKEINTRESOURCE(IDR_WAVE4), NULL, SND_RESOURCE | SND_ASYNC);
			csnake->Move();
			print_smileface();//Ц��
            UpdateScore(cfood->GetProgressBar()/5);//����������ʱʳ�������ȷ��
            RewriteScore();
        }
        //msnake
        if (msnake->mGetBigFood(*cfood)) //�Ե���ʱʳ��
        {
            msnake->mMove(*cfood);
            UpdateaiScore(cfood->GetProgressBar() / 5);//����������ʱʳ�������ȷ��
            RewriteaiScore();
        }

        if (cfood->GetBigFlag()) //�����ʱ����ʱʳ���˸��
        {
            cfood->FlashBigFood();
        }

        Sleep(speed);//�����ߵ��ƶ�Ч��
    }

    /*������*/
    delete csnake;//�ͷŷ�����ڴ�ռ�
    delete msnake;
    delete cfood;
    int tmp = GameOver();//������Ϸ�������棬��������ѡ��
    switch (tmp)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 2;
    }
}

void Controller::UpdateScore(const int& tmp)//���·���
{
    score += key * 10 * tmp;//���÷���������Ϸ�Ѷȼ����˵Ĳ���tmpȷ��
}
void Controller::UpdateaiScore(const int& tmp)//����AI�߷���
{
	aiscore += key * 10 * tmp;//���÷���������Ϸ�Ѷȼ����˵Ĳ���tmpȷ��
}
void Controller::RewriteScore()//�ػ����
{
    /*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
    SetCursorPosition(37, 8);
    SetColor(11);
    int bit = 0;
    int tmp = score;
    while (tmp != 0)
    {
        ++bit;
        tmp /= 10;
    }
    for (int i = 0; i < (6 - bit); ++i)
    {
        std::cout << " " ;
    }
    std::cout << score ;
}
void Controller::RewriteaiScore()//�ػ�AI�߷���
{
	/*Ϊ���ַ���β�����룬������������Ϊ6λ�����㵱ǰ����λ������ʣ��λ���ÿո�ȫ�����������*/
	SetCursorPosition(37, 10);
	SetColor(11);
	int bit = 0;
	int tmp = aiscore;
	while (tmp != 0)
	{
		++bit;
		tmp /= 10;
	}
	for (int i = 0; i < (6 - bit); ++i)
	{
		std::cout << " ";
	}
	std::cout << aiscore;
}

int Controller::Menu()//ѡ��˵�
{
    /*���Ʋ˵�*/
    SetColor(11);
    SetCursorPosition(32, 19);
    std::cout << "�˵���" ;
    Sleep(100);
    SetCursorPosition(34, 21);
    SetBackColor();
    std::cout << "������Ϸ" ;
    Sleep(100);
    SetCursorPosition(34, 23);
    SetColor(11);
    std::cout << "���¿�ʼ" ;
    Sleep(100);
    SetCursorPosition(34, 25);
    std::cout << "�˳���Ϸ" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 72://UP
            if (tmp_key > 1)
            {
                switch (tmp_key)
                {
                case 2:
                    SetCursorPosition(34, 21);
                    SetBackColor();
                    std::cout << "������Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

                    --tmp_key;
                    break;
                case 3:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 25);
                    SetColor(11);
                    std::cout << "�˳���Ϸ" ;

                    --tmp_key;
                    break;
                }
            }
            break;

        case 80://DOWN
            if (tmp_key < 3)
            {
                switch (tmp_key)
                {
                case 1:
                    SetCursorPosition(34, 23);
                    SetBackColor();
                    std::cout << "���¿�ʼ" ;
                    SetCursorPosition(34, 21);
                    SetColor(11);
                    std::cout << "������Ϸ" ;

                    ++tmp_key;
                    break;
                case 2:
                    SetCursorPosition(34, 25);
                    SetBackColor();
                    std::cout << "�˳���Ϸ" ;
                    SetCursorPosition(34, 23);
                    SetColor(11);
                    std::cout << "���¿�ʼ" ;

                    ++tmp_key;
                    break;
                }
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        if (flag)
        {
            break;
        }
        SetCursorPosition(0, 31);
    }

    if (tmp_key == 1) //ѡ�������Ϸ���򽫲˵�����
    {
        SetCursorPosition(32, 19);
        std::cout << "      " ;
        SetCursorPosition(34, 21);
        std::cout << "        ";
        SetCursorPosition(34, 23);
        std::cout << "        ";
        SetCursorPosition(34, 25);
        std::cout << "        ";
    }
    return tmp_key;
}

void Controller::Game()//��Ϸһ��ѭ��
{
    Start();//��ʼ����

    while (true)//��Ϸ����Ϊһ����ѭ����ֱ���˳���Ϸʱѭ������
    {
        Select();//ѡ�����
        DrawGame();//������Ϸ����

        int tmp = PlayGame();//������Ϸѭ���������¿�ʼ���˳���Ϸʱ������ѭ��������ֵ��tmp
        if (tmp == 1) //����ֵΪ1ʱ���¿�ʼ��Ϸ
        {
            system("cls");
            continue;
        }
        else if (tmp == 2) //����ֵΪ2ʱ�˳���Ϸ
        {
            break;
        }
        else
        {
            break;
        }
    }
}

int Controller::GameOver()//��Ϸ��������
{
    /*������Ϸ��������*/
    Sleep(500);
	PlaySound(MAKEINTRESOURCE(IDR_WAVE3), NULL, SND_RESOURCE | SND_ASYNC);
    SetColor(11);
    SetCursorPosition(8, 8);
    std::cout << "��������������������������������������������" ;
    Sleep(30);
    SetCursorPosition(7, 9);
    std::cout << " ��               Game Over !!!              ��" ;
    Sleep(30);
    SetCursorPosition(7, 10);
    std::cout << " ��                                          ��" ;
    Sleep(30);

	if (score <= 10)
	{
		SetCursorPosition(7, 11);
		std::cout << " ��       ����ɲ���� �����⣿��            ��";
		Sleep(30);
	}

	else if (score > 10 && score < 60)
	{
		SetCursorPosition(7, 11);
		std::cout << " ��       just so so                         ��";
		Sleep(30);
	}
	else {
		SetCursorPosition(7, 11);
		std::cout << " ��       ����Ī�Ǵ�˵�е�����!              ��";
		Sleep(30);
	}

   
    SetCursorPosition(7, 12);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(7, 13);
    std::cout << " ��             ��ķ���Ϊ��                 ��" ;
    SetCursorPosition(22, 13);
    std::cout << score ;
    Sleep(30);

	SetCursorPosition(7, 14);
	std::cout << " ��             �˻�����Ϊ��                 ��";
	SetCursorPosition(22, 14);
	std::cout << aiscore;
	Sleep(30);

	SetCursorPosition(7, 15);
	std::cout << " ��                                          ��";
	Sleep(30);

	if (score < aiscore) {
		SetCursorPosition(7, 16);
		std::cout << " ��             ���Ǵ򲻹��ұƵ�             ��";
		Sleep(30);
		
	}
	else {
		SetCursorPosition(7, 16);
		std::cout << " ��        ����Ϊ���棡                      ��";
		Sleep(30);
		
	}
	SetCursorPosition(7, 17);
	std::cout << " ��                                          ��";
	Sleep(30);
	SetCursorPosition(7, 18);
	std::cout << " ��             �Ƿ�����һ�֣�               ��";
	Sleep(30);
    SetCursorPosition(7, 19);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(7, 20);
    std::cout << " ��    �ţ��õ�        ���ˣ�����ѧϰ����˼  ��" ;
    Sleep(30);
    SetCursorPosition(7, 21);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(7, 22);
    std::cout << " ��                                          ��" ;
    Sleep(30);
    SetCursorPosition(8, 23);
    std::cout << "��������������������������������������������" ;

    Sleep(100);
    SetCursorPosition(10, 20);
    SetBackColor();
    std::cout << "�ţ��õ�" ;
    SetCursorPosition(0, 31);

    /*ѡ�񲿷�*/
    int ch;
    int tmp_key = 1;
    bool flag = false;
    while ((ch = _getch()))
    {
        switch (ch)
        {
        case 75://LEFT
            if (tmp_key > 1)
            {
                SetCursorPosition(10, 20);
                SetBackColor();
                std::cout << "�ţ��õ�" ;
                SetCursorPosition(18, 20);
                SetColor(11);
                std::cout << "���ˣ�����ѧϰ����˼" ;
                --tmp_key;
            }
            break;

        case 77://RIGHT
            if (tmp_key < 2)
            {
                SetCursorPosition(18, 20);
                SetBackColor();
                std::cout << "���ˣ�����ѧϰ����˼" ;
                SetCursorPosition(10, 20);
                SetColor(11);
                std::cout << "�ţ��õ�" ;
                ++tmp_key;
            }
            break;

        case 13://Enter
            flag = true;
            break;

        default:
            break;
        }

        SetCursorPosition(0, 31);
        if (flag) {
            break;
        }
    }

    SetColor(11);
    switch (tmp_key)
    {
    case 1:
        return 1;//���¿�ʼ
    case 2:
        return 2;//�˳���Ϸ
    default:
        return 1;
    }
}