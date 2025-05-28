/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swap_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahour <achahour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 11:22:25 by achahour          #+#    #+#             */
/*   Updated: 2025/05/16 19:35:03 by achahour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static	void	swap(t_stack_node **head) //Check if a stack is sorted
{
	int	len;

	len = stack_len(*head);  //check how many element in the stack
	if (NULL == *head || NULL == head || 1 == len) //if the stack is empty o only has 1 node, do nothing
		return ;
	*head = (*head)->next; //move the head to the second node B
	(*head)->prev->prev = *head; //Update A prev to point to B
	(*head)->prev->next = (*head)->next; // A now skip B to connect to next "C"
	if ((*head)->next) // C pointer back to A instead of B
		(*head)->next->prev = (*head)->prev;
	(*head)->next = (*head)->prev;  //B point to A next
	(*head)->prev = NULL;
}

void	sa(t_stack_node **a, bool checker) //swap the first 2 nodes of stack A
{
	swap(a);
	if (!checker)
		write(1, "sa\n", 3);
}

void	sb(t_stack_node **b, bool checker)  //swap the first 2 nodes of stack B
{
	swap(b);
	if (!checker)
		write(1, "sb\n", 3);
}

void	ss(t_stack_node **a, t_stack_node **b, bool checker)  //Swap both of stack A & B in the same time
{
	swap(a);
	swap(b);
	if (!checker)
		write(1, "ss\n", 3);
}
