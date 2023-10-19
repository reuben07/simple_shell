#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

#define BUF_FLUSH -1
#define BUFFER_FLUSH '\0'
#define WRITE_BUFFER_SIZE 1024

/* Structures */
typedef struct list_s
{
    char *str;
    int num;
    struct list_s *next;
} list_t;

typedef struct info_struct
{
    char *path;
    char *line;
    char **arg;
    int argc;
    int linecount_flag;
    int status;
    int err_num;
    int read_file_descriptor;
    int line_count;
    char *history_file;
    list_t *history;
    list_t *environment;
    list_t *alias;
    char **environment_variables;
    char *argument;
    char **arguments;
    char *executable_path;
    char **command_buffer;
    char *filename;
} info_t;

typedef struct shell_info_s
{
    char *argument;
    char **arguments;
    char *executable_path;
    int argument_count;
    char *filename;
    char *command_buffer;
    char *environment_variables;
} shell_info_t;

/* Prototypes */
char *custom_copy(char *dst, char *src, int max_chars);
char *custom_concat(char *dst, char *src, int max_bytes);
char *custom_char_search(char *str, char target_char);

int release_memory(void **memory_ptr);
void *reallocate_memory(void *old_ptr, size_t old_size, size_t new_size);
char *fill_memory_block(char *block, char value, size_t size);
void free_string_array(char **str_array);

char *string_copy(char *dest_str, char *src_str);
char *duplicate_string(const char *str);
void print_string(char *str);
int write_character(char c);

int str_len(char *str);
int str_cmp(char *str1, char *str2);
char *needle_starts(const char *haystack, const char *needle);
char *concatenate_strings(char *destination, char *source);

char **custom_tokenizer(char *input_str, char *custom_delimiter);
char **char_delim_tokenizer(char *input_str, char delimiter);

int shell_loop(info_t *param_info, char **arg_vector);
int find_builtin_command(info_t *param_info);
void find_command_in_path(info_t *param_info);
void fork_exec_command(info_t *param_info);
int is_executable_command(info_t *info_struct, char *file_path);
char *copy_characters(char *input_string, int start_index, int end_index);
char *find_command_path(info_t *info_struct, char *path_string, char *command);

void clear_shell_info(shell_info_t *shell_info);
void set_shell_info(shell_info_t *shell_info, char **argument_vector);
void free_shell_info(shell_info_t *shell_info, int free_all);

int check_interactive_mode(info_t *info);
int is_character_delimiter(char c, char *delimiters);
int is_character_alphabetic(int c);
int convert_string_to_integer(char *s);

ssize_t read_textfile(const char *filename, size_t letters);
int save_history_to_file(info_t *param_info);

char **copy_env_strings(info_t *param_info);
list_t *add_node_end(list_t **head, const char *str, int num);
void free_list(list_t **head);

void initialize_info(info_t *param_info, char **arg_vector);
void clear_info(info_t *param_info);
int interactive_mode(info_t *param_info);
ssize_t get_line_input(info_t *param_info);
int print_error(info_t *param_info, char *message);

int _shellexit(info_t *param_info);
int _listenv(info_t *param_info);
int _seehelp(info_t *param_info);
int _allhistory(info_t *param_info);
int _setenvironment(info_t *param_info);
int _unsetenvironment(info_t *param_info);
int _changedir(info_t *param_info);
int _myalias(info_t *param_info);

char *locate_path(info_t *param_info, char *env_path, char *command);
int file_cmd(info_t *param_info, char *filename);
int execute_command(info_t *param_info);

void replace_shell_alias(info_t *param_info);
list_t *get_alias_by_name(list_t *alias_list, char *name);

char *convert_number_to_string(int number, int base, int is_negative);

void string_puts(char *str);
int write_char(char c);

char *string_conc(char *dest, const char *src);

int main(int argc, char *argv[]);

#endif /* SHELL_H */
