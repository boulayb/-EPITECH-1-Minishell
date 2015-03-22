/*
** list.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Jan 24 15:34:47 2015 arnaud boulay
** Last update Sun Feb  1 16:54:28 2015 arnaud boulay
*/

#include <stdlib.h>
#include "my.h"

t_env		*create_list(char **env)
{
  int		i;
  t_env		*env_list;

  i = -1;
  if ((env_list = malloc(sizeof(t_env))) == NULL)
    {
      my_putstr("Error: Malloc failed in create_list.\n");
      return (NULL);
    }
  env_list->back = env_list;
  env_list->next = env_list;
  env_list->str = NULL;
  while (env[++i] != NULL)
    if (add_chain(env_list, env[i]) == -1)
      return (NULL);
  return (env_list);
}

int		add_chain(t_env *env_list, char *str)
{
  t_env		*new_chain;

  if (str == NULL)
    {
      my_putstr("Error: add_chain: str is NULL.\n");
      return (-1);
    }
  if ((new_chain = malloc(sizeof(t_env))) == NULL)
    {
      my_putstr("Error: Malloc failed in add_chain.\n");
      return (-1);
    }
  if ((new_chain->str = my_strdup(str)) == NULL)
    return (-1);
  new_chain->back = env_list->back;
  new_chain->next = env_list;
  env_list->back->next = new_chain;
  env_list->back = new_chain;
  return (0);
}

void		rm_chain(t_env *chain)
{
  free(chain->str);
  chain->back->next = chain->next;
  chain->next->back = chain->back;
  free(chain);
}

void		rm_list(t_env *env_list)
{
  t_env		*chain;
  t_env		*tmp;

  chain = env_list->next;
  while (chain != env_list)
    {
      tmp = chain->next;
      rm_chain(chain);
      chain = tmp;
    }
  free(env_list);
}

void		empty_list(t_env *env_list)
{
  t_env		*chain;
  t_env		*tmp;

  chain = env_list->next;
  while (chain != env_list)
    {
      tmp = chain->next;
      rm_chain(chain);
      chain = tmp;
    }
}
