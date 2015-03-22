/*
** my_listtotab.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Jan 28 13:58:49 2015 arnaud boulay
** Last update Sun Feb  1 16:56:59 2015 arnaud boulay
*/

#include <stdlib.h>
#include "my.h"

int		count_elem(t_env *env_list)
{
  int		i;
  t_env		*tmp;

  tmp = env_list->next;
  i = 0;
  while (tmp != env_list)
    {
      ++i;
      tmp = tmp->next;
    }
  return (i);
}

char		**my_listtotab(char **env, t_env *env_list)
{
  t_env		*tmp;
  int		elem;
  int		i;

  i = -1;
  tmp = env_list->next;
  elem = count_elem(env_list);
  if ((env = malloc(sizeof(char *) * (elem + 1))) == NULL)
    {
      my_putstr("Error: Malloc failed in my_listtotab.\n");
      return (NULL);
    }
  while (tmp != env_list)
    {
      if ((env[++i] = malloc(sizeof(char) * (my_strlen(tmp->str) + 1))) == NULL)
	{
	  my_putstr("Error: Malloc failed in my_listtotab.\n");
	  return (NULL);
	}
      env[i] = my_strcpy(env[i], tmp->str);
      tmp = tmp->next;
    }
  env[++i] = NULL;
  return (env);
}
