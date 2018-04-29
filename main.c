#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include "meuconio.h"

//2048

#define TAMANHO_MATRIZ 4

int matriz[TAMANHO_MATRIZ][TAMANHO_MATRIZ], score = 0, game_loop = 0, linhaAtual = -1, colunaAtual = -1;

//game_loop = 0 -> jogo rolando
//game_loop = 1 -> jogador ganhou (formou um quadrado 2048)
//game_loop = 2 -> a matriz está cheia, mas ainda há pelo menos uma jogada possível
//game_loop = -1 -> jogador perdeu
//score = pontuação do jogador
//linhaAtual, colunaAtual = mostram qual foi a última posição em que houve um agrupamento de números

char dir;
//variável que dirá qual a direção em que o usuário quer que os números se movam (direita, esquerda, cima ou baixo (d, e, c, b))

void botaZero();
//inicializa a matriz com zeros, que representarão uma posição vazia
void juntaNumeros(int linhaInicial, int colunaInicial, int linhaAlvo, int colunaAlvo);
//função que agrupa números iguais quando possível
void iniciaMatriz();
//gera duas posições na matriz e as preenche com o número 2
void imprimeMatriz();
//imprime a matriz do jogo para o usuário
void gameLoop();
//função que lerá o input do usuário enquanto for possível jogar
int checaVitoriaDerrota();
//retornará 1 se o usuário ganhar, 0 se ainda ha jogo e -1 se ele perdeu
int checaColuna(int linha, int dir);
int checaLinha(int coluna, int dir);

int main() {
  srand(time(NULL));

  int res;

  botaZero();

  iniciaMatriz();
   
  imprimeMatriz();

  gameLoop();

  res = checaVitoriaDerrota();

  if (res == 1)
    printf("Vc ganhou!\n");
  else
    printf("Derrota!\n");

  getch();
}

void botaZero() {
  int i, j;

  for (i = 0; i < TAMANHO_MATRIZ; i++) {
    for (j = 0; j < TAMANHO_MATRIZ; j++) {
      matriz[i][j] = 0;
    }
  }
}

void iniciaMatriz() {
  int i, linha, coluna;

  for (i = 0; i < 2; i++) {
    do {
      linha = rand() % 4;
      coluna = rand() % 4;
    } while (matriz[linha][coluna] != 0);

    matriz[linha][coluna] = 2;
  }
}

void gameLoop() {
    int fim = 0, i, j, pos, cont = 0;

    fim = checaVitoriaDerrota();
    
    fflush(stdin);
    
    scanf("%c", &dir);

    while (fim == 0)
	  {
      	if(dir == 'c' || dir == 'C')
      	{
      		for(i = 0; i < TAMANHO_MATRIZ; i++)
			{
				for(j = 0; j < TAMANHO_MATRIZ; j++)
				{
					pos = checaLinha(i, -1);
					
					if(matriz[j][i] > 0)
					{
						//Tem algo na posição atual...
						if(pos < j && pos > -1)
							if(pos > 0)
								if(matriz[pos - 1][i] == matriz[j][i] && ((pos - 1) != linhaAtual || i != colunaAtual) )
								{
									//Se o número logo acima da posição retornada for igual ao número da posição atual
									juntaNumeros(j, i, pos - 1, i);
									cont++;
								}
								else
								{
									//Se não há nenhum número na coluna acima da posição atual
									matriz[pos][i] = matriz[j][i];
									matriz[j][i] = 0;
									cont++;
								}
							else
							{
								matriz[pos][i] = matriz[j][i];
								matriz[j][i] = 0;
								cont++;
							}
						else
							if(j > 0)
								if(matriz[j][i] == matriz[j - 1][i] && ((j - 1) != linhaAtual || i != colunaAtual))
								{
									juntaNumeros(j, i, j - 1, i);
									cont++;
								}
					}	
				}
			}	
		}
		else if(dir == 'b' || dir == 'B')
		{
			for(i = TAMANHO_MATRIZ - 1; i >= 0; i--)
			{
				for(j = TAMANHO_MATRIZ - 1; j >= 0; j--)
				{
					if(matriz[j][i] > 0)
					{
						pos = checaLinha(i, 1);
						if(pos > j)
						{
							if(pos < 3)
								if(matriz[pos + 1][i] == matriz[j][i]  && ((pos + 1) != linhaAtual || i != colunaAtual))
								{
									juntaNumeros(j, i, pos + 1, i);
									cont++;
								}
								else
								{
									matriz[pos][i] = matriz[j][i];
									matriz[j][i] = 0;
									cont++;
								}
							else
							{
								matriz[pos][i] = matriz[j][i];
								matriz[j][i] = 0;
								cont++;
							}
						}
						else
							if(j < 3)
								if(matriz[j + 1][i] == matriz[j][i]  && ((j + 1) != linhaAtual || i != colunaAtual))
								{
									juntaNumeros(j, i, j + 1, i);
									cont++;
								}
					}
				}
			}
		}
		else if(dir == 'e' || dir == 'e')
		{
			for(i = 0; i < TAMANHO_MATRIZ; i++)
			{
				for(j = 0; j < TAMANHO_MATRIZ; j++)
				{
					pos = checaColuna(i, -1);
					
					if(matriz[i][j] > 0)
					{
						if(pos < j && pos > -1)
						{
							if(pos > 0)
								if(matriz[i][pos - 1] == matriz[i][j] && (i != linhaAtual || (pos - 1) != colunaAtual))
								{
									juntaNumeros(i, j, i, pos - 1);
									cont++;
								}
								else
								{
									matriz[i][pos] = matriz[i][j];
									matriz[i][j] = 0;
									cont++;
								}
							else
							{
								matriz[i][pos] = matriz[i][j];
								matriz[i][j] = 0;
								cont++;
							}
						}
						else
							if(j > 0)
								if(matriz[i][j] == matriz[i][j - 1] && (i != linhaAtual || (j - 1) != colunaAtual))
								{
									juntaNumeros(i, j, i, j - 1);
									cont++;
								}
					}
				}
			}
		}
		else if(dir == 'd' || dir == 'D')
		{
			for(i = TAMANHO_MATRIZ - 1; i >= 0; i--)
			{
				for(j = TAMANHO_MATRIZ - 1; j >= 0; j--)
				{
					pos = checaColuna(i, 1);
					
					if(matriz[i][j] > 0)
					{
						if(pos > j)
						{
							if(pos < 3)
								if(matriz[i][j] == matriz[i][pos + 1] && (i != linhaAtual || (pos + 1) != colunaAtual))
								{
									juntaNumeros(i, j, i, pos+1);
									cont++;
								}
								else
								{
									matriz[i][pos] = matriz[i][j];
									matriz[i][j] = 0;
									cont++;
								}
							else
							{
								matriz[i][pos] = matriz[i][j];
								matriz[i][j] = 0;
								cont++;
							}
						}
						else
							if(j < 3)
								if(matriz[i][j] == matriz[i][j + 1] && (i != linhaAtual || (j + 1) != colunaAtual))
								{
									juntaNumeros(i, j, i, j+1);
									cont++;
								}
					}
				}
			}
		}
		
		fim = checaVitoriaDerrota();
		
		if(fim == 0 || fim == 2)
		{
			if(cont > 0 && fim != 2)
			{
				do {
	            	i = rand() % TAMANHO_MATRIZ;
	            	j = rand() % TAMANHO_MATRIZ;
	          	} while (matriz[i][j] != 0);
	          	
	          	matriz[i][j] = 2;
			}
			
			cont = 0;
          	 
          	imprimeMatriz();
			
			fflush(stdin);
			
			scanf("%c", &dir);	
			
			linhaAtual = -1;
			colunaAtual = -1;		
		}
      }
    }

    void imprimeMatriz() {
      int i, j;

	  clrscr();
	  gotoxy(15, 2);
      printf("\n\t\t\tSCORE:%d\t\t\n", score);
      
      for (i = 0; i < TAMANHO_MATRIZ; i++) {
      	gotoxy(20, 5+i);
        for (j = 0; j < TAMANHO_MATRIZ; j++) {
        	
            if(matriz[i][j] == 0)
			{
				textbackground(15);
				textcolor(5);
                printf("     .     ");
			}
			else
			{
                if(matriz[i][j] == 2)
                {
                	textbackground(1);
        			textcolor(15);
				}
        		else if(matriz[i][j] == 4)
				{
					textbackground(3);
					textcolor(6);
				}
				else if(matriz[i][j] == 8)
				{
					textbackground(6);
					textcolor(4);
				}
				else if(matriz[i][j] == 16)	
        		{
        			textbackground(8);
					textcolor(12);	
				}	
        		else if(matriz[i][j] == 32)
        		{
        			textbackground(9);
        			textcolor(7);
				}
        		else if(matriz[i][j] == 64)
        		{
        			textbackground(13);
        			textcolor(11);
				}
        		else if(matriz[i][j] == 128)
        		{
        			textbackground(12);
        			textcolor(14);
				}
        		else if(matriz[i][j] == 256)
        		{
        			textbackground(14);
        			textcolor(13);
				}
        		else if(matriz[i][j] == 512)
        		{
        			textbackground(7);
        			textcolor(2);
				}
        		else if(matriz[i][j] == 1024)
        		{
        			textbackground(4);
        			textcolor(3);
				}
        		else if(matriz[i][j] == 2048)
        		{
        			textbackground(2);
        			textcolor(5);
				}

        		printf("     %d     ", matriz[i][j]);
			}
		}
        printf("\n\n");
      }
      
      textcolor(15);
      textbackground(0);
    }

    int checaVitoriaDerrota() {
      int i, j, ret = 0, cont, contJogadasPossiveis;
      cont = 0;
      contJogadasPossiveis = 0;

      for (i = 0; i < TAMANHO_MATRIZ; i++) {
        for (j = 0; j < TAMANHO_MATRIZ; j++) {
          if (matriz[i][j] > 0) {
            cont++;

            if (matriz[i][j] == 2048) {
              ret = 1;
              break;
            }
          }

        }
      }

      if (cont == TAMANHO_MATRIZ * TAMANHO_MATRIZ && ret == 0)
	  {
       for(i = 0; i < TAMANHO_MATRIZ; i++)
       {
       		for(j = 0; j < TAMANHO_MATRIZ; j++)
       		{
       			if(j > 0)
				   if(matriz[i][j - 1] == matriz[i][j])
				   	contJogadasPossiveis++;	
				if(j < TAMANHO_MATRIZ - 1)
					if(matriz[i][j + 1] == matriz[i][j])
				   		contJogadasPossiveis++;	
				if(i > 0)
					if(matriz[i - 1][j] == matriz[i][j])
						contJogadasPossiveis++;	
				if(i < TAMANHO_MATRIZ - 1)
					if(matriz[i + 1][j] == matriz[i][j])
						contJogadasPossiveis++;	
			}
	   }
	   
	   if(contJogadasPossiveis > 0)
	   	ret = 2;
	   else
	   	ret = -1;
   	}
   	
   	  contJogadasPossiveis = 0;

      return ret;
    }

    int checaColuna(int linha, int dir) {
      int i = 0, ret = -1;

      if (dir == 1) {
        //direita
        for (i = 0; i < TAMANHO_MATRIZ; i++) {
          if (matriz[linha][i] == 0)
            ret = i;
        }
      } else {
        //esquerda
        for (i = TAMANHO_MATRIZ - 1; i >= 0; i--) {
          if (matriz[linha][i] == 0)
            ret = i;
        }
      }

      return ret;
    }

    int checaLinha(int coluna, int dir) {
      int i, ret = -1;

      if (dir == 1) {
        //'B'
        for (i = 0; i < TAMANHO_MATRIZ; i++) {
          if (matriz[i][coluna] == 0)
            ret = i;
        }
      } else {
        //'C'
        for (i = TAMANHO_MATRIZ - 1; i >= 0; i--) {
          if (matriz[i][coluna] == 0)
            ret = i;
        }
      }

      return ret;
    }
    
	void juntaNumeros(int linhaInicial, int colunaInicial, int linhaAlvo, int colunaAlvo)
	{
		matriz[linhaAlvo][colunaAlvo] *= 2;
		score += matriz[linhaAlvo][colunaAlvo];
		matriz[linhaInicial][colunaInicial] = 0;
		
		linhaAtual = linhaAlvo;
		colunaAtual = colunaAlvo;
	}
