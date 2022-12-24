#ifndef MAP_H
# define MAP_H

# define NUM_OF_ELEMENTS 7

# include <unistd.h>
# include <stdlib.h>

typedef struct s_value
{
	void			*(*function)(void *arg);
	void			*(*get_arg)(void);
	char			*cmd_name;
	struct s_value	*next;
} t_value;

typedef struct s_map
{
	int				key;
	t_value			*value;
	struct s_map	*next;
} t_map;


void	add_node_value(t_map map[], t_value *v_new);
t_value	*new_value(void *(*value)(void *func_struct), char *id, void *func_struct);
void	m_new(t_map map[], int key, t_value *value);
void	put(t_map map[], char *id, void *(*value)(void *func_struct), void *func_struct);
int		get_key(char *input);
t_value	*get(t_map map[], char *input);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const	char *str);
int		ft_strncmp(const char	*s1, const char *s2, size_t n);
void	clean_map(t_map map[]);


#endif
