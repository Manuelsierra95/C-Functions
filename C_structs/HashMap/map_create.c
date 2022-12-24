#include "map.h"

void	add_node_value(t_map map[], t_value *v_new)
{
	if (map->value && v_new)
	{
		v_new->next = map->value;
		map->value = v_new;
	}
}

t_value	*new_value(void *(*function)(void *arg), char *cmd_name, void *get_arg)
{
	t_value	*value;

	value = malloc(sizeof(t_value));
	if (!value)
		return (NULL);
	value->function = function;
	value->cmd_name = cmd_name;
	value->get_arg = get_arg;
	value->next = NULL;
	return (value);
}

void	m_new(t_map map[], int key, t_value *value)
{
	map[key].key = key;
	map[key].value = value;
	map[key].next = NULL;
}

