/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_fillit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aquint <aquint@42.us.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 00:16:17 by aquint            #+#    #+#             */
/*   Updated: 2017/08/31 13:58:34 by aquint           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft_lq/libft.h"
#include "fillit.h"
#define TRUE 1
#define FALSE 0

int		r_fillit_solver(char **board, t_piece *head, int row, int col)
{
	char **piece;
	int	valid;

	if (head == NULL)
	{
		ft_putchar('b');
		return (TRUE);
	}
	piece = head->content;
	if (board[row] == '\0')
	{
		ft_putchar('c');
		return (FALSE);
	}
	valid = valid_check(board, piece, row, col);
	if (valid == FALSE)
	{
		if (board [row][col] == '\0')
			r_fillit_solver(board, head, row + 1, 0);
		else
			r_fillit_solver(board, head, row, col + 1);
		return (FALSE);	
	}
	else
	{
		ft_putchar('B');
		place_piece(board, piece, row, col);
		head = head->next;
		r_fillit_solver(board, head, 0, 0);
		if (head == NULL)
		{
			ft_putchar('d');
			return (TRUE);
		}
		else
		{
			ft_putchar('e');
			return (TRUE); // Brodie : change this to FALSE to get it to infinitily expand. 
		}
	}
}


int		valid_check(char **board, char **piece,  unsigned int row, unsigned int col)	
{
	unsigned int i;
	unsigned int c;

	i = 0;
	while (piece[i] != '\0')
	{
		c = 0;
		while (piece[i][c] != '\0')
		{
			if (piece[i][c] != '.')
			{
				if (((col + c) >= ft_strlen(&board[row][col])) || ((row + i) >= ft_strlen(board[row]))) 
					return (FALSE);
				else
				{
					if (board[row + i][col + c] == '.')
						c++;
					else
						return (FALSE);
				}
			}
			else
				c++;
		}
		i++;

	}
	return (TRUE);
}

char	**place_piece(char **board, char **piece, int row, int col)
{
	int i;
	int c;
	
	i = 0;
	while (piece[i] != '\0')
	{
		c = 0;
		while (piece[i][c] != '\0')
		{
			if (piece[i][c] != '.')
			{
				if (board[row + i][col + c] == '.')
				{
					board[row + i][col + c] = piece[i][c];
					c++;
				}
			}
			else
				c++;
		}
		i++;
	}
	return (board);
}

char	**fillit_board(int size)
{
	char **board;
	int i;
	int col;

	i = 0;
	if (!(board = (char**)ft_memalloc(sizeof(*board) * (size + 1))))
		return (NULL);
	while (i < size)
	{
		if (!(board[i] = (char*)ft_memalloc(sizeof(board) * (size + 1))))
			return (NULL);
		col = 0;
		while (col < size)
			board[i][col++] = '.';
		board[i][col] = '\0';
		i++;
	}
	board[i] = NULL;
	return (board);
}




int		solve_print(t_piece *head)
{
	unsigned int 	bsize;
	char 			**board;	
	t_piece 		*tmp;
	int 			i;
//	int 			result;

	i = 0;
	tmp = head;
	bsize = 2;
	while ((bsize * bsize) < (head->number * 4))
		bsize++;
	ft_putnbr(bsize);
	ft_putchar('\n');
	if (!(board = fillit_board(bsize)))
		return (0);
	while ((r_fillit_solver(board, head, 0, 0)) == 0)
	{
		ft_putchar('\n');
		ft_putarray(board);
		while (board[i] != '\0')
		{
			free(board[i]);
			i++;
		}
		free(board);
		if (!(board = fillit_board(++bsize)))
		{
			ft_putchar('t');
			return (0);
		}
		ft_putnbr(bsize);
		head = tmp;

	}
	ft_putchar('\n');
	ft_putarray(board);
	return (TRUE);
}