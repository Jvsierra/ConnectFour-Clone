#include <stdio.h>
#include <conio.h>
#include "meuconio.h"

//Jogo "Connect Four" para dois jogadores

#define L 6
#define C 7

int m[L][C], turno = 1;

void incializaMatriz();
void imprimeMatriz();
void gameLoop();

void inicializaMatriz()
{
	int i, j;
	
	for(i = 0; i < L; i++)
		for(j = 0; j < C; j++)
			m[i][j] = 0;
}

void imprimeMatriz()
{
	int i, j;
	textbackground(0);
	textcolor(15);
	clrscr();
	textbackground(7);
	for(i = 0; i < L; i++)
	{
		gotoxy(20, 5+i);
		for(j = 0; j < C; j++)
		{
			if(m[i][j] == 0)
			{
				textcolor(15);
				printf("| |");
			}	
			else
			{
				textcolor(15);
				printf("|");
				
				if(m[i][j] == 1)
					textcolor(4);
				else
					textcolor(1);
					
				printf("O");
				
				textcolor(15);
				printf("|");
			}
				
		}
		printf("\n");
	}
	
	textbackground(0);
	textcolor(15);
}

int resultadoJogo();

void gameLoop()
{
	int linha, coluna, res;
	
	printf("Jogada do jogador %d (linha, coluna):\n", turno);
	scanf("%d %d", &linha, &coluna);
	
	res = resultadoJogo();
	
	while(res == 0)
	{
		while(linha < 0 || coluna < 0 || coluna >= C || linha >= L || m[linha][coluna] != 0)
		{
			printf("Jogada do jogador %d (linha, coluna):\n", turno);
			scanf("%d %d", &linha, &coluna);
		}
		
		m[linha][coluna] = turno;
		
		res = resultadoJogo();
		
		imprimeMatriz();
		
		if(res == 0)
		{
			if(turno == 1)
				turno = 2;
			else
				turno = 1;
			
			printf("Jogada do jogador %d (linha, coluna):\n", turno);
			scanf("%d %d", &linha, &coluna);
		}
	}
	
	if(res == -1)
		printf("Empate!\n");
	else
		printf("Vitoria do jogador %d!\n", turno);
}

int resultadoJogo()
{
	int i, j, k, a, ret, cont, contJogadas;
	ret = 0;
	
	for(i = 0; i < L; i++)
		for(j = 0; j < C; j++)
		{
			if(m[i][j] > 0)
			{
				contJogadas++;
				//Checa na horizontal
				if(j + 3 < C)
				{
					cont = 0;
					k = j + 1;
					while(k <= j + 3 && cont < 3 && m[i][k] == m[i][j])
					{
						k++;
						cont++;
					}
					
					if(cont == 3)
					{
						ret = m[i][j];
						break;
					}
				}
				
				//Checa na vertical
				if(i + 3 < L)
				{
					cont = 0;
					k = i+1;
					
					while(k <= i + 3 && cont < 3 && m[k][j] == m[i][j])
					{
						k++;
						cont++;
					}
					
					if(cont == 3)
					{
						ret = m[i][j];
						break;
					}
				}
				
				//Checa na diagonal
				if(j + 3 < C && i - 3 <= 0)
				{
					cont = 0;
					k = i - 1;
					a = j + 1;
					
					while(k >= 0 && a <= i + 3 && cont < 3 && m[k][a] == m[i][j])
					{
						k--;
						a++;
						cont++;
					}
					
					if(cont == 3)
					{
						ret = m[i][j];
						break;
					}
				}
			}
		}
		
		if(contJogadas == L * C && ret == 0)
			//empate
			ret = -1;
		
	return ret;
}

int main()
{
	inicializaMatriz();
	imprimeMatriz();
	gameLoop();
	
	getch();	
}
