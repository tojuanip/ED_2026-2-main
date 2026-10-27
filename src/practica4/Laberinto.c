#include "Laberinto.h"
#include <windows.h>


void setColorAndBackground(int forgC, int backC)
{
	WORD wColor = ((backC & 0x0F) << 4) + (forgC & 0x0F);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}

void gotoxy(int x, int y)
{
	COORD coord = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

Laberinto crear_laberinto(void)
{
    int i,j;
    char *tmp = 
"xxxxxxxxxxxxxxxxxxxxxxxxxx\
xAx*****x****************x\
x*xxx*x*x*xxxxxxxxx*xxxx*x\
x*****x*x******x**x****x*x\
xxxxxxx*xxxxxx*xx*xxxx*xxx\
x*****x*x****x*x****xx***x\
x*xxx*x*xxxx*x*x*xxxxx*x*x\
x***x*x****x*****xxxxxxx*x\
xxx*x*xxxx*xxxxxxx****x**x\
x*x*x***xx****xx***xx*x*xx\
x*x*x*x*xxxxx**x*xxxx*x**x\
x*x*x*x***x*xx*x****x*xx*x\
x*x*x*xxx****x*x*xx*x****x\
x*x*x*xxxxxxxx*x**x*xxxx*x\
x***x********x*xx*x*x****x\
x*xxxxxxxxxx*x**xxx*x*xxxx\
x***x******x**x*****x**x*x\
xxx*x*xxxxxxx*xxxxxxxx*x*x\
x*x*x*******x****xx****x*x\
x*x*x*xxxxx*xxxx*xx*xxxx*x\
x*x*x****xx***x**xx*x****x\
x*x*xxxxxxx*x**x*xx*x*x*xx\
x*x*********xx*x*xx*xxx*xx\
x*xxxxxxxxxxx**x*********x\
x***x***x***x*xxxxxxxxxx*x\
x*x***x***x*************Bx\
xxxxxxxxxxxxxxxxxxxxxxxxxx\0";

    Laberinto lab;
    lab = (unsigned char**) malloc(sizeof(unsigned char *)*REN);
    
    for(i=0;i<REN;i++)
    {
        lab[i] = (unsigned char*) malloc(sizeof(unsigned char)*COL);
    }
    
    for(i=0;i<REN;i++)
    {
        //printf("\n\r");
        for(j=0;j<COL;j++)
        {
            //printf("%c",tmp[(i*COL)+j]);
            lab[i][j] = tmp[(i*COL)+j];
        }   
    }
    return lab;
}

void liberarLaberinto(Laberinto lab)
{
	for(int i = 0; i<REN;i++)
		free(lab[i]);
	free(lab);
}

void imprimirLab(Laberinto lab)
{
	int i, j;
	gotoxy(0, 0);

	for(i = 0; i < REN; i++)
    {
        for(j = 0; j < COL; j++)
        {
            char c = lab[i][j];
            int forgC = 0;
            int backC = 0;

            if (c == 'x' || c == 'X') 
			{
                forgC = 0;  backC = 15;
            } 
			else if (c == '*') 
			{
                forgC = 0;  backC = 2;
            }
			else if (c == '.')
			{
                forgC = 0;  backC = 14;
            } 
			else if (c == 'o' || c == 'O') 
			{
                forgC = 15; backC = 4;
            } 
			else if (c == 'A' || c == 'B') 
			{
                forgC = 0;  backC = 14;
            }

            setColorAndBackground(forgC, backC);
            if (c == '*') {
                printf("  ");
            } else {
                printf("%c ", c);
            }
        }   
        printf("\n");
    }
    setColorAndBackground(7, 0);
}

void setAoB(Laberinto lab,Coordenada punto,char caracter)
{
	for(int i=0;i<REN;i++)
    {
        for(int j=0;j<COL;j++)
        {
			if(lab[i][j]==caracter)
				lab[i][j]='*';
			if(i == punto.x && j== punto.y)				
				lab[i][j]=caracter;
        }   
    }
}

void setOrigen(Laberinto lab,Coordenada origen)
{
	setAoB(lab,origen,'A');
}

void setDestino(Laberinto lab,Coordenada destino)
{
	setAoB(lab,destino,'B');
}
