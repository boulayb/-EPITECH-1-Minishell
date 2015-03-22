/*
** cd.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Jan 28 15:23:01 2015 arnaud boulay
** Last update Sun Feb  1 18:58:19 2015 arnaud boulay
*/

#include <unistd.h>
#include <stdlib.h>
#include "my.h"

int		cd_null(char **tab, t_env *env_list)
{
  if (get_env("HOME=", env_list) != NULL)
    {
      if (chdir(get_env("HOME=", env_list) + 5) == -1)
	my_putstr("Error: cd: Wrong path.\n");
      else
	if (change_oldpwd(tab, env_list) == -1)
	  return (-1);
    }
  else
    my_putstr("Error: cd: Can't find env variable HOME.\n");
  return (0);
}

int		cd_to_home(char **tab, t_env *env_list)
{
  char		*pwd;

  if (get_env("HOME=", env_list) == NULL)
    {
      my_putstr("Error: cd: Can't find env variable HOME.\n");
      return (0);
    }
  if ((pwd = my_strcatdup(get_env("HOME=", env_list) + 5, tab[1] + 1, 2, '/'))
      == NULL)
    return (-1);
  if (chdir(pwd) == -1)
    {
      my_putstr("Error: cd: Wrong path.\n");
      return (0);
    }
  free(pwd);
  if (change_oldpwd(tab, env_list) == -1)
    return (-1);
  return (0);
}

int		cd_to_oldpath(t_env *env_list)
{
  if (chdir(get_env("OLDPWD=", env_list) + 7) == -1)
    my_putstr("Error: cd: can't find env variable OLDPWD or wrong path.\n");
  else
    {
      if (swap_pwd(env_list) == -1)
	return (-1);
      my_putstr(get_env("PWD=", env_list) + 4);
      my_putchar('\n');
    }
  return (0);
}

int		change_pwd(char **tab, char **path, t_env *env_list)
{
  int		i;

  i = -1;
  if (tab[1][0] == '/' || tab[1][0] == '~')
    {
      remove_env(env_list, "PWD=");
      if (add_chain(env_list, "PWD=") == -1)
	return (-1);
      if (tab[1][0] == '~')
	if ((path[0] = change_for_home(path[0], env_list)) == NULL)
	  return (-1);
    }
  while (path[++i] != NULL)
    if (my_strcmp("..", path[i]) == 1)
      {
	if (remove_path(env_list) == -1)
	  return (-1);
      }
    else
      if (add_path(path[i], env_list) == -1)
	return (-1);
  return (0);
}

int		change_oldpwd(char **tab, t_env *env_list)
{
  char		*oldpwd;
  char		**path;

  remove_env(env_list, "OLDPWD=");
  if ((oldpwd = my_strcatdup("OLDPWD=", get_env("PWD=", env_list) + 4, 1, ' '))
      != NULL)
    {
      if (add_chain(env_list, oldpwd) == -1)
	return (-1);
      free(oldpwd);
    }
  if (tab[1] == NULL)
    {
      if (pwd_to_home(env_list) == -1)
	return (-1);
      return (0);
    }
  path = NULL;
  if ((path = my_strtowordtab(path, tab[1], '/')) == NULL)
    return (-1);
  if (change_pwd(tab, path, env_list) == -1)
    return (-1);
  free_tab(path);
  return (0);
}
