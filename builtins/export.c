#include "../../include/minishell.h"

/**
 * @brief implementa o comando `export` para o minishell.
 * 
 * - adiciona ou atualiza variáveis de ambiente fornecidas como argumentos.
 * - processa cada argumento e manipula as variáveis na lista de ambiente.
 * 
 * @param token estrutura contendo o comando e a lista de variáveis de ambiente.
 * @return 0 em caso de sucesso, -1 em caso de falha na conversão de comandos.
 */
int	my_export(t_token *token)
{
	char	**commands;
	int		i;

	// converte os comandos para uma matriz de strings
	commands = convert_commands_to_array_matrix(token);
	if (!commands) // verifica se a conversão foi bem-sucedida
		return (-1);

	i = 1; // inicia no índice 1 para ignorar o próprio comando `export`
	while (commands[i])
	{
		// processa cada argumento para manipular as variáveis de ambiente
		env_assignment_handler(token, commands[i]);
		i++;
	}

	// libera a matriz de strings usada para armazenar os comandos
	free(commands[0]);
	free(commands);

	return (0);
}

/**
 * @brief lida com a atribuição de variáveis de ambiente.
 * 
 * - verifica se o argumento é uma atribuição válida (contém `=`).
 * - atualiza o valor da variável se já existir ou a adiciona à lista caso contrário.
 * - ignora entradas inválidas ou argumentos começando com `=`.
 * 
 * @param token estrutura contendo a lista de variáveis de ambiente.
 * @param arg argumento a ser processado como uma variável de ambiente.
 */
static void	env_assignment_handler(t_token *token, char *arg)
{
	char	**current;
	char	*key;

	// verifica se o argumento contém `=` mas não começa com ele
	if (arg[0] != '=' && ft_strchr(arg, '='))
	{
		// extrai a chave da variável de ambiente
		key = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);

		// verifica se a variável já existe na lista de ambiente
		current = find_env_node(token->env_lst, key);
		if (current)
		{
			// se existir, libera o valor atual e atualiza com o novo argumento
			free(*current);
			*current = arg;
		}
		else
		{
			// se não existir, adiciona como uma nova variável na lista
			ft_lstadd_back(&token->env_lst, ft_lstnew(arg));
		}

		// libera a memória usada pela chave extraída
		free(key);
	}
	else
	{
		// libera o argumento caso seja inválido (começa com `=`)
		free(arg);
	}
}