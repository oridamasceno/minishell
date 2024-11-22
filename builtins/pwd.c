#include "../../include/minishell.h"

/**
 * @brief implementa o comando `pwd` para o minishell.
 * 
 * - obtém e imprime o diretório de trabalho atual.
 * - imprime uma nova linha após o diretório.
 * 
 * @param token estrutura contendo o comando e o descritor de saída.
 * @return 0 em caso de sucesso, 1 em caso de erro ao obter o diretório atual.
 */
int	my_pwd(t_token *token)
{
	char	*cwd;

	// obtém o diretório de trabalho atual usando `getcwd`
	cwd = getcwd(NULL, 0);
	if (!cwd) // verifica se ocorreu um erro ao obter o diretório
		return (1);

	// imprime o diretório atual no descritor de saída
	ft_putstr_fd(cwd, token->fd_out);

	// imprime uma nova linha após o diretório
	ft_putchar_fd('\n', token->fd_out);

	// libera a memória alocada para armazenar o diretório
	free(cwd);

	return (0); // retorna sucesso
}