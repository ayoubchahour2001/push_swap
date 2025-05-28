/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahour <achahour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 17:59:22 by achahour          #+#    #+#             */
/*   Updated: 2025/05/16 19:03:21 by achahour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

void	set_current_position(t_stack_node *stack) //Set the current position of every node 
{
	int		i;
	int		centerline; //Will store the middle index of the stack

	i = 0; //position Index (starting from 0)
	if (NULL == stack) //If stack is empty, exit the function. no do nothing
		return ; //we using return (with nothing), because we not have aNy data to return 
	centerline = stack_len(stack) / 2; //We divide total number of nodes to 2 (stack_len), to find the middle index
	while (stack) //starting the loop iterates over each nodes
	{
		stack->current_position = i; //store the position index of the current node
		if (i <= centerline) // if node is in the first half set True (closer to the top)
			stack->above_median = true;
		else
			stack->above_median = false; // if node is in the first half set False (closer to the bottom)
		stack = stack->next; //Move to the next node in the stack
		++i; //increase the position index
	}
}

/*
	Each node in stack b, this function set TARGET_NODE which the best place in stack A to insert that value
	The smallest bigger value
	If no node bigger, best_match_index is the smallest node
	Every node in B gets its target node in A 
 */
static	void	set_target_node(t_stack_node *a, t_stack_node *b)
{
	t_stack_node	*current_a;
	t_stack_node	*target_node;
	long			best_match_index;

	while (b) //for each node in stack B, we try to find the smallest bigger value in stack A
	{
		best_match_index = LONG_MAX; //we used to track the best candidate in stack A
		current_a = a;
		while (current_a) //we used to track the best candidate in stack A
		{
			if (current_a->value > b->value
				&& current_a->value < best_match_index) //WE CHECK IF CURRENT STACK A BIGGER THE VALUE
			{
				best_match_index = current_a->value;
				target_node = current_a;
			}
			current_a = current_a->next;
		}
		if (LONG_MAX == best_match_index)
			b->target_node = find_smallest(a);  //If there is no bigger number in A, we insert b->value at the smallest value in a
		else
			b->target_node = target_node; //assign th e best target node we found in A
		b = b->next; //move to th next node in stack B
	}
}

/* 
	*Set the prices to push the node
	*from b -> a
	*The price checks for the relative positions in the stack
	*for every node, setting the respective price
*/
void	set_price(t_stack_node *a, t_stack_node *b)
{
	int	len_a;
	int	len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (b)
	{
		b->push_price = b->current_position;
		if (!(b->above_median))
			b->push_price = len_b - (b->current_position);
		if (b->target_node->above_median)
			b->push_price += b->target_node->current_position;
		else
			b->push_price += len_a - (b->target_node->current_position);
		b = b->next;
	}
}

/* 
	*Flag the cheapest node in the current
	*Stacks configurations
*/

void	set_cheapest(t_stack_node *b) //The function marks the node in stack b that is the cheapest to push to stack A
{
	long			best_match_value; //store the lowest push_price founds so far
	t_stack_node	*best_match_node; //pointer to the node

	if (NULL == b) //if the list is empty, just exit
		return ;
	best_match_value = LONG_MAX; //starting the assuming the worst possible price
	while (b) //check every node in the stack b
	{
		if (b->push_price < best_match_value) //if the push price less than the current best match value, we save:
		{
			best_match_value = b->push_price; //save that price into value
			best_match_node = b;  //save that node into node
		}
		b = b->next; //moves the pointer b to the next node
	}
	best_match_node->cheapest = true;  //Mark that node true and which the one push next
}

/* All the necessary value to make the push */
void	init_nodes(t_stack_node *a, t_stack_node *b)
{
	set_current_position(a);
	set_current_position(b);
	set_target_node(a, b);
	set_price(a, b);
	set_cheapest(b);
}
