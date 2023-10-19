#include "Shell.h"

/**
 * check_chain_delimiter - Checks if the current character in the buffer is a chain delimiter.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 *
 * Return: 1 if it's a chain delimiter, 0 otherwise.
 */
int check_chain_delimiter(info_t *info, char *buf, size_t *p)
{
    size_t j = *p;

    if (buf[j] == '|' && buf[j + 1] == '|')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_OR;
    }
    else if (buf[j] == '&' && buf[j + 1] == '&')
    {
        buf[j] = 0;
        j++;
        info->cmd_buf_type = CMD_AND;
    }
    else if (buf[j] == ';')
    {
        buf[j] = 0;
        info->cmd_buf_type = CMD_CHAIN;
    }
    else
    {
        return 0;
    }

    *p = j;
    return 1;
}

/**
 * evaluate_chain - Checks if we should continue chaining based on the last status.
 * @info: The parameter struct.
 * @buf: The character buffer.
 * @p: Address of the current position in buf.
 * @i: Starting position in buf.
 * @len: Length of buf.
 *
 * Return: Void.
 */
void evaluate_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
    size_t j = *p;

    if (info->cmd_buf_type == CMD_AND && info->status)
    {
        buf[i] = 0;
        j = len;
    }
    
    if (info->cmd_buf_type == CMD_OR && !info->status)
    {
        buf[i] = 0;
        j = len;
    }

    *p = j;
}

/**
 * replace_aliases - Replaces aliases in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_aliases(info_t *info)
{
    int i;
    list_t *node;
    char *p;

    for (i = 0; i < 10; i++)
    {
        node = find_node_with_prefix(info->alias, info->argv[0], '=');
        if (!node)
            return 0;

        free(info->argv[0]);
        p = string_char(node->str, '=');

        if (!p)
            return 0;

        p = string_dpl(p + 1);

        if (!p)
            return 0;

        info->argv[0] = p;
    }

    return 1;
}

/**
 * replace_variables - Replaces variables in the tokenized string.
 * @info: The parameter struct.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_variables(info_t *info)
{
    int i = 0;
    list_t *node;

    for (i = 0; info->argv[i]; i++)
    {
        if (info->argv[i][0] != '$' || !info->argv[i][1])
            continue;

        if (!string_cmp(info->argv[i], "$?"))
        {
            replace_string(&(info->argv[i]),
                           string_dpl(converts_number(info->status, 10, 0)));
            continue;
        }

        if (!string_cmp(info->argv[i], "$$"))
        {
            replace_string(&(info->argv[i]),
                           string_dpl(converts_number(getpid(), 10, 0)));
            continue;
        }

        node = find_node_with_prefix(info->env, &info->argv[i][1], '=');
        if (node)
        {
            replace_string(&(info->argv[i]),
                           string_dpl(string_char(node->str, '=') + 1));
            continue;
        }

        replace_string(&info->argv[i], string_dpl(""));
    }

    return 0;
}

/**
 * replace_string - Replaces a string.
 * @old: Address of the old string.
 * @new: New string.
 *
 * Return: 1 if replaced, 0 otherwise.
 */
int replace_string(char **old, char *new)
{
    free(*old);
    *old = new;
    return 1;
}
