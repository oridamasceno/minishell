#include "../../include/minishell.h"

/**
 * @brief implementa o comando `echo` para o minishell.
 * 
 * - imprime os argumentos fornecidos ao comando `echo`.
 * - suporta a flag `-n`, que omite a nova linha final.
 * 
 * @param token estrutura contendo o comando e seus argumentos.
 * @return 0 em caso de sucesso.
 */
int	my_echo(t_token *token)
{
	int		should_print_new_line; // flag para determinar se deve imprimir uma nova linha
	t_token	*head;                 // ponteiro para o início da lista de tokens

	head = token;                 // armazena a referência do token inicial
	should_print_new_line = 1;    // por padrão, imprime nova linha no final

	// verifica se há argumentos após o comando `echo`
	if (token->next)
	{
		// verifica se o primeiro argumento é a flag `-n` (sem nova linha)
		if (!ft_strncmp(token->next->content, "-n", 2) && ft_strlen(token->next->content) == 2)
		{
			should_print_new_line = 0; // desativa a impressão da nova linha
			token = token->next;      // avança para o próximo token
		}

		// avança para os próximos argumentos
		token = token->next;
		while (token && token->type != PIPE)
		{
			// imprime o conteúdo do token no descritor de saída
			ft_putstr_fd(token->content, head->fd_out);

			// move para o próximo token e adiciona espaço, se necessário
			token = token->next;
			if (token && token->type != PIPE)
				ft_putchar_fd(' ', head->fd_out);
		}
	}

	// imprime uma nova linha, se a flag `-n` não estiver ativa
	if (should_print_new_line)
		ft_putchar_fd('\n', head->fd_out);

	return (0);
}