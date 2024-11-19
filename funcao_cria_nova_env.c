#include "minishell.h"

int	first_equal(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_env	*my_lstlast(t_env *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	my_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*aux;

	if (lst)
	{
		if (!(*lst))
			*lst = new;
		else
		{
			aux = my_lstlast(*lst);
			aux->next = new;
		}
	}
}

// void	my_lstadd_front(t_env **lst, t_env *new)
// {
// 	if (lst)
// 	{
// 		if (*lst && new)
// 		{
// 			new->next = *lst;
// 			*lst = new;
// 		}
// 		else if (new)
// 			*lst = new;
// 	}
// }

t_env	*my_lstnew(char *first_str, char *second_str)
{
	t_env	*list;

	list = (t_env *) malloc(sizeof(t_env));
	if (!list)
		return (NULL);

    list->key = first_str;
    list->str = second_str;
	list->next = NULL;
	return (list);
}

void free_env(t_env *list)
{
    t_env *temp;
    
    while (list)
    {
        temp = list;
        list = list->next;
        free(temp->key);
        free(temp->str);
        free(temp);
    }
}

t_env *new_env_lst(char **ev, t_env *env_list)
{
    int i;
    int equal_index;
    char *key;
    char *str;
    t_env *new;

    i = -1;
    while (ev[++i])
    {
        equal_index = first_equal(ev[i]);
        key = ft_substr(ev[i], 0, equal_index);
        if (!key)
            return (NULL);
        str = ft_substr(ev[i], equal_index + 1, strlen(ev[i]) - equal_index - 1);
        if (!str)
        {
            free (key);
            return (NULL);
        }
        new = my_lstnew(key, str);
        my_lstadd_back(&env_list, new);
    }
    return (env_list);
}

int main(int ac, char **av, char **ev)
{
	int i = -1;
    t_env *tmp;
	t_env *env_list;
    env_list = NULL;

    env_list = new_env_lst(ev, env_list);

    tmp = env_list;
    while (ev[++i])
        printf("String do env: %s\n\n", ev[i]);
    printf("----------------------------------------\n");
    while (tmp)
    {
        printf("Str da struct: %s\n", tmp->key);
        printf("Frase da struct: %s\n\n", tmp->str);
        tmp = tmp->next;
    }

    free_env(env_list);
	return (0);
}
