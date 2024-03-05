#include <stdio.h>
#include <string.h>

struct tpExemplar
{
	int cod;
	tpExemplar *prox;
};

struct tpLivro
{
	char autor[50], titulo[50];
	tpLivro *prox;
	tpExemplar *disponivel;
	tpExemplar *emprestado;
};

tpLivro *novoLivro(char autor[50], char titulo[50])
{
	tpLivro *nc = new tpLivro;
	strcpy(nc->autor,autor);
	strcpy(nc->titulo,titulo);
	nc -> prox = NULL;
	nc -> disponivel = NULL;
	nc -> emprestado = NULL;
	return nc;
}

tpExemplar *novoExemplar(int cod)
{
	tpExemplar *nc = new tpExemplar;
	nc -> cod = cod;
	nc -> prox = NULL;
	return nc;
}

tpLivro *inserirLivro(tpLivro *livro, char autor[50], char titulo[50])
{
	tpLivro *nc = novoLivro(autor,titulo);
	tpLivro *p = livro;
	if(livro == NULL)
	{
		livro = nc;
	}
	else
	{
		while(p -> prox != NULL)
		{
			p = p -> prox;
		}
		p -> prox = nc;
	}
	return livro;
}

tpExemplar *inserirExemplar(tpExemplar *inicio, int cod)
{
	
	tpExemplar *nc = novoExemplar(cod);
	tpExemplar *p = inicio;
	if(inicio == NULL)
	{
		inicio = nc;
	}
	else
	{
		while(p -> prox != NULL)
		{
			p = p -> prox;
		}
		p -> prox = nc;
	}
	return inicio;
}

tpLivro *buscaLivro(tpLivro *livro, char titulo[50])
{
	while(livro != NULL && stricmp(livro->titulo, titulo) != 0)
	{
		livro = livro -> prox;
	}
	return livro;
}

tpExemplar *buscaExemplar(tpExemplar *exemplar, int cod)
{
	while(exemplar != NULL && exemplar -> cod != cod)
	{
		exemplar = exemplar -> prox;
	}
	return exemplar;
}

tpLivro *ultimoLivro(tpLivro *livro)
{
	if(livro == NULL)
		return NULL;
	else {
		while(livro -> prox != NULL)
			livro = livro -> prox;
	}
	return livro;
}

void emprestaExemplar(tpLivro *livro, int cod)
{
	tpExemplar *p = livro -> disponivel;
	tpExemplar *s;
	if(p != NULL)
	{
		if(p -> cod == cod)
		{
			p = livro -> disponivel;
			livro -> disponivel = p -> prox;
			delete(p);
			livro -> emprestado = inserirExemplar(livro -> emprestado, cod);
		}
		else
		{
			while(p -> prox != NULL && p -> prox -> cod != cod)
			{
				p = p -> prox;
			}
			if(p -> prox != NULL)
			{
				s = p -> prox;
				p -> prox = p -> prox -> prox;
				delete(s);
				livro -> emprestado = inserirExemplar(livro -> emprestado, cod);
			}
		}
	}
}

void devolveExemplar(tpLivro *livro, int cod)
{
	tpExemplar *p = livro -> emprestado;
	tpExemplar *s;
	if(p != NULL)
	{
		if(p -> cod == cod)
		{
			p = livro -> emprestado;
			livro -> emprestado = p -> prox;
			delete(p);
			livro -> disponivel = inserirExemplar(livro -> disponivel, cod);
		}
		else
		{
			while(p -> prox != NULL && p -> prox -> cod != cod)
			{
				p = p -> prox;
			}
			if(p -> prox != NULL)
			{
				s = p -> prox;
				p -> prox = p -> prox -> prox;
				delete(s);
				livro -> disponivel = inserirExemplar(livro -> disponivel, cod);
			}
		}
	}
}

tpLivro *buscaTitulo(tpLivro *livro, char titulo[50])
{
	while(livro != NULL && stricmp(livro -> titulo, titulo) != 0)
	{
		livro = livro -> prox;
	}
	return livro;
}
