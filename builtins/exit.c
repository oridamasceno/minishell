#include "../../include/minishell.h"

/**
 * @brief implementa o comando `exit` para o minishell.
 * 
 * - chama a função `exit_error_hanlder` para verificar e tratar os erros relacionados ao comando `exit`.
 * - limpa a lista de variáveis de ambiente, a lista de tokens e o histórico do readline.
 * - termina o programa com o status de saída determinado.
 * 
 * @param token ponteiro para a lista de tokens.
 * @param env_lst ponteiro para a lista de variáveis de ambiente.
 */
void	my_exit(t_token **token, t_list **env_lst)
{
	unsigned char	status;

	// trata erros relacionados ao comando `exit` e obtém o status de saída
	status = exit_error_hanlder(token);

	// limpa a lista de variáveis de ambiente e os tokens
	ft_lstclear(env_lst, free);
	clear_token_lst(token, 0);

	// limpa o histórico do readline
	rl_clear_history();

	// termina o programa com o status de saída
	exit(status);
	return ;
}

/**
 * @brief implementa o comando `exit` para o minishell quando em um pipe.
 * 
 * - chama a função `exit_error_hanlder` para verificar e tratar os erros relacionados ao comando `exit`.
 * - limpa a lista de variáveis de ambiente e a lista de tokens.
 * - não encerra o programa, apenas retorna o status de saída.
 * 
 * @param token ponteiro para a lista de tokens.
 * @param env_lst ponteiro para a lista de variáveis de ambiente.
 * @return status de saída.
 */
int	my_exit_pipe(t_token **token, t_list **env_lst)
{
	int	status;

	// trata erros relacionados ao comando `exit` e obtém o status de saída
	status = exit_error_hanlder(token);

	// limpa a lista de variáveis de ambiente e os tokens
	ft_lstclear(env_lst, free);
	clear_token_lst(token, 0);

	// não encerra o programa, apenas retorna o status de saída
	return (status);
}

/**
 * @brief trata erros relacionados ao comando `exit`.
 * 
 * - verifica se o número de argumentos é válido.
 * - se houver um argumento, verifica se é um número válido.
 * - se for um número válido, retorna o valor convertido.
 * - caso contrário, exibe mensagens de erro apropriadas.
 * 
 * @param token_lst ponteiro para a lista de tokens.
 * @return o status de saída, que pode ser um código numérico ou 255 em caso de erro.
 */
static int	exit_error_hanlder(t_token **token_lst)
{
	t_token	*token;

	// verifica se a lista de tokens está vazia
	if (!token_lst || !*token_lst)
		return (0); // se estiver vazia, retorna 0

	token = *token_lst;

	// verifica se o número de argumentos é válido
	if (validate_arguments(token))
	{
		// exibe mensagem de erro se houver argumentos demais
		ft_putstr_fd("error: too many arguments\n", STDERR_FILENO);
		return (1); // retorna 1 para indicar erro
	}
	else if (token->next && token->next->type == COMMAND)
	{
		// se o próximo token for um número válido, converte e retorna
		if (is_valid_numeric_string(token->next->content) == 0)
			return (ft_atoi(token->next->content));
		else
		{
			// exibe mensagem de erro se o número for inválido
			ft_putstr_fd("error: invalid number\n", STDERR_FILENO);
			return (255); // retorna 255 para erro de número inválido
		}
	}

	return (0); // se não houver erro, retorna 0
}

/**
 * @brief verifica se a string fornecida é um número válido.
 * 
 * - verifica se a string contém apenas números (com ou sem sinal).
 * 
 * @param s string a ser verificada.
 * @return 0 se a string for um número válido, 1 caso contrário.
 */
static int	is_valid_numeric_string(char *s)
{
	if (!s || *s == '-') // verifica se a string é nula ou começa com '-'
		return (2); // retorna 2 para erro de número inválido

	if (*s == '+') // ignora o sinal de mais no início da string
		s++;

	if (!*s) // verifica se a string está vazia após o sinal
		return (1); // retorna 1 para erro de número inválido

	// verifica se todos os caracteres são dígitos
	while (*s)
	{
		if (!ft_isdigit(*s))
			return (1); // retorna 1 se algum caractere não for dígito
		s++;
	}

	return (0); // retorna 0 se a string for um número válido
}