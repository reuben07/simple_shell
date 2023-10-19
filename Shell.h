#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct list_s - Linked list structure
 * @str: String stored in the node
 * @next: Pointer to the next node
 */
typedef struct list_s
{
	char *str;
	struct list_s *next;
} list_t;

/**
 * struct info_s - Parameter struct for maintaining function prototypes
 * @history: Linked list to store command history
 * @alias: Linked list to store aliases
 * @argc: Number of arguments
 * @argv: Array of argument strings
 * @status: Exit status
 * @err_num: Error number
 * @hist_count: History count
 * @env: Linked list to store environment variables
 */
typedef struct info_s
{
	list_t *history;
	list_t *alias;
	int argc;
	char **argv;
	int status;
	int err_num;
	int hist_count;
	list_t *env;
} info_t;

/* Function Prototypes */
int _all_history(info_t *info);
int unset_alias(info_t *info, char *alias_str);
int assign_alias(info_t *info, char *alias_str);
int show_alias(list_t *alias_node);
int _my_alias(info_t *info);

int exit_shell(info_t *info);
int _change_dir(info_t *info);
int get_help(info_t *info);

char *history_file_path(info_t *info);
int save_history(info_t *info);
int load_history(info_t *info);
int history_entry(info_t *info, char *buffer, int line_count);
int renumber_history_line(info_t *info);

int show_environment(info_t *info);
char *get_environment_variable(info_t *info, const char *variable_name);
int set_environment_variable(info_t *info);
int unset_environment_variable(info_t *info);
int populate_env(info_t *info);

void display_error_message(info_t *info, char *error_string);
int write_char_to_standard_error(char character);
int write_to_file_descriptor(char character, int file_descriptor);
int write_string_to_file_descriptor(char *string, int file_descriptor);

int string_to_integer(char *str);
void display_error_message(info_t *info, char *error_string);
int print_error_dec(int input, int fd);
char *convert_number_to_string(long int number, int base, int flags);
void remove_comments(char *buffer);

void clear_info(info_t *infos);
void set_info(info_t *infos, char **av);
void free_info(info_t *infos, int all);

ssize_t input_buffer(info_t *info, char **buf, size_t *len);
ssize_t get_line_input(info_t *info);
ssize_t read_buffer(info_t *info, char *buf, size_t *i);
int get_input_line(info_t *info, char **ptr, size_t *length);
void blockCtrlC(__attribute__((unused)) int sig_num);

list_t *add_to_start(list_t **list_head, const char *data, int index);
list_t *append_to_end(list_t **list_head, const char *data, int index);
size_t print_data_list(const list_t *head);
int remove_node_at_position(list_t **list_head, unsigned int position);
void clear_data_list(list_t **list_head_ptr);

size_t count_nodes(const list_t *h);
char **list_to_strings(list_t *head);
size_t show_list(const list_t *h);
list_t *find_node_with_prefix(list_t *node, char *prefix, char c);
ssize_t retrieve_node_index(list_t *head, list_t *node);

void *resize_memory_block(void *ptr, unsigned int old_size, unsigned int new_size);
char *fill_memory(char *s, char b, unsigned int n);
void free_string(char **pp);

int free_pointer(void **ptr);

int file_cmd(info_t *info, char *path);
char *duplicate_chars(char *pathstr, int start, int stop);
char *locate_path(info_t *info, char *pathstr, char *cmd);

int shell_loop(info_t *param_info, char **arg_vector);
int find_builtin_command(info_t *param_info);
void find_command_in_path(info_t *param_info);
void fork_exec_command(info_t *param_info);

int check_chain_delimiter(info_t *info, char *buf, size_t *p);
void evaluate_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len);
int replace_aliases(info_t *info);
int replace_variables(info_t *info);
int replace_string(char **old, char *new);

int interactive_mode(info_t *info);
int char_delim(char c, char *delim);
int custom_tokenizer(int c);
int convert_string_to_integer(char *s);

char *copy_string(char *dest, char *src, int n);
char *string_cat(char *dest, char *src, int n);
char *string_char(char *s, char c);

char **tokenize_string(char *str, char *delimiter);
char **split_string(char *str, char delimiter);

int string_len(char *s);
int string_cmp(char *s1, char *s2);
char *needle_starts(const char *haystack, const char *needle);
char *string_conc(char *dest, char *src);

char *string_cpy(char *dest, char *src);
char *string_dpl(const char *str);
void string_puts(char *str);
int write_char(char c);

#endif /* SHELL_H */
