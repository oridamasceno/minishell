#include "../../include/minishell.h"

/**
 * @brief implementa o comando `env` para o minishell.
 * 
 * - imprime as variáveis de ambiente atuais.
 * - cada variável é exibida no formato: `chave=valor`.
 * 
 * @param token estrutura contendo o comando e a lista de variáveis de ambiente.
 * @return 0 em caso de sucesso.
 */
int	my_env(t_token *token)
{
	t_list	*env;

	// verifica se o token é válido e obtém a lista de variáveis de ambiente
	if (token)
		env = token->env_lst;
	else
		env = NULL;

	// percorre a lista de variáveis de ambiente e imprime cada uma
	while (env)
	{
		ft_putstr_fd(env->content, token->fd_out); // imprime a variável atual
		ft_putchar_fd('\n', token->fd_out);       // adiciona uma nova linha
		env = env->next;                          // avança para a próxima variável
	}

	return (0); // retorna sucesso
}