/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabayle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/09 00:22:23 by mabayle           #+#    #+#             */
/*   Updated: 2018/06/27 02:43:30 by mabayle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
 *   Objective of the function : leaks prevention
 */
void				ft_free(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}

/*
 *   Objective of the function : check if separator is present, modify pointer position
 *
 *   Infos : - ft_strchr = function locates the first occurrence of my SEPARATOR in the string pointed to my buff
 *           - ft_strsub = malloc and return a portion of my string (*buff) // start at index[0] and stop at my first occurence
 *           - ft_memmove = function copies len bytes (ft_strlen) from string src (tmp) to string dst (buff).
 */
static int			ft_check(char **buff, char **line)
{
	char			*tmp;

	tmp = ft_strchr(*buff, SEPARATOR);
	if (tmp)
	{
		*line = ft_strsub(*buff, 0, tmp - *buff);
		ft_memmove(*buff, tmp + 1, ft_strlen(tmp));
		tmp = NULL;
		return (1);
	}
	return (0);
}

/*
 *   Objective of the function : fills and extends the buffer if it needed
 *
 *   Infos : - tmp copy buffer content
 *           - clean buffer
 *           - ft_strjoin = Allocate and return a "fresh" string ending with a '\0' resulting from the concatenation of tmp and new_buff
 *           - free tmp after use
 */
static	void		ft_add_data(char **buff, char *tmp, char *new_buff)
{
	tmp = ft_strdup(*buff);
	ft_free((void **)buff);
	*buff = ft_strjoin(tmp, new_buff);
	ft_free((void **)&tmp);
}

/*
 *   Objective of the function : special function for buffer (return value ==> -1 <error> // 0 <read ok> // 1 <read ok + "we got a line !">)
 *
 *   Infos : - new_buff = variable for buffer processing (free after use)
 *           - ret = variable used for indexing and return value
 *           - ft_add_data = fills the buffer if it is not empty
 *           - ft_strdup = function allocates sufficient memory for a copy of the string new_buff, does the copy, and returns a pointer to it
 *           - ft_check = check if we are at the end of the line // In case who ft_check return 1 ==> free new_buff and return 1
 */
static	int			ft_fill(int fd, char **buff, char **line)
{
	char			*new_buff;
	char			*tmp;
	int				ret;

	if (!(new_buff = (char *)malloc(sizeof(char) * BUFF_SIZE + 1)))
		return (-1);
	new_buff[BUFF_SIZE] = 0;
	while ((ret = read(fd, new_buff, BUFF_SIZE)))
	{
		if (ret == -1)
			return (-1);
		new_buff[ret] = '\0';
		tmp = NULL;
		if (*buff)
			ft_add_data(buff, tmp, new_buff);
		else
			*buff = ft_strdup(new_buff);
		if (ft_check(buff, line))
		{
			ft_free((void **)&new_buff);
			return (1);
		}
	}
	ft_free((void **)&new_buff);
	return (0);
}

/*
 *    Objective of the function : return 1 line read to file descriptor (return values ==> -1 <error> // 0 <read ok + end of file> // 1 <read ok + "we got a line !">)
 *
 *   Infos : - OPEN_MAX = macro of <limits.h> (max fd for a program = 256)
 *           - *fd_error = variable who serve to check error case (free after use)
 *           - ft_check = verify if SEPARATOR is present
 *           - ft_fill = special function for buffer processing
 *           - *line = store GNL result
 */
int					get_next_line(int fd, char **line)
{
	static char		*buff[OPEN_MAX];
	char			*fd_error;
	int				ret;

	if (!(fd_error = (char *)malloc(sizeof(char) * 1)))
		return (-1);
	if (!line || fd < 0 || fd > OPEN_MAX || read(fd, fd_error, 0) < 0)
	{
		ft_free((void **)&fd_error);
		if (line != NULL)
			*line = NULL;
		return (-1);
	}
	ft_free((void **)&fd_error);
	if (buff[fd] && ft_check(&buff[fd], line))
		return (1);
	if ((ret = ft_fill(fd, &buff[fd], line)) != 0)
		return (ret);
	if (buff[fd] == NULL || buff[fd][0] == '\0')
		return (0);
	*line = buff[fd];
	buff[fd] = NULL;
	return (1);
}
