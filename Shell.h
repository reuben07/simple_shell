#ifndef SHELL_H
#define SHELL_H

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_FLUSH '\0'
#define WRITE_BUF_SIZE 1024

typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

typedef struct CommandInfo_s
{
	char **argv;
	int status;
	int err_num;
	int argc;
	list_t *env;
	list_t *alias;
	list_t *history;
} CommandInfo_t;

/* Function prototypes for commands.c */
int my_help(CommandInfo_t *info);
int my_exit(CommandInfo_t *info);
int my_cd(CommandInfo_t *info);

int error_atoi(const char *str);
char *_getenv(CommandInfo_t *info, const char *name);
int _strcmp(const char *s1, const char *s2);
int _setenv(CommandInfo_t *info, const char *name, const char *value);

/* Function prototypes for alias_functions.c */
int _myhistory(CommandInfo_t *info);
int unset_alias(CommandInfo_t *info, char *str);
int set_alias(CommandInfo_t *info, char *str);
int print_alias(list_t *node);
int print_list(list_t *list);
int _myalias(CommandInfo_t *info);

/* Function prototype for delete_node_at_index */
int delete_node_at_index(list_t **head, unsigned int index);

/* Function prototypes for list manipulation */
int get_node_index(list_t *head, list_t *node);
list_t *node_starts_with(list_t *head, const char *prefix, char delimiter);
list_t *add_node_end(list_t **head, const char *str, int value);

/* Function prototypes for env_functions.c */
int print_environment(CommandInfo_t *info);
char *get_environment_variable(CommandInfo_t *info, const char *name);
int set_environment_variable(CommandInfo_t *info);
int unset_environment_variable(CommandInfo_t *info);
int populate_environment_list(CommandInfo_t *info);

void print_string_list(char **list);
char *starts_with(const char *str, const char *prefix);
void print_error(CommandInfo_t *info const char *message, ...);


/* Function prototypes for output_handling.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* Function prototypes for m_betty.c */
int main(void);
int _puts_norm(char *s);
int _puts(char *s);
int _putchar(char c);
int _strlen(const char *s);

#endif /* SHELL_H */
