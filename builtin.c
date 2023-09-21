#include "shell.h"
/**
 * my_exit - a func that exist the shell
 * @infor: the struct containing args used to maintain func header
 * Return: 0 if the 1st arg of info isn't "exit"
 */
int my_exit(infor_t *infor)
{
	int extchk;

	if (infor->argv[1])
	{
		extchk = err_atoi(infor->argv[1]);
		if (extchk == -1)
		{
			infor->status = 2;
			print_err(infor, "lllegal number: ");
			_eputs(infor->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infor->err_num = err_atoi(infor->argv[1]);
		return (-2);
	}
	infor->err_num = -1;
	return (-2);
}

/**
 * my_cd - a func that changes the present directory
 * @infor: struct containing args used for function headers
 * Return: 0
 */
int my_cd(infor_t *infor)
{
	char *st, *dr, buff[1024];
	int chdir_ret;

	st = getcwd(buff, 1024);
	if (!st)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infor->argv[1])
	{
		dr = get_env(infor, "HOME=");
		if (!dr)
			chdir_ret = chdir((dr = get_env(infor, "PWD=")) ? dr : "/");
		else
			chdir_ret = chdir(dr);
	}
	else if (str_cmp(infor->argv[1], "-") == 0)
	{
		if (!get_env(infor, "OLDPWD="))
		{
			_puts(st);
			_putchar('\n');
			return (1);
		}
		_puts(get_env(infor, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((dr = get_env(infor, "OLDPWD=")) ? dr : "/");
	}
	else
		chdir_ret = chdir(infor->argv[1]);
	if (chdir_ret == -1)
	{
		print_err(infor, "cat't cd to ");
		_eputs(infor->argv[1]);
		_eputchar('\n');
	}
	else
	{
		set_env(infor, "OLDPWD", get_env(infor, "PWD="));
		set_env(infor, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * my_help - a func that changes the present directory of the process
 * @infor: struct containing args used to maintain const function header
 * Return: 0 (success)
 */
int my_help(infor_t *infor)
{
	char **arg_arr;

	arg_arr = infor->argv;
	_puts("help call works. Function not yet implemented\n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
