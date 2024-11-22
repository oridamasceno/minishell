#include "../../include/minishell.h"

// funções auxiliares
static int	cd_with_params(t_token *token);
static int	cd_without_params(t_token *token);

/**
 * @brief implementa o comando `cd` (change directory) para o minishell.
 * @param token estrutura contendo o comando e seus argumentos.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
int	my_cd(t_token *token)
{
	int	status;

	// verifica se há argumentos em excesso
	if (token->next && token->next->next && token->next->next->type != COMMAND)
	{
		ft_putstr_fd("error: cd: too many arguments\n", token->fd_out);
		return (1);
	}

	// decide o comportamento baseado na presença de parâmetros
	if (token->next && token->next->type == COMMAND)
		status = cd_with_params(token);
	else
		status = cd_without_params(token);

	return (status);
}

/**
 * @brief altera o diretório atual para o especificado nos parâmetros.
 * @param token estrutura contendo o comando e o diretório de destino.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
static int	cd_with_params(t_token *token)
{
	char	*pwd;

	// valida os argumentos do comando
	if (validate_arguments(token))
	{
		ft_putstr_fd("error: cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}

	// obtém o diretório atual
	pwd = getcwd(NULL, 0);

	// tenta mudar para o diretório especificado
	if (chdir(token->next->content) == -1)
	{
		ft_putstr_fd("error: cd: no such file or directory: ", STDERR_FILENO);
		ft_putstr_fd(token->next->content, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		free(pwd);
		return (1);
	}

	// atualiza a variável de ambiente OLDPWD
	if (update_env(token->env_lst, "OLDPWD=", pwd) != 0)
	{
		free(pwd);
		return (1);
	}
	free(pwd);

	// atualiza a variável de ambiente PWD
	pwd = getcwd(NULL, 0);
	if (update_env(token->env_lst, "PWD=", pwd) != 0)
	{
		free(pwd);
		return (1);
	}
	free(pwd);

	return (0);
}

/**
 * @brief altera o diretório atual para o valor da variável HOME.
 * @param token estrutura contendo o comando e a lista de variáveis de ambiente.
 * @return 0 em caso de sucesso, 1 em caso de erro.
 */
static int	cd_without_params(t_token *token)
{
	char	*pwd;
	char	*home;

	// obtém o diretório atual
	pwd = getcwd(NULL, 0);

	// busca o valor da variável HOME
	home = find_env_in_lst(token->env_lst, "HOME");
	if (!home)
	{
		ft_putstr_fd("error: cd: HOME not set\n", token->fd_out);
		free(pwd);
		return (1);
	}

	// tenta mudar para o diretório HOME
	if (chdir(home) == -1)
	{
		ft_putstr_fd("error: cd: no such file or directory: ", token->fd_out);
		ft_putstr_fd(home, token->fd_out);
		ft_putstr_fd("\n", token->fd_out);
		free(pwd);
		return (1);
	}

	// atualiza a variável de ambiente OLDPWD
	if (update_env(token->env_lst, "OLDPWD=", pwd) != 0)
	{
		free(pwd);
		return (1);
	}
	free(pwd);

	// atualiza a variável de ambiente PWD
	pwd = getcwd(NULL, 0);
	if (update_env(token->env_lst, "PWD=", pwd) != 0)
	{
		free(pwd);
		return (1);
	}
	free(pwd);

	return (0);
}