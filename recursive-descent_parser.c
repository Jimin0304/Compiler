#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	expression(void);
int	term(void);
int	factor(void);
void	error(int i);

enum {NL, PLUS, STAR, NUMBER, LPAREN, RPAREN, END} token;
char	ch;
int	num;

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

char	*ft_strcat(char *str, char ch)
{
	int	size;
	char	*temp;

	if (!str)
	{
		str = (char *)malloc(sizeof(char) * 2);
		str[0] = ch;
		str[1] = '\0';
		return (str);
	}
	size = strlen(str);
	temp = str;
	str = (char *)malloc(sizeof(char) * (size + 2));
	strcpy(str, temp);
	str[size] = ch;
	str[size + 1] = '\0';
	free (temp);
	return (str);
}		

void	get_token(void)
{
	char	*num_str;

	num_str = NULL;
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
	{
		token = NUMBER;
		num_str = ft_strcat(num_str, ch);
		while (is_digit((int) ch) == 1)
		{
			ch = getchar();
			num_str = ft_strcat(num_str, ch);
		}
		num = atoi(num_str);
		return ;
	}
	else if (ch == EOF)
		token = END;
	else
		token = NL;
	ch = getchar();
}

int	expression(void)
{
	int	result;

	result = term();
	while (token == PLUS)
	{
		get_token();
		result = result + term();
	}
	return (result);
}

int	term(void)
{
	int	result;

	result = factor();
	while (token == STAR)
	{
		get_token();
		result = result * factor();
	}
	return (result);
}

int	factor(void)
{
	int	result;

	if (token == NUMBER)
	{
		result = num;
		get_token();
	}
	else if (token == LPAREN)
	{
		get_token();
		result = expression();
		if (token == RPAREN)
			get_token();
		else
			error(2);
	}
	else
		error(1);
	return (result);
}

void	error(int i)
{
	printf("Syntax Error: ");
	switch (i) {
		case 1:
			printf("number of '(' expected.\n");
			break ;
		case 2:
			printf("')' expected.\n");
			break ;
		case 3:
			printf("EOF expected.\n");
			break ;
	}
	exit(1);
}

int	main(void)
{
	int	result;

	ch = getchar();
	get_token();
	result = expression();
	if (token != END)
		error(3);
	else
		printf("Right Syntax !!\nresult : %d\n", result);
	return (0);
}
