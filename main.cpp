#include "controller.h"
#include "music.h"

int main()//�������
{
	
	mciSendString("open D:\\desktop\\AIGreeend\\music\\background.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	Controller controller;//����һ��Controller��
    controller.Game();//������Ϸѭ��
    return 0;
}
