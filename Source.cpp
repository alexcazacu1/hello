#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<Windows.h>

const int height = 20;
const int width = 30
int x = width / 2, y = height / 2, punctex, punctey, fructex, fructey, score = 0,q;
int gameover = 0, tailx[100], taily[100], tail=2;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int y, int x)
{
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}
void puncte()
{
	punctex = rand() % (width-3);		//puncte normale care marasc scorul cu 10 si coada cu o unitate
	punctey = rand() % (height);
}
void fructe()
{
	fructex = rand() % (width - 3);			//fructe speciale care maresc scorul cu 30 si coada cu 3 unitati
	fructey = rand() % (height);
}
void tabla()
{
	//printeaza zidul de sus
	for (int i = 0; i< width + 2; i++)
	{
		SetConsoleTextAttribute(h, 4);
		printf("%c", 219);
		SetConsoleTextAttribute(h, 8);
	}
		printf("\n");

	//printeaza marginile si spatiul
	for (int i = 0; i< height; i++)
	{
		for (int j = 0; j<width; j++)
		{
			if (j == 0)
			{
				SetConsoleTextAttribute(h, 4);
				printf("%c", 219);
				SetConsoleTextAttribute(h, 8);
			}
			if (i == y && j == x)
			{
				SetConsoleTextAttribute(h, 9);
				printf("%c", 219);
				SetConsoleTextAttribute(h, 8);
			}
			else if ((i == punctey) && (j == punctex))
			{
				SetConsoleTextAttribute(h, 2);
				printf("%c", 235);
				SetConsoleTextAttribute(h, 8);
			}
			else if ((i == fructey) && (j == fructex) && score%110==0)
			{
				SetConsoleTextAttribute(h, 5);
				printf("%c", 234);
				SetConsoleTextAttribute(h, 8);
			}
			//sa apara coada
			else
			{
				int print = false;
				for (int k = 0; k<tail; k++)
				{
					if (tailx[k] == j && taily[k] == i)
					{
						SetConsoleTextAttribute(h, 9);
						printf("%c", 219);
						SetConsoleTextAttribute(h, 8);
						print = true;
					}

				}
				if (!print)
					printf(" ");
			}
			if (j == width - 1)
			{
				SetConsoleTextAttribute(h, 4);
				printf("%c", 219);
				SetConsoleTextAttribute(h, 8);
			}
		}
		printf("\n");
	}

	//printeaza zidul de jos
	for (int i = 0; i< width + 2; i++)
	{
		SetConsoleTextAttribute(h, 4);
		printf("%c", 219);
		SetConsoleTextAttribute(h, 8);
	}
	SetConsoleTextAttribute(h, 7);
	printf("\n\n \t SCORE:%d\n", score);
	SetConsoleTextAttribute(h, 8);
	if (gameover == 0)
	{
		SetConsoleTextAttribute(h, 7);
		printf("\t Mai ai 3 vieti:* * *");
		SetConsoleTextAttribute(h, 8);
	}
	if (gameover == 1)		//in cazul in care sarpele loveste zidul ii scade o viata si revinela pozitia initiala 
	{
		x = width / 2;
		y = height / 2;
		q = ' ';
		gameover++;	
	}
	if (gameover==2)
	{
		SetConsoleTextAttribute(h, 7);
		printf("\t Mai ai 2 vieti:* *");
		SetConsoleTextAttribute(h, 8);
	}
	if (gameover == 3)
	{
		x = width / 2;
		y = height / 2;
		q = ' ';
		gameover++;
	}
	if (gameover == 4)
	{
		SetConsoleTextAttribute(h, 7);
		printf("\t Mai ai o viata:*");
		SetConsoleTextAttribute(h, 8);
	}
}
void miscare()
{
	Sleep(10);
	if (_kbhit())
		q = _getch();
	{
		switch (q)
		{
		case 's':
			y++;
			break;
		case 'w':
			y--;
			break;
		case 'a':
			x--;
			break;
		case 'd':
			x++;
			break;
		}
	}

}
void joc()
{
	int precx = x;			//coada formata din doi vectori in functie de coordonate
	int precy = y;
	int prec2x, prec2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 0; i< tail; i++)
	{
		prec2x = tailx[i];
		prec2y = taily[i];
		tailx[i] = precx;
		taily[i] = precy;
		precx = prec2x;
		precy = prec2y;
	}

	if (x > width-1 || x < 0 || y> height - 1 || y < 0)
	{
		gameover++;

	}
	if ((x == punctex) && (y == punctey))
	{
		puncte();
		score = score + 10;
		tail++;
	}
	if ((x == fructex) && (y == fructey))
	{
		fructe();
		score = score + 30;
		tail+=3;
	}

}
void instructiune()
{	
	printf("\t\t\t\tSNAKE");
	printf("\n\n");
	printf("Ai 3 vieti, mananca punctele verzi pentru 10 puncte si pe cele mov pentru 30 de puncte.\nPentru a te misca foloseste tastele WASD.\n Apasa ENTER pentru a incepe jocul");
	while (1)
	{
		if (kbhit())
		if (getch() == 13)
			break;
	}
		
}
void main()
{
	instructiune();
	q = ' ';
	system("mode 40, 30");	//pentru marimea consolei
	puncte();
	fructe();
	while (gameover != 5)
	{
		tabla();
		miscare();
		joc();
		Sleep(123);
		system("cls");
	}
	printf("Ai pierdut\n");
	printf("Score=%d\n", score);
}
