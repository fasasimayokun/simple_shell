#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_STRTOK 0
#define USE_GETLINE 0

#define HIST_MAX 4096
#define HIST_FILE ".simple_shell_history"

extern char **environ;

/**
 * struct liststr - the structure for singly linked list
 * @num: the numerical field
 * @str: the string field
 * @next: pointer to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - the structure containing pseudo-args to pass
 * to the func allowing uniform prototype for func pointer
 * @arg: a str generated from getline
 * @argv: the arr of strs generated from the arg
 * @path: a file path of the present command
 * @argc: the argument number
 * @line_count: the err count
 * @err_num: the err code for the exit functions
 * @linecount_flag: line input counts
 * @fname: the prog filename
 * @env: linked list copy of the environ
 * @environ: the custom updated copy of environ from the LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: environ changes
 * @status: the status of the last executed command returned
 * @cmd_buf: address of pointer to command buffer
 * @cmd_buf_type: the command type or, and :
 * @readfd: the fd to get the line input from
 * @histcount: the total count of the history line number
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;
	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} infor_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 * struct builtin - a structure that cotains a builtin str and realted func
 * @type: the builtin cmd flag
 * @func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(infor_t *);
} builtin_table;

int hsh(infor_t *, char **);
int find_builtin(infor_t *);
void _find_cmd(infor_t *);
void _fork_cmd(infor_t *);

int is_cmd(infor_t *, char *);
char *rep_chars(char *, int, int);
char *find_pth(infor_t *, char *, char *);

int loop_hsh(char **);

void _eputs(char *);
int _eputchar(char);
int put_fd(char ch, int fd);
int _putsfd(char *str, int fd);

int str_len(char *);
int str_cmp(char *, char *);
char *begins_with(const char *, const char *);
char *str_cat(char *, char *);

char *str_cpy(char *, char *);
char *str_dup(const char *);
void _puts(char *);
int _putchar(char);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *str_chr(char *, char);

char **strtowd(char *, char *);
char **strtowd_2(char *, char);

char *mem_set(char *, char, unsigned int);
void ffrree(char **);
void *re_alloc(void *, unsigned int, unsigned int);

int bffree(void **);

int interactive_mod(infor_t *);
int is_delim(char, char *);
int is_alpha(int);
int _atoi(char *);

int err_atoi(char *);
void print_err(infor_t *, char *);
int print_bas(int, int);
char *convert_num(long int, int, int);
void detach_comments(char *);

int my_exit(infor_t *);
int my_cd(infor_t *);
int my_help(infor_t *);

int my_history(infor_t *);
int my_alias(infor_t *);

ssize_t get_num(infor_t *);
int get_line(infor_t *, char **, size_t *);
void signint_handler(int);

void clr_infor(infor_t *);
void set_infor(infor_t *, char **);
void free_infor(infor_t *, int);

char *get_env(infor_t *, const char *);
int my_env(infor_t *);
int _mysetenv(infor_t *);
int _myunsetenv(infor_t *);
int populate_env_arr(infor_t *);

char **get_environ(infor_t *);
int _unsetenv(infor_t *, char *);
int set_env(infor_t *, char *, char *);

char *get_hist_file(infor_t *infor);
int write_hist(infor_t *infor);
int read_hist(infor_t *infor);
int build_hist_arr(infor_t *infor, char *, int);
int renumber_hist(infor_t *infor);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_arr_str(const list_t *);
int delete_node_at_pos(list_t **, unsigned int);
void free_arr(list_t **);

size_t arr_len(const list_t *);
char **arr_to_strings(list_t *);
size_t print_arr(const list_t *);
list_t *node_begins_with(list_t *, char *, char);
ssize_t get_node_pos(list_t *, list_t *);

int is_chain(infor_t *, char *, size_t *);
void check_chain(infor_t *, char *, size_t *, size_t, size_t);
int update_vars(infor_t *);
int update_string(char **, char *);
int update_alias(infor_t *);

#endif
