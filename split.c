/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achahour <achahour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 18:59:48 by achahour          #+#    #+#             */
/*   Updated: 2025/05/16 19:29:09 by achahour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stddef.h>

static	int	count_words(char *str, char separator)
{
	int		count; //Numbers of word we will count
	bool	inside_word; //logical variable (True/False) that help us know if we are currently inside a word.

	count = 0; //Start counting words "Initialize word counter"
	while (*str) //starting the Loop
	{
		inside_word = false; // when we have separtor retunr the false
		while (*str == separator && *str)
			++str; //Post increment{after the use}, "str++"==>Pre-increment{before the use}
		// The loop passed all separator like space in the first or betwwen the word
		while (*str != separator && *str) // The loop enter in the word, we analyse if not are in separator in the end of string so we are in right word.
		{
			if (!inside_word) //check we are inside word
			{
				++count; //The number of words increases when we discover the beginning of a new word
				inside_word = true; // this line prevents us from counting the same word twice 
			}
			++str; //Post increment "return the original value"
		}
	}
	return (count);
}

static	char	*get_next_word(char *str, char separator)
{
	static int	cursor = 0; //THE CURSOR IS A POINTER INSIDE THE STRING "STR" {VARIABLE}, IT REMEMBER WHERE WE STOPPED
	char		*next_str; //STORE NEW WORD
	int			len; // CALCULATE WORD LENGTH
	int			i; // COPY COUNTER

	len = 0;
	i = 0;
	while (str[cursor] == separator) //SKIP THE SEPARATOR, UNTIL WE REACH  THE FIRST LETRER OF THE WORLD
		++cursor ;
	while ((str[cursor + len] != separator) && str[cursor + len]) // CALCULATE LENGTH OF WORD FROM CURSOR, AS LONG AS WE DO NOT REACH A SEPARATOR OR THE END OF THE STRING
		++len;
	next_str = malloc((size_t)len * sizeof(char) + 1);  //WE RESERVE A SPACE MEMORY
	if (NULL == next_str)  //ENSURE THE RESERVATION IS SUCCESSFUL
		return (NULL);
	while ((str[cursor] != separator) && str[cursor]) //WE COPY CHARACTER BT CHARACTER FROM STR TO NEXT STR, UNTIL WE REACH THE SEPARATOR OR THE END OF STRING
		next_str[i++] = str[cursor++];
	next_str[i] = '\0'; //WE CLOSE THE STRING WITH A \0
	return (next_str); // RETURN TO WORD THAT WAS COPY
}

char	**ft_split(char *str, char separator)
{
	int		words_number;  //HOW MANY WORD WORDS EXITS
	char	**vector_strings; //POINT TO THE RESULTING ARRAY OF STRINGS
	int		i;

	i = 0; // INITIALIZE
	words_number = count_words(str, separator); 
	if (!words_number) //CHECK IF THE STRING COUNTAIN ZERO WORDS OR EMPTY, OR ONLY SEPARATOR
		exit(1); //IF ITS TRUE THE PROGRAM EXITS
	vector_strings = malloc(sizeof(char *) * (size_t)(words_number +2)); //wE ALLOCATE MEMORY FOR "words_number +2" 1 for first empty, secondly for NULL TERMINATOR
	if (NULL == vector_strings)  // CHECK IF FAILED MALLOC IN POINTER VECTOR_STRING RETURN NULL
		return (NULL);
	while (words_number-- >= 0)  //Run the loop when the number is higher than 0
	{
		if (0 == i)  //CHECK IF I IS EQUAL 0, IF TRUE WHERE IN THE FIRST ITERATION OF THE LOOP
		{
			vector_strings[i] = malloc(sizeof(char)); //WE RESERVE ONE BYTE ONLY FOT THE FIRST WORD ITS EMPTY IN THE STRING
			if (NULL == vector_strings[i]) //CHECK IF FAILED TO RESERVE IN MEMORY
				return (NULL);
			vector_strings[i++][0] = '\0'; //ACCESS THE CURRENT INDEX I OF VEC_STR AND INCREASE IT, 0 OTS FORST CHARACTER IN THE STRING, SET THE FIRST CHRACTER IN THE STRING TO THE NULL TERMINATOR
			continue ; //sKIP TO THE NEXT ITERATION
		}
		vector_strings[i++] = get_next_word(str, separator); //THE FUNCTION NEXT WORD USED IT TO STORED UN CURRENT INDEX VECOTR_STRING
	}
	vector_strings[i] = NULL; // Set the last element to NUll to mark the end of the array
	return (vector_strings);
}
