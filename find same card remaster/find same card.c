#include <stdio.h>
#include <Windows.h>
#include <stdlib.h> //랜덤함수를 쓰기위함
#include <time.h>


struct a {
	int x;
	int y;
};

int x, y, sel = 0;
char card[4][4] = { {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0} }; //카드의 상태를 나타내는 배열(0이면 뒷면 1이면 앞면 2는 잠시 뒤집은 앞면)
char map[4][4], pic[2][8] = { {'@', '#', '%', '&', '*', '<', '^', '>' }, {0, 0, 0, 0, 0, 0, 0, 0 } }; //16개의 칸에 들어갈 8개의 문자와 들어간 횟수를 저장하는 배열
void shuffle();
void chul();
struct a ipruk(struct a *);
void check();
void stdisp();
struct a firstchoice;
struct a secondchoice;

void main()
{
	stdisp();
	shuffle();

	while (1)									//전체가 반복함
	{
		chul();
		ipruk(&firstchoice);
		chul();
		ipruk(&secondchoice);
		chul();
		Sleep(1000);																	//화면을 1초동안 멈춤
		check();
		if (card[0][0] == 1 && card[0][1] == 1 && card[0][2] == 1 && card[0][3] == 1 && card[1][0] == 1 && card[1][1] == 1 && card[1][2] == 1 && card[1][3] == 1 && card[2][0] == 1 && card[2][1] == 1 && card[2][2] == 1 && card[2][3] == 1 && card[3][0] == 1 && card[3][1] == 1 && card[3][2] == 1 && card[3][3] == 1)
		{
			printf("잘하셨습니다.\n");
			break;						//모두 앞면이 되면 끝남
		}
	}
	system("pause");
}
void shuffle()
{
	srand((unsigned)time(NULL)); // 정확한 난수를 생성하기 위한 명령어
	for (x = 0; x < 4; x++)						//16개의 칸에 무작위로 넣기위한 for
	{
		for (y = 0; y < 4; y++)
		{
			while (1)							//16개가 모두 채워질때까지 무한반복
			{
				sel = rand() % 8;				//숫자8개중 무작위로 한개를 뽑음
				if (pic[1][sel] < 2)			//뽑은 횟수가 2보다 작을때
				{
					map[x][y] = pic[0][sel];	//뽑은 문자를 16개 칸 안에 배치함
					pic[1][sel] += 1;			//뽑은 횟수를 1개 증가시킴
					break;						//1개를 배치시켰으므로 반복문을 빠져나감
				}
			}
		}
	}
}
void chul()
{
	system("cls");							//화면을 지움
	for (y = 0; y < 4; y++)
	{
		for (x = 0; x < 4; x++)
		{
			if (card[y][x] == 0)			//카드의 상태가 뒷면이면 ? 로 나타냄
			{
				printf(" ?  ");
			}
			else							//카드의 상태가 앞면이면 그 자리의 문자로 나타냄
			{
				printf(" %c  ", map[y][x]);
			}
		}
		printf("\n\n");
	}
}
struct a ipruk(struct a *choice)
{
	while (1)								//처음 뒤집을 카드의 좌표를 입력받음
	{
		printf("뒤집을 x좌표를 입력하세요(0~3): ");
		scanf_s("%d", &choice->x);
		printf("뒤집을 y좌표를 입력하세요(0~3): ");
		scanf_s("%d", &choice->y);
		if (choice->x < 0 || choice->y < 0 || choice->x >= 4 || choice->y >= 4) //입력값은 0~3
		{
			printf("입력값은 0부터3까지 입니다\n");
		}
		else if (card[choice->y][choice->x] != 0) //뒷면이 아닌 카드를 선택했을때
		{
			printf("뒷면인 카드를 선택해주세요\n");
		}
		else
		{
			card[choice->y][choice->x] = 2; // 선택한 카드를 잠시 앞면인 상태로 바꿈
			break;
		}
	}
	return *choice;
}
void check()
{
	if (map[firstchoice.y][firstchoice.x] == map[secondchoice.y][secondchoice.x])  //선택한 문자 2개가 같으면
	{
		card[firstchoice.y][firstchoice.x] = 1;										//카드의 상태를 앞면으로 만듬
		card[secondchoice.y][secondchoice.x] = 1;
	}
	else
	{
		card[firstchoice.y][firstchoice.x] = 0;										//선택한 문자2개가 같지 않으면 다시 뒤집음
		card[secondchoice.y][secondchoice.x] = 0;
	}
}
void stdisp()
{
	printf("같은그림찾기 made by 황익주\n\n아무 키나 누르시면 시작합니다.\n\n");
	system("pause");
}