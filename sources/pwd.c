/*
** pwd.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Thu Jan 29 18:36:26 2015 arnaud boulay
** Last update Sun Feb  1 16:55:27 2015 arnaud boulay
*/

#include <stdlib.h>
#include "my.h"

int		add_path(char *str, t_env *env_list)
{
  char		*pwd;

  if ((pwd = my_strcatdup(get_env("PWD=", env_list), str, 2, '/')) != NULL)
    {
      remove_env(env_list, "PWD=");
      if (add_chain(env_list, pwd) == -1)
	return (-1);
      free(pwd);
    }
  return (0);
}

int		remove_path(t_env *env_list)
{
  int		lenght;
  char		*pwd;

  if ((pwd = my_strdup(get_env("PWD=", env_list))) == NULL)
    return (-1);
  lenght = my_strlen(pwd);
  while (--lenght > 0)
    if (pwd[lenght] == '/')
      {
	if (lenght == 4)
	  pwd[lenght + 1] = '\0';
	else
	  pwd[lenght] = '\0';
	remove_env(env_list, "PWD=");
	if (add_chain(env_list, pwd) == -1)
	  return (-1);
	lenght = 0;
      }
  free(pwd);
  return (0);
}

char		*change_for_home(char *str, t_env *env_list)
{
  int		i;
  char		*home;
  char		*dest;

  i = -1;
  if ((home = get_env("HOME=", env_list) + 6) == NULL)
    return (NULL);
  if ((dest = malloc(sizeof(char) * (my_strlen(home) + 1))) == NULL)
    {
      my_putstr("Error: Malloc failed in change_for_home.\n");
      return (NULL);
    }
  while (home[++i] != '\0')
    dest[i] = home[i];
  dest[i] = '\0';
  free(str);
  return (dest);
}

int		pwd_to_home(t_env *env_list)
{
  char		*pwd;

  remove_env(env_list, "PWD=");
  if ((pwd = my_strcatdup("PWD=", get_env("HOME=", env_list) + 5, 1, ' '))
      == NULL)
    return (-1);
  if (add_chain(env_list, pwd) == -1)
    return (-1);
  free(pwd);
  return (0);
}

int		swap_pwd(t_env *env_list)
{
  char		*pwd;
  char		*tmp;

  if ((tmp = my_strdup(get_env("OLDPWD=", env_list) + 7)) == NULL)
    return (-1);
  remove_env(env_list, "OLDPWD=");
  pwd = my_strcatdup("OLDPWD=", get_env("PWD=", env_list) + 4, 1, ' ');
  if (add_chain(env_list, pwd) == -1)
    return (-1);
  free(pwd);
  remove_env(env_list, "PWD=");
  pwd = my_strcatdup("PWD=", tmp, 1, ' ');
  if (add_chain(env_list, pwd) == -1)
    return (-1);
  free(pwd);
  free(tmp);
  return (0);
}
