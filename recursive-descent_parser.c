#include <stdio.h>
#include <stdlib.h>

void	expression(void);
void	term(void);
void	factor(void);
void	error(int i);

enum {NL, PLUS, STAR, NUMBER, LPAREN, RPAREN, END} token;
char	ch;

int	is_whitespace(int c)
{
	if ((9 <= ch && ch <= 13) || (ch == 32))
		return (1);
	return (0);
}

int	is_digit(int c)
{
	if (48 <= c && c <= 57)
		return (1);
	return (0);
}

void	get_token(void)
{
	ch = getchar();
	while (is_whitespace((int) ch) == 1)
		ch = getchar();
	if (ch == '+')
		token = PLUS;
	else if (ch == '*')
		token = STAR;
	else if (ch == '(')
		token = LPAREN;
	else if (ch == ')')
		token = RPAREN;
	else if (is_digit((int) ch) == 1)
		token = NUMBER;
	else if (ch == EOF)
		token = END;
	else
		token = NL;
}

void	expression(void)
{
	term();
	while (token == PLUS)
	{
		get_token();
		term();
	}
}

void	term(void)
{
	factor();
	while (token == STAR)
	{
		get_token();
		factor();
	}
}

void	factor(void)
{
	if (token == NUMBER)
		get_token();
	else if (token == LPAREN)
	{
		get_token();
		expression();
		if (token == RPAREN)
			get_token();
		else
			error(2);
	}
	else
		error(3);
}

void	error(int i)
{
	printf("Syntax Error: ");
	switch (i) {
		case 1:
			printf("Undefined tokens.\n");
			break ;
		case 2:
			printf("Unclosed parentheses.\n");
			break ;
		case 3:
			printf("Undefined factors.\n");
			break ;
	}
	exit(1);
}

int	main(void)
{
	get_token();
	expression();
	if (token != END)
		error(1);
	else
		printf("Right Syntax !!\n");
	return (0);
}
