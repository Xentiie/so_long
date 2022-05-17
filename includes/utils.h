#ifndef UTILS_H
# define UTILS_H

# include "ttypes.h"
# include <stdlib.h>

char	    *read_all_file(int fd, int read_size);
t_vector2	map_to_screen(t_vector2 pos);
t_vector2	screen_to_map(t_vector2 pos);
void		*mmalloc(size_t size);

#endif