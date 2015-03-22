/*
** exec.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Tue Jan 20 18:13:04 2015 arnaud boulay
** Last update Wed Mar 11 18:55:09 2015 Boulay Arnaud
*/

#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "my.h"

char		**add_color(char **tab)
{
  int		i;
  char		**new_tab;

  i = -1;
  while (tab[++i] != NULL)
    ;
  if ((new_tab = malloc(sizeof(char *) * (i + 2))) == NULL)
    return (NULL);
  i = -1;
  while (tab[++i] != NULL)
    {
      if ((new_tab[i] = malloc(sizeof(char) * (my_strlen(tab[i]) + 1))) == NULL)
	return (NULL);
      new_tab[i] = my_strcpy(new_tab[i], tab[i]);
    }
  if ((new_tab[i] = malloc(sizeof(char) * (my_strlen("--color=auto") + 1)))
      == NULL)
    return (NULL);
  new_tab[i] = my_strcpy(new_tab[i], "--color=auto");
  new_tab[++i] = NULL;
  free_tab(tab);
  return (new_tab);
}

int		exec_son(char **tab, char **env, char *name)
{
  int		status;
  pid_t		fid;

  if (access(name, F_OK) == -1)
    return (0);
  if ((fid = fork()) == -1)
    {
      my_putstr("Error: Fork failed in exec_son.\n");
      return (-1);
    }
  if (fid == 0)
    {
      if (is_inside(tab[0], "ls") == 1)
	if ((tab = add_color(tab)) == NULL)
	  {
	    my_putstr("Error: Malloc failed in add_color.\n");
	    return (-1);
	  }
      execve(name, tab, env);
    }
  if (wait(&status) == -1)
    return (-1);
  if (status == 139)
    my_putstr("Segmentation Fault.\n");
  return (1);
}

int		exec_core(char **tab, char **path, char **env, char *name)
{
  int		i;
  int		ret;
  int		start;

  start = 1;
  i = -1;
  while (start != -1 && path[++i] != NULL)
    {
      if (start == 0 || name == NULL)
	if ((name = my_strcatdup(path[i], tab[0], 2, '/')) == NULL)
	  return (-1);
      start = 0;
      ret = exec_son(tab, env, name);
      if (ret == -1)
	return (-1);
      else if (ret == 1)
	start = -1;
      free(name);
    }
  if (start != -1)
    {
      my_putstr(tab[0]);
      my_putstr(": command not found.\n");
    }
  return (0);
}

int		exec_program(char **tab, char **path, t_env *env_list)
{
  char		*name;
  char		**env;

  env = NULL;
  name = NULL;
  if (tab == NULL || tab[0] == NULL)
    return (0);
  if ((env = my_listtotab(env, env_list)) == NULL)
    return (-1);
  if (is_inside(tab[0], "/") == 1)
    if ((name = my_strdup(tab[0])) == NULL)
      return (-1);
  if (exec_core(tab, path, env, name) == -1)
    return (-1);
  free_tab(env);
  return (0);
}
