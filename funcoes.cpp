#include <stdio.h>
#include <conio2.h>
#include <windows.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "tad.h"

char pegaN(int &n)
{
	char aux[9];
	fflush(stdin);
	gets(aux);
	n = atoi(aux);
	return strlen(aux) > 0;
}

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
	printf("                                                                                                                ");
	for(int i=5;i<29;i++)
	{
		gotoxy(4,i);
		printf("                                                                                                                ");
	}
	l=0;
}

void ir(int &l)
{
	gotoxy(5,++l+4);
	if(l > 23)
	{
		getch();
		for(int i=5;i<29;i++)
		{
			gotoxy(4,i);
			printf("                                                                                                                ");
		}
		l=0;
	}
}

void h(void)
{
	gotoxy(5,3);
}

tpLivro *vInserirLivros(tpLivro *livro)
{
	FILE *ptr = fopen("BancoDeDados.txt","r");
	tpLivro p, *UltLiv;
	char aux[10];
	
	while(!feof(ptr))
	{
		fscanf(ptr,"%[^;] ; %[^;] ; %[^;];",&p.autor, &p.titulo,&aux);
		livro = inserirLivro(livro,p.autor, p.titulo);
		UltLiv = ultimoLivro(livro);
		
		while(stricmp(aux,"D") != 0)
		{
			UltLiv -> disponivel = inserirExemplar(UltLiv -> disponivel,atoi(aux));
			fscanf(ptr,"%[^;];",&aux);
		}
		fscanf(ptr,"%[^;];",&aux);
		
		while(stricmp(aux,"E") != 0)
		{
			UltLiv -> emprestado = inserirExemplar(UltLiv -> emprestado,atoi(aux));
			fscanf(ptr,"%[^;];",&aux);
		}
		fscanf(ptr,"\n");
	}
	fclose(ptr);
	return livro;
}

//A RESPEITO DO FSCANF, TEM QUE PUXAR DO ARQUIVO TEXTO ALEM DO AUTOR E TITULO, TEM Q PEGAR TBM O CODIGO DE CADA EXEMPLAR

void vExibirLivros(tpLivro *livro)
{
	int l;
	tpExemplar *p;
	
	limpar(l);
	h(); printf("*** Exibir livros ***");
	
	while(livro != NULL)
	{
		ir(l); printf("%s; %s",livro -> autor, livro -> titulo);
		ir(l); printf("Disponiveis: ");
		p = livro -> disponivel;
		while(p != NULL)
		{
			printf("%d ",p -> cod);
			p = p -> prox;
		}
		p = livro -> emprestado;
		ir(l); printf("Emprestados: ");
		while(p != NULL)
		{
			printf("%d ",p -> cod);
			p = p -> prox;
		}
		ir(l);
		livro = livro -> prox;
	}
	
	getch();
}

void atualizarTXT (tpLivro *livro)
{
	FILE *ptr = fopen("BancoDeDados.txt","w");
	tpExemplar *p;
	int l;
	
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
		fprintf(ptr,"D;");
		while(p != NULL)
		{
			fprintf(ptr,"%d;",p -> cod);
			p = p -> prox;
		}
		fprintf(ptr,"E;\n");
		livro = livro -> prox;
	}	
	fclose(ptr);
}

void vEmprestarLivros(tpLivro *livro)
{
	int l;
	int cod;
	char titulo[50], flag;
	tpLivro *p;
	tpExemplar *e;
	limpar(l);
	h(); printf("*** Emprestar Livros ***");
	
	ir(l); printf("Titulo do livro: ");
	fflush(stdin);
	gets(titulo);
	while(strlen(titulo) > 0)
	{
		p = buscaLivro(livro, titulo);
		
		if(p != NULL)
		{
			limpar(l);
			h(); printf("*** Emprestar Livros ***");
			ir(l); printf("%s; %s",p -> autor, p -> titulo);
			ir(l); printf("Disponiveis: ");
			e = p -> disponivel;
			flag = 0;
			while(e != NULL)
			{
				printf("%d ",e -> cod);
				e = e -> prox;
				flag = 1;
			}
			if(!flag)
			{
				printf("Nenhum exemplar!");
				ir(l);
				getch();
			}
			else
			{
				ir(l); printf("Codigo do exemplar: ");
				while(flag && pegaN(cod))
				{
					e = buscaExemplar(p -> disponivel, cod);
					if(e != NULL)
					{
						emprestaExemplar(p,cod);
					}
					else
					{
						ir(l); printf("Exemplar nao encontrado!");
						getch();
					}
					limpar(l);
					h(); printf("*** Emprestar Livros ***");
					ir(l); printf("%s; %s",p -> autor, p -> titulo);
					ir(l); printf("Disponiveis: ");
					e = p -> disponivel;
					flag = 0;
					while(e != NULL)
					{
						printf("%d ",e -> cod);
						e = e -> prox;
						flag = 1;
					}
					if(flag)
					{
						ir(l); printf("Codigo do exemplar: ");
					}
					else
					{
						printf("Nenhum exemplar!");
						ir(l);
						getch();
					}
				}
			}
		}
		else
		{
			ir(l); printf("Livro nao encontrado!");
			getch();
		}
		limpar(l);
		h(); printf("*** Emprestar Livros ***");
		
		ir(l); printf("Titulo do livro: ");
		fflush(stdin);
		gets(titulo);
	}
}

void vDevolverLivros(tpLivro *livro)
{
	int l;
	int cod;
	char titulo[50], flag;
	tpLivro *p;
	tpExemplar *e;
	limpar(l);
	h(); printf("*** Devolver Livros ***");
	
	ir(l); printf("Titulo do livro: ");
	fflush(stdin);
	gets(titulo);
	while(strlen(titulo) > 0)
	{
		p = buscaLivro(livro, titulo);
		
		if(p != NULL)
		{
			limpar(l);
			h(); printf("*** Devolver Livros ***");
			ir(l); printf("%s; %s",p -> autor, p -> titulo);
			ir(l); printf("Emprestados: ");
			e = p -> emprestado;
			flag = 0;
			while(e != NULL)
			{
				printf("%d ",e -> cod);
				e = e -> prox;
				flag = 1;
			}
			if(!flag)
			{
				printf("Nenhum exemplar!");
				ir(l);
				getch();
			}
			else
			{
				ir(l); printf("Codigo do exemplar: ");
				while(flag && pegaN(cod))
				{
					e = buscaExemplar(p -> emprestado, cod);
					if(e != NULL)
					{
						devolveExemplar(p,cod);
					}
					else
					{
						ir(l); printf("Exemplar nao encontrado!");
						getch();
					}
					limpar(l);
					h(); printf("*** Devolver Livros ***");
					ir(l); printf("%s; %s",p -> autor, p -> titulo);
					ir(l); printf("Emprestados: ");
					e = p -> emprestado;
					flag = 0;
					while(e != NULL)
					{
						printf("%d ",e -> cod);
						e = e -> prox;
						flag = 1;
					}
					if(flag)
					{
						ir(l); printf("Codigo do exemplar: ");
					}
					else
					{
						printf("Nenhum exemplar!");
						ir(l);
						getch();
					}
				}
			}
		}
		else
		{
			ir(l); printf("Livro nao encontrado!");
			getch();
		}
		limpar(l);
		h(); printf("*** Devolver Livros ***");
		
		ir(l); printf("Titulo do livro: ");
		fflush(stdin);
		gets(titulo);
	}
}


void vRelatorio(tpLivro *livro, char flagExemplar, char flagBusca)
{
	int l;
	char aux[50], flag = 0;
	tpExemplar *p;
	limpar(l);
	h(); printf("*** Relatorio ***");
	if(flagBusca == 'A')
	{
		ir(l); printf("Autor: ");
		fflush(stdin);
		gets(aux);
		while(livro != NULL)
		{
			if(stricmp(livro -> autor, aux) == 0)
			{
				ir(l);
				flag = 1;
				ir(l); printf("Titulo: %s", livro -> titulo);
				
				if(flagExemplar == 'D')
				{
					ir(l); printf("Disponivel: ");
					p = livro -> disponivel;
					while(p != NULL)
					{
						printf("%d ",p -> cod);
						p = p -> prox;
					}
				}
				else
				{
					ir(l); printf("Emprestado: ");
					p = livro -> emprestado;
					while(p != NULL)
					{
						printf("%d ",p -> cod);
						p = p -> prox;
					}
				}
			}
			livro = livro -> prox;
		}
		if(flag == 0)
		{
			ir(l); printf("Nenhum livro encontrado!");
		}
	}
	else
	{
		ir(l); printf("Titulo: ");
		fflush(stdin);
		gets(aux);
		ir(l);
		livro = buscaTitulo(livro, aux);
		if(livro != NULL)
		{
			flag = 1;
			ir(l); printf("Autor: %s\n", livro -> autor);
			
			if(flagExemplar == 'D')
			{
				ir(l); printf("Disponivel: ");
				p = livro -> disponivel;
				while(p != NULL)
				{
					printf("%d ",p -> cod);
					p = p -> prox;
				}
			}
			else
			{
				ir(l); printf("Emprestado: ");
				p = livro -> emprestado;
				while(p != NULL)
				{
					printf("%d ",p -> cod);
					p = p -> prox;
				}
			}
			ir(l);
		}
	}
	getch();
}

void vConsultaLivros(tpLivro *livro, char &flagExemplar, char &flagBusca)
{
	int l;
	char op;
	do
	{
		limpar(l);
		h(); printf("*** Consulta Livros ***");
		if(flagExemplar == 'D')
		{
			ir(l); printf("[A] Disponiveis");
		}
		else
		{
			ir(l); printf("[A] Emprestados");
		}
			
		if(flagBusca == 'A')
		{
			ir(l); printf("[B] Autor");
		}
		else
		{
			ir(l); printf("[B] Titulo");
		}
		ir(l);
		ir(l); printf("[1] Buscar");
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

void quant(tpLivro *livro)
{
	int qtdDistintos=0, qtdAutor, qtdExemplares=0, qtdEmprestados=0, qtdDisponiveis=0, l, qtdMaisEmprestado=0, c=0;
	char autor[50], titulo[50];
	tpLivro *p, *q;
	tpExemplar *e;
	p = livro;
	while(p != NULL)
	{
		qtdDistintos++;
		e = p -> disponivel;
		while(e != NULL)
		{
			qtdDisponiveis++;
			qtdExemplares++;
			
			e = e -> prox;
		}
		
		c=0;
		e = p -> emprestado;
		while(e != NULL)
		{
			qtdEmprestados++;
			qtdExemplares++;
			c++;
			e = e -> prox;
		}
		if(c > qtdMaisEmprestado)
		{
			qtdMaisEmprestado = c;
			strcpy(autor, p -> autor);
			strcpy(titulo, p -> titulo);
		}
		p = p -> prox;
	}
	qtdAutor = qtdDistintos;
	p = livro;
	while(p != NULL)
	{
		q = p -> prox;
		while(q != NULL && stricmp(q -> autor, p -> autor) != 0)
		{
			q = q -> prox;
		}
		if(q != NULL)
			qtdAutor--;
		p = p -> prox;
	}
	
	limpar(l);
	h(); printf("*** Relatorio de quantidades ***");
	ir(l); printf("Livros: %d",qtdDistintos);
	ir(l); printf("Exemplares: %d",qtdExemplares);
	ir(l); printf("Emprestados: %d",qtdEmprestados);
	ir(l); printf("Disponiveis: %d",qtdDisponiveis);
	ir(l); printf("Autores: %d",qtdAutor);
	ir(l);
	ir(l); printf("Livro com mais exemplares emprestados: ");
	ir(l); printf("  %s; %s",autor, titulo);
	ir(l); printf("  Quantidade de emprestados: %d",qtdMaisEmprestado);
	getch();
}

int main ()
{
	quadro();
	int l;
	tpLivro *livro = NULL;
	char flagExemplar = 'D';
	char flagBusca = 'A';
	char op;
	livro = vInserirLivros(livro);
	do
	{
		limpar(l);
		h(); printf("*** Livros ***");
		
		ir(l); printf("[1] Emprestar livros");
		ir(l); printf("[2] Devolver livros");
		ir(l); printf("[3] Exibir livros");
		ir(l); printf("[4] Consultar livros");
		ir(l); printf("[5] Relatorio de quantidades");
		op = toupper(getch());
		switch(op)
		{
			case '1':
				vEmprestarLivros(livro);
				atualizarTXT(livro);
				break;
			case '2':
				vDevolverLivros(livro);
				atualizarTXT(livro);
				break;
			case '3':
				vExibirLivros(livro);
				break;
			case '4':
				vConsultaLivros(livro, flagExemplar, flagBusca);
				break;
			case '5':
				quant(livro);
				break;
		}
	} while(op != 27);
}
