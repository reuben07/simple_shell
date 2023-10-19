#include "Shell.h"

/**
 * custom_tokenizer - Splits a string into words using a custom delimiter.
 * @input_str: The input string to be split.
 * @custom_delimiter: The custom delimiter string.
 *
 * Return: An array of strings, or NULL on failure.
 */
char **custom_tokenizer(char *input_str, char *custom_delimiter)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (input_str == NULL || input_str[0] == '\0')
		return NULL;

	if (!custom_delimiter)
		custom_delimiter = " ";

	for (i = 0; input_str[i] != '\0'; i++)
	{
		if (!is_custom_delimiter(input_str[i], custom_delimiter) && (is_custom_delimiter(input_str[i + 1], custom_delimiter) || !input_str[i + 1]))
			num_words++;
	}

	if (num_words == 0)
		return NULL;

	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (is_custom_delimiter(input_str[i], custom_delimiter))
			i++;

		k = 0;
		while (!is_custom_delimiter(input_str[i + k], custom_delimiter) && input_str[i + k])
			k++;

		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return NULL;
		}

		for (m = 0; m < k; m++)
			tokens[j][m] = input_str[i++];

		tokens[j][m] = '\0';
	}

	tokens[j] = NULL;
	return tokens;
}

/**
 * char_delim_tokenizer - Splits a string into words using a specified delimiter character.
 * @input_str: The input string to be split.
 * @delimiter: The delimiter character.
 *
 * Return: An array of strings, or NULL on failure.
 */
char **char_delim_tokenizer(char *input_str, char delimiter)
{
	int i, j, k, m, num_words = 0;
	char **tokens;

	if (input_str == NULL || input_str[0] == '\0')
		return NULL;

	for (i = 0; input_str[i] != '\0'; i++)
	{
		if ((input_str[i] != delimiter && input_str[i + 1] == delimiter) ||
			(input_str[i] != delimiter && !input_str[i + 1]) || input_str[i + 1] == delimiter)
			num_words++;
	}

	if (num_words == 0)
		return NULL;

	tokens = malloc((1 + num_words) * sizeof(char *));
	if (!tokens)
		return NULL;

	for (i = 0, j = 0; j < num_words; j++)
	{
		while (input_str[i] == delimiter && input_str[i] != delimiter)
			i++;

		k = 0;
		while (input_str[i + k] != delimiter && input_str[i + k] && input_str[i + k] != delimiter)
			k++;

		tokens[j] = malloc((k + 1) * sizeof(char));
		if (!tokens[j])
		{
			for (k = 0; k < j; k++)
				free(tokens[k]);
			free(tokens);
			return NULL;
		}

		for (m = 0; m < k; m++)
			tokens[j][m] = input_str[i++];

		tokens[j][m] = '\0';
	}

	tokens[j] = NULL;
	return tokens;
}
