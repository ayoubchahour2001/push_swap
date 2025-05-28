/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahour <achahour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:59:40 by achahour          #+#    #+#             */
/*   Updated: 2025/05/16 19:33:20 by achahour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

static	long	ft_atol(const char *str)
{
	long	num;
	int		isneg;
	int		i;

	num = 0;
	isneg = 1;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'
			|| str[i] == '\n' || str[i] == '\r'
			|| str[i] == '\v' || str[i] == '\f'))//LOOP FOR SKIP WHITESPACE
		i++;
	if (str[i] == '+') //We just skip it because isneg remains 1 is positive number
		i++;
	else if (str[i] == '-') //We multiply isneg by -1 to sort negative number
	{
		isneg *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9') //The loop run while str[i] is a digit between 0 and 9
	{
		num = (num * 10) + (str[i] - '0');
		i++; //Move to next character in the string
	}
	return (num * isneg); // We return digit if are positive or negative becuase is num multiply isneg=1
}

 // CHECK IF "INVALID CHARACTER"
 // TOO BIG NUMBER OR TOO SMALL NUMBERS
 // REPEATED NUMBERS
void	stack_init(t_stack_node **a, char **argv, bool flag_argc_2) //This function is used ti initailize a stack with number passed as strings
{
	long	nbr;  //VARIABLES - STORES THE NUMBER AFTER CONVERTING FROM STRING
	int		i;

	i = 0;
	while (argv[i]) // START LOOPING OVER EACH STRING IN ARGV
	{
		if (error_syntax(argv[i])) //NO VALID NUMBER, WE STOP AND CLEAN UP MEMORY
			error_free(a, argv, flag_argc_2);
		nbr = ft_atol(argv[i]); // TURN STRING INTO A LONG NUMBER
		if (nbr > INT_MAX || nbr < INT_MIN) // WE CHECK IF NUMBER IS IN INT RANGE
			error_free(a, argv, flag_argc_2);
		if (error_repetition(*a, (int)nbr)) // WE CHECK FOR DUPLICATE NUMBERS
			error_free(a, argv, flag_argc_2); //ADD NUMBER "INTEGER" TO THE STACK
		append_node(a, (int)nbr);
		++i; // MOVE TO NEXT STRING
	}
	if (flag_argc_2) //FREE MEMORY IF NEEDED
		free_matrix(argv);
}
