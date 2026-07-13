#include "DxLib.h"
#define ENEMY_MAX 20
const int WIDTH = 1280, HEIGHT = 720;

float playerX;
float playerY;


float enemyX[ENEMY_MAX];
float enemyY[ENEMY_MAX];
float enemySpeed[ENEMY_MAX];
float enemyDirection[ENEMY_MAX];
int enemyActive[ENEMY_MAX];


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdline, int nCmdShow)
{
	float cx;
	float cy;

	int i;
	int score = 0;
	int spawnTimer = 0;
	int mouseInput = 0;
	int oldMouseInput = 0;

	SRand (GetNowCount());
	SetWindowText("ëñÇÈãÖÇåÇÇøî≤Ç≠ÉQÅ[ÉÄÅiâºÅj");
	SetGraphMode(WIDTH, HEIGHT, 32);
	ChangeWindowMode(true);
	if (DxLib_Init() == -1) return -1;
	SetDrawScreen(DX_SCREEN_BACK);
	SetMouseDispFlag(false);
	SetBackgroundColor(255, 255, 255);

	cx = WIDTH / 2;
	cy = HEIGHT / 2;

	for (i = 0; i < ENEMY_MAX; i++) enemyActive[i] = 0;

	while (1)
	{
		ClearDrawScreen();

		oldMouseInput = mouseInput;
		mouseInput = GetMouseInput();

		SetMousePoint(WIDTH / 2, HEIGHT / 2);

		spawnTimer++;
		if (spawnTimer >= 40)
		{
			spawnTimer = 0;

			for (i = 0; i < ENEMY_MAX; i++)
			{
				if (enemyActive[i] == 0)
				{
					int side = GetRand(1);

					if (side == 0)
					{
						enemyX[i] = 10;
						enemyDirection[i] = -1;
					}
					else
					{
						enemyX[i] = WIDTH - 10;
						enemyDirection[i] = 1;
					}

					enemyY[i] = cy;
					enemySpeed[i] = 4.0f + GetRand(5);
					enemyActive[i] = 1;
					break;
				}
			}
		}

		for (i = 0; i < ENEMY_MAX; i++)
		{
			if (enemyActive[i] == 1)
			{
				if (enemyDirection[i] == -1)
				{
					enemyX[i] += enemySpeed[i];
					if (enemyX[i] > WIDTH) enemyActive[i] = 0;
				}
				else
				{
					enemyX[i] -= enemySpeed[i];
					if (enemyX[i] < 0) enemyActive[i] = 0;
				}
			}
		}

		if ((mouseInput & MOUSE_INPUT_LEFT) && !(oldMouseInput & MOUSE_INPUT_LEFT))
		{
			for (i = 0; i < ENEMY_MAX; i++)
			{
				if (enemyActive[i] == 1)
				{
					float hdx = enemyX[i] - cx;
					if (hdx < 0) hdx = -hdx;

					if (hdx < 30.0f)
					{
						enemyActive[i] = 0;
						score += 1;
						PlaySoundMem(LoadSoundMem("click.wav"), DX_PLAYTYPE_BACK);
						break;
					}
				}
			}
		}

		for (i = 0; i < ENEMY_MAX; i++)
		{
			if (enemyActive[i] == 1)
			{
				DrawCircle(enemyX[i], enemyY[i], 15, GetColor(135, 206, 250), true);
			}
		}





		DrawLine(cx - 3, cy, cx + 3, cy, GetColor(0, 0, 0));
		DrawLine(cx, cy - 3, cx, cy + 3, GetColor(0, 0, 0));

		DrawFormatString(10, 10, GetColor(0, 0, 0), "score; %d", score);

		ScreenFlip();
		WaitTimer(16);
		if (ProcessMessage() == -1) break;
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break;
	}

	DxLib_End();
	return 0;
}