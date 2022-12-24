#include<pthread.h>
#include<stdlib.h>
#include<dirent.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

// TODO: Hacer makefile / mejorar el path o hacer otro modo de crear los archivos / mas control de errores

typedef struct s_threads
{
	int			id;
	pthread_t	*thread;
} t_threads;

char	*path;
char	*name;
char	*extension;
int		number_of_files;
int		number_of_threads;

char	*strjoin(char const *s1, char const *s2)
{
	char	*a;

	if (!s1 || !s2)
		return (NULL);
	a = malloc((strlen(s1) + strlen(s2) + 1) * sizeof(char));
	if (!a)
		return (NULL);
	memcpy(a, s1, strlen(s1));
	memcpy(a + strlen(s1), s2, strlen(s2));
	a[strlen(s1) + strlen(s2)] = '\0';
	return (a);
}

void	*create_files(void *arg)
{
	t_threads	*thread;
	int			id;
	int			files_to_create;
	int			start;
	int			end;

	thread = arg;
	id = thread->id;
	files_to_create = number_of_files / number_of_threads;
	start = files_to_create * id;
	end = start + files_to_create;

	if (id == number_of_threads - 1)
		end = number_of_files;
	
	char	file[256];

	for (int i = start; i < end; i++)
	{
		sprintf(file, "%s%s%03i.%s", path, name, i + 1, extension);
		FILE *f = fopen(file, "w");
		fclose(f);
	}

	pthread_exit(0);
}

void	threads_init(t_threads *threads)
{
	threads->thread = malloc(sizeof(pthread_t) * number_of_threads);

	for (int i = 0; i < number_of_threads; i++)
	{
		threads[i].id = i;
		pthread_create(&threads->thread[i], NULL, &create_files, (void *)&threads[i]);
	}
	for (int i = 0; i < number_of_threads; i++)
		pthread_join(threads->thread[i], NULL);
}

void	valuate_args(int argc, char **argv)
{
	if (argc < 5)
	{
		printf("Ruta / Nombre / Extension / Numero\n");
		exit(-1);
	}

	DIR *dir = opendir(argv[1]);

	if (errno == ENOENT)
	{
		printf("El directorio no existe\n");
		exit(-1);
	}
	closedir(dir);

	// path = strjoin("./", argv[1]);
	path = argv[1];
	printf("path: %s\n", path);
	name = argv[2];
	extension = argv[3];
	number_of_files = atoi(argv[4]);
	if (argc == 6)
	{
		printf("hilos: %d\n", atoi(argv[5]));
		number_of_threads = atoi(argv[5]);
	}
}

int main(int argc, char **argv)
{
	static t_threads	*threads;

	threads = malloc(sizeof(t_threads));
	valuate_args(argc, argv);
	threads_init(threads);

	free(threads);
}