#include "map.h"

int	get_key(char *input)
{
	int	i;
	int	key;

	key = 0;
	i = -1;
	while (input[++i])
		key += input[i];
	return ((key % NUM_OF_ELEMENTS) + 1);
}
void	put(t_map map[], char *cmd_name, void *(*function)(void *arg), void *get_arg)
{
	int		key;

	key = get_key(cmd_name);
	if (map[key].key == key)
		add_node_value(&map[key], new_value(function, cmd_name, get_arg));
	else
		m_new(map, key, new_value(function, cmd_name, get_arg));
}

t_value	*get(t_map map[], char *input)
{
	int		key;
	t_value	*aux;

	key = get_key(input);
	aux = map[key].value;
	if (map[key].key == key)
		while (aux)
		{
			if (!ft_strncmp(input, aux->cmd_name, ft_strlen(input)))
				return (aux);
			aux = aux->next;
		}
	return (NULL);
}

void	clean_map(t_map map[])
{
	t_value	*node;
	t_value	*aux;
	int		i;

	i = 0;
	while (++i < (NUM_OF_ELEMENTS + 1))
		if (map[i].key == i)
		{
			aux = map[i].value;
			while(aux)
			{
				node = aux;
				aux = node->next;
				free(node);
			}
		}
}
