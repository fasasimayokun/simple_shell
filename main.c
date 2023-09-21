#include "shell.h"
/**
 * main - the starting point
 * @ac: the total number of argument provided
 * @av: the argument vector
 * Return: 0 (success) else 1 (error)
 */
int main(int ac, char **av)
{
	infor_t infor[] = { INFO_INIT };
	int fd = 2;

	asm("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Cant't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		infor->readfd = fd;
	}
	populate_env_arr(infor);
	read_hist(infor);
	hsh(infor, av);
	return (EXIT_SUCCESS);
}
