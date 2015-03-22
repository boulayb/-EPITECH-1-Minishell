/*
** env_builtin.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Sat Jan 31 18:25:00 2015 arnaud boulay
** Last update Sun Feb 22 17:37:26 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include <stdio.h>
#include "my.h"

char		**keep_program(char **tab, int options)
{
  char		**new_tab;
  int		i;
  int		j;

  i = -1;
  j = -1;
  while (tab[++i] != NULL)
    ;
  if ((new_tab = malloc(sizeof(char *) * (i - options + 1))) == NULL)
    return (NULL);
  i = options - 1;
  while (tab[++i] != NULL)
    {
      if ((new_tab[++j] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1)))
	  == NULL)
	return (NULL);
      new_tab[j] = my_strcpy(new_tab[j], tab[i]);
    }
  new_tab[++j] = NULL;
  return (new_tab);
}

int		exec_fake_env(char **tab, char **path, t_env *tmp_env, int options)
{
  char		**new_tab;

  if ((new_tab = keep_program(tab, options)) == NULL)
    {
      my_putstr("Error: Malloc failed in keep_program.\n");
      return (-1);
    }
  if (exec_program(new_tab, path, tmp_env) == -1)
    return (-1);
  free_tab(new_tab);
  return (0);
}

int		unset_option(char **tab, t_env *tmp_env, int *exec, int *options)
{
  if (tab[2] == NULL)
    {
      my_putstr("Error: env: -u require at least one argument.\n");
      return (-1);
    }
  remove_env(tmp_env, tab[2]);
  if (tab[3] != NULL)
    {
      *exec = 1;
      *options += 2;
    }
  return (0);
}

int		find_options(char **tab, t_env *tmp_env, int *exec, int *options)
{
  if (my_strcmp(tab[1], "-i") == 1 ||
      my_strcmp(tab[1], "--ignore-environment") == 1)
    {
      empty_list(tmp_env);
      *exec = 1;
      ++*options;
    }
  else if (is_inside(tab[1], "=") == 1)
    {
      if (add_chain(tmp_env, tab[1]) == -1)
	return (-1);
      else if (tab[2] != NULL)
	{
	  *exec = 1;
	  ++*options;
	}
    }
  else if (my_strcmp(tab[1], "-u") == 1 || my_strcmp(tab[1], "--unset") == 1)
    {
      if (unset_option(tab, tmp_env, exec, options) == -1)
	return (0);
    }
  else
    *exec = 1;
  return (0);
}
