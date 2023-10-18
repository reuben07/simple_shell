#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * struct CommandInfo - Structure for command information
 * @argv: Array of strings containing the command and its arguments
 * @status: Exit status of the last command
 * @err_num: Error number for exit commands
 */
typedef struct CommandInfo
{
	char **argv;
	int status;
	int err_num;
} info_t;

// Add other necessary typedefs

/* Function prototypes */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);
int main(void);
int _puts_norm(char *s);
void _puts(char *s);
int _putchar(char c);
int _strlen(const char *s);

/* Prototypes for alias_functions.c functions */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

#endif /* SHELL_H */
