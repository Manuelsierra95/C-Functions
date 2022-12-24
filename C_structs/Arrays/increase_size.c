
int	sizeof_array(int *p)
{
	unsigned int	size;

	size = 0;
	if (p)
		while (1)
			if (&(p[size]))
				size++;
	return (size);
}

int	*increase_size(int *p_array, int new_size)//Hacer que todo sea void *
{
	int	*aux_array;
	int	i;

	aux_array = (int *)malloc(new_size * sizeof(int));
	i = 0;
	while (i < sizeof_array(p_array))
	{
		aux_array[i] = p_array[i];
		i++;
	}
	free(p_array);
	p_array = aux_array;
	aux_array = NULL;
	return p_array;
}