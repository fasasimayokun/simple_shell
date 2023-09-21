#include "shell.h"
/**
 * hsh - a func of the main shell loop
 * @infor: the param and return info structurew
 * @av: the arg vector
 * Return: 0 (suceess) else 1
 */
int hsh(infor_t *infor, char **av)
{
	ssize_t rd = 0;
	int builtin_rt = 0;

	while (rd != -1 && builtin_rt != -2)
	{
		clr_infor(infor);
		if (interactive_mod(infor))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		rd = get_num(infor);
		if (rd != -1)
		{
			set_infor(infor, av);
			builtin_rt = find_builtin(infor);
			if (builtin_rt == -1)
				_find_cmd(infor);
		}
		else if (interactive_mod(infor))
			_putchar('\n');
		free_infor(infor, 0);
	}
	write_hist(infor);
	free_infor(infor, 1);
	if (!interactive_mod(infor) && infor->status)
		exit(infor->status);
	if (builtin_rt == -2)
	{
		if (infor->err_num == -1)
			exit(infor->status);
		exit(infor->err_num);
	}
	return (builtin_rt);
}
/**
 * find_builtin - a func that finds the builtin cmd
 * @infor: the parm and return info structure
 * Return: 0 (success) else -1 (unsuccessful) else
 * 2 (builtin signals exit) else 1 (not found)
 */
int find_builtin(infor_t *infor)
{
	int nm, built_in_rt = -1;
	builtin_table builtintab[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (nm = 0; builtintab[nm].type; nm++)
	{
		if (str_cmp(infor->argv[0], builtintab[nm].type) == 0)
		{
			infor->line_count++;
			built_in_rt = builtintab[nm].func(infor);
			break;
		}
	}
	return (built_in_rt);
}

/**
 * _find_cmd - a func that finds the command in path
 * @infor: the param and return info struct
 * Return: void(nothing)
 */
void _find_cmd(infor_t *infor)
{
	char *pth = NULL;
	int nm, k;

	infor->path = infor->argv[0];
	if (infor->linecount_flag == 1)
	{
		infor->line_count++;
		infor->linecount_flag = 0;
	}
	for (nm = 0, k = 0; infor->arg[nm]; nm++)
		if (!is_delim(infor->arg[nm], " \t\n"))
			k++;
	if (!k)
		return;

	pth = find_pth(infor, get_env(infor, "PATH="), infor->argv[0]);
	if (pth)
	{
		infor->path = pth;
		_fork_cmd(infor);
	}
	else
	{
		if ((interactive_mod(infor) || get_env(infor, "PATH=")
					|| infor->argv[0][0] == '/')
				&& is_cmd(infor, infor->argv[0]))
			_fork_cmd(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			print_err(infor, "not found\n");
		}
	}
}

/**
 * _fork_cmd - a func that forks an execution thread to run command
 * @infor: the param and return info struct
 * Return: void(nothing)
 */
void _fork_cmd(infor_t *infor)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error.");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_infor(infor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infor->status));
		if (WIFEXITED(infor->status))
		{
			infor->status = WEXITSTATUS(infor->status);
			if (infor->status == 126)
				print_err(infor, "Permission denied\n");
		}
	}
}
