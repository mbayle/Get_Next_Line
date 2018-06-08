#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>
# include <libft.h>

# define BUFF_SIZE 8

int		get_next_line(int fd, char **line);

#endif
