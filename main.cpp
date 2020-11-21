#include "controller.h"
#include "music.h"

int main()//程序入口
{
	
	mciSendString("open D:\\desktop\\AIGreeend\\music\\background.mp3 alias bkmusic", NULL, 0, NULL);
	mciSendString("play bkmusic repeat", NULL, 0, NULL);
	Controller controller;//声明一个Controller类
    controller.Game();//整个游戏循环
    return 0;
}
