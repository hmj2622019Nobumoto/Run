#include "DxLib.h"

const int WIDTH = 960, HEIGHT = 640;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
{

	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	//while (1)
	//{
	//	ClearDrawScreen();





	//	ScreenFlip();
	//	WaitTimer(16);
	//	if (ProcessMessage() == -1) break;
	//	if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	//}

	DxLib_End();
	return 0;
}