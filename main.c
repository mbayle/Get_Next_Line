/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:29:24 by mabayle           #+#    #+#             */
/*   Updated: 2018/06/11 12:31:53 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"
#include <stdio.h>

int		main(void)
{
	char		**line;

	**line = NULL;
	get_next_line(0, line);
	printf("my line: %s\n", *line);
	return (0);
}
