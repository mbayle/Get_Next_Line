/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 12:25:45 by mabayle           #+#    #+#             */
/*   Updated: 2018/06/26 20:31:37 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include "libft.h"

# define BUFF_SIZE 32
# define SEPARATOR '\n'

int		get_next_line(int fd, char **line);

#endif
