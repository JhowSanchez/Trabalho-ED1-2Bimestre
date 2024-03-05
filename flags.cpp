#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tad.h"

void quadro()
{
	for(int i=4;i<119;i++)
	{
		gotoxy(i,2);
		printf("%c",196);
		gotoxy(i,4);
		printf("%c",196);
		gotoxy(i,29);
		printf("%c",196);
	}
	for(int i=2;i<30;i++)
	{
		gotoxy(3,i);
		printf("%c",179);
		gotoxy(118,i);
		printf("%c",179);
	}
	gotoxy(3,2);
	printf("%c",218);
	gotoxy(3,4);
	printf("%c",195);
	gotoxy(118,2);
	printf("%c",191);
	gotoxy(118,4);
	printf("%c",180);
	gotoxy(118,29);
	printf("%c",217);
	gotoxy(3,29);
	printf("%c",192);
}

void limpar(int &l)
{
	gotoxy(4,3);
	printf("                                                                                                                  ");
	for(int i=5;i<29;i++)
	{
		gotoxy(4,i);
		printf("                                                                                                                  ");
	}
	l=0;
}

void ir(int &l)
{
	gotoxy(5,++l+4);
}

void h(void)
{
	gotoxy(5,3);
}

tpLivro *lerReg(FILE *ptr, tpLivro *livro)
{
	char autor[50], titulo[50];
	int qtdEmprestado, qtdDisponivel, i;
	tpLivro *p;
	fscanf(ptr,"%[^;];%[^;];%d;%d;\n",&autor,&titulo,&qtdDisponivel,&qtdEmprestado);
	livro = inserirLivro(livro,autor,titulo);
	p = ultimoLivro(livro);
	for(i=0;i<qtdDisponivel;i++)
	{
		p -> disponivel = inserirExemplar(p -> disponivel, i+1);
	}
	for(;i<qtdDisponivel+qtdEmprestado;i++)
	{
		p -> emprestado = inserirExemplar(p -> emprestado, i+1);
	}
	return livro;
}

tpLivro *vInserirLivros(tpLivro *livro)
{
	FILE *ptr = fopen("livros.txt","r");
	while(!feof(ptr))
	{
		livro = lerReg(ptr,livro);
	}
	return livro;
	fclose(ptr);
}

//A RESPEITO DO FSCANF, TEM QUE PUXAR DO ARQUIVO TEXTO ALEM DO AUTOR E TITULO, TEM Q PEGAR TBM O CODIGO DE CADA EXEMPLAR

void vExibirLivros(tpLivro *livro)
{
	clrscr();
	printf("*** Exibir livros ***\n\n");
	exibirLivros(livro);
	getch();
}

void atualizarTXT (tpLivro *livro)
{
	FILE *ptr = fopen("livros.txt","w");
	tpExemplar *p;
	
	clrscr();
	
	while(livro != NULL)
	{
		fprintf(ptr,"%s;%s;",livro -> autor, livro -> titulo);
		p = livro -> disponivel;
		while(p != NULL)
		{
			fprintf(ptr,"%d;",p -> cod);
			p = p -> prox;
		}
		p = livro -> emprestado;
		fprintf(ptr,";");
		while(p != NULL)
		{
			fprintf(ptr,"%d;",p -> cod);
			p = p -> prox;
		}
		fprintf(ptr,"\n");
		livro = livro -> prox;
	}	
	fclose(ptr);
}

void vEmprestarLivros(tpLivro *livro)
{
	int cod;
	char autor[50], titulo[50];
	tpLivro *p;
	tpExemplar *e;
	clrscr();
	printf("*** Emprestar Livros ***\n\n");
	
	printf("  Autor: ");
	fflush(stdin);
	gets(autor);
	while(strlen(autor) > 0)
	{
		printf("  Titulo: ");
		fflush(stdin);
		gets(titulo);
		
		p = buscaLivro(livro, autor, titulo);
		
		if(p != NULL)
		{
			printf("  Codigo do exemplar: ");
			scanf("%d",&cod);
			e = buscaExemplar(p -> disponivel, cod);
			if(e != NULL)
			{
				emprestaExemplar(p,cod);
				printf("  Emprestimo realizado!\n");
				getch();
			}
			else
			{
				printf("  Exemplar nao encontrado!\n");
				getch();
			}
		}
		else
		{
			printf("  Livro nao encontrado!\n");
			getch();
		}
		clrscr();
		printf("*** Emprestar Livros ***\n\n");
		
		printf("  Autor: ");
		fflush(stdin);
		gets(autor);
	}
}

void vDevolverLivros(tpLivro *livro)
{
	int cod;
	char autor[50], titulo[50];
	tpLivro *p;
	tpExemplar *e;
	clrscr();
	printf("*** Devolver Livros ***\n\n");
	
	printf("  Autor: ");
	fflush(stdin);
	gets(autor);
	while(strlen(autor) > 0)
	{
		printf("  Titulo: ");
		fflush(stdin);
		gets(titulo);
		
		p = buscaLivro(livro, autor, titulo);
		
		if(p != NULL)
		{
			printf("  Codigo do exemplar: ");
			scanf("%d",&cod);
			e = buscaExemplar(p -> emprestado, cod);
			if(e != NULL)
			{
				devolveExemplar(p,cod);
				printf("  Devolucao realizado!\n");
				getch();
			}
			else
			{
				printf("  Exemplar nao encontrado!\n");
				getch();
			}
		}
		else
		{
			printf("  Livro nao encontrado!\n");
			getch();
		}
		clrscr();
		printf("*** Devolver Livros ***\n\n");
		
		printf("  Autor: ");
		fflush(stdin);
		gets(autor);
	}
}


void vRelatorio(tpLivro *livro, char flagExemplar, char flagBusca)
{
	char aux[50], flag = 0;
	tpExemplar *p;
	clrscr();
	printf("*** Relatorio ***\n\n");
	if(flagBusca == 'A')
	{
		printf("  Autor: ");
		fflush(stdin);
		gets(aux);
		while(livro != NULL)
		{
			if(stricmp(livro -> autor, aux) == 0)
			{
				printf("\n");
				flag = 1;
				printf("  Titulo: %s\n", livro -> titulo);
				
				if(flagExemplar == 'D')
				{
					printf("  Disponivel: ");
					p = livro -> disponivel;
					while(p != NULL)
					{
						printf("%d ",p -> cod);
						p = p -> prox;
					}
				}
				else
				{
					printf("  Emprestado: ");
					p = livro -> emprestado;
					while(p != NULL)
					{
						printf("%d ",p -> cod);
						p = p -> prox;
					}
				}
				printf("\n");
			}
			livro = livro -> prox;
		}
		if(flag == 0)
		{
			printf("  Nenhum livro encontrado!\n");
		}
	}
	else
	{
		printf("  Titulo: ");
		fflush(stdin);
		gets(aux);
		printf("\n");
		livro = buscaTitulo(livro, aux);
		if(livro != NULL)
		{
			flag = 1;
			printf("  Autor: %s\n", livro -> autor);
			
			if(flagExemplar == 'D')
			{
				printf("  Disponivel: ");
				p = livro -> disponivel;
				while(p != NULL)
				{
					printf("%d ",p -> cod);
					p = p -> prox;
				}
			}
			else
			{
				printf("  Emprestado: ");
				p = livro -> emprestado;
				while(p != NULL)
				{
					printf("%d ",p -> cod);
					p = p -> prox;
				}
			}
			printf("\n");
		}
	}
	getch();
}

void vConsultaLivros(tpLivro *livro, char &flagExemplar, char &flagBusca)
{
	char op;
	do
	{
		clrscr();
		printf("*** Consulta Livros***\n\n");
		if(flagExemplar == 'D')
		{
			printf("  [A] Disponiveis\n");
		}
		else
		{
			printf("  [A] Emprestados\n");
		}
			
		if(flagBusca == 'A')
		{
			printf("  [B] Autor\n\n");
		}
		else
		{
			printf("  [B] Titulo\n\n");
		}
		
		printf("  [1] Buscar");
		op = toupper(getch());
		switch(op)
		{
			case 'A':
				if(flagExemplar == 'D')
				{
					flagExemplar = 'E';
				}
				else
				{
					flagExemplar = 'D';
				}
				break;
			case 'B':
				if(flagBusca == 'A')
				{
					flagBusca = 'T';
				}
				else
				{
					flagBusca = 'A';
				}
				break;
			case '1':
				vRelatorio(livro, flagExemplar, flagBusca);
				break;
		}
	} while(op != 27);
}

int main ()
{
	int l;
	getch();
	tpLivro *livro = NULL;
	char flagExemplar = 'D';
	char flagBusca = 'A';
	char op;
	livro = vInserirLivros(livro);
	do
	{
		clrscr();
		printf("*** Livros ***\n\n");
		
		printf("  [1] Emprestar livros\n");
		printf("  [2] Devolver livros\n");
		printf("  [3] Exibir livros\n");
		printf("  [4] Consultar livros\n");
		op = toupper(getch());
		switch(op)
		{
			case '1':
				vEmprestarLivros(livro);
				break;
			case '2':
				vDevolverLivros(livro);
				break;
			case '3':
				vExibirLivros(livro);
				break;
			case '4':
				vConsultaLivros(livro, flagExemplar, flagBusca);
				break;
		}
	} while(op != 27);
}
