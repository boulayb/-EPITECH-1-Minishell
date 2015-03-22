/*
** main.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Jan 19 11:23:19 2015 arnaud boulay
** Last update Wed Mar 11 20:31:44 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include <signal.h>
#include "my.h"

static t_builtins	gl_builtins[] =
  {
    {"cd", &my_cd},
    {"env", &my_env},
    {"setenv", &my_setenv},
    {"unsetenv", &my_unsetenv},
    {"exit", &my_exit},
    {NULL, NULL}
  };

void			disp_prompt(t_env *env_list)
{
  static int		i;

  my_putstr(BLUE);
  my_putchar('(');
  if (env_list != NULL && get_env("USER=", env_list) != NULL)
    my_putstr(get_env("USER=", env_list) + 5);
  else
    my_putstr("boulay_b");
  my_putstr(" - ");
  if (env_list != NULL && get_env("PWD=/", env_list) != NULL)
    my_putstr(get_env("PWD=/", env_list) + 4);
  else
    my_putstr("minishell1");
  my_putchar(' ');
  my_putstr(LIGHT_BLUE);
  my_putnbr(i++);
  my_putstr(BLUE);
  my_putstr(")$>");
  my_putstr(LIGHT_BLUE);
}

int			fcnt_ptr(char **tab, char **path, char **tabsep, t_env *env_list)
{
  int			i;

  i = -1;
  while (gl_builtins[++i].str != NULL)
    {
      if (my_strcmp(tab[0], gl_builtins[i].str) == 1)
	{
	  if (gl_builtins[i].ptr(tab, path, tabsep, env_list) == -1)
	    return (-1);
	  return (0);
	}
    }
  if (exec_program(tab, path, env_list) == -1)
    return (-1);
  return (0);
}

int			my_prompt(char *str, char **path, t_env *env_list)
{
  char			**tabsep;
  char			**tab;
  int			i;

  tab = NULL;
  tabsep = NULL;
  i = -1;
  if ((tabsep = my_strtowordtab(tabsep, str, ';')) == NULL)
    return (-1);
  free(str);
  while (tabsep[++i] != NULL)
    {
      if ((tab = my_strtowordtab(tab, tabsep[i], ' ')) == NULL)
	return (-1);
      if (fcnt_ptr(tab, path, tabsep, env_list) == -1)
	return (-1);
      free_tab(tab);
    }
  disp_prompt(env_list);
  free_tab(tabsep);
  free_tab(path);
  return (0);
}

int			my_minishell(char **env)
{
  t_env			*env_list;
  int			ret;
  char			**path;
  char			*str;

  path = NULL;
  if ((env_list = create_list(env)) == NULL)
    return (-1);
  disp_prompt(env_list);
  my_signal();
  while ((str = get_next_line(0)) != NULL)
    {
      if (check_env(env_list) == -1)
	return (-1);
      if ((path = my_strtowordtab(path, get_env("PATH=", env_list) + 5, ':'))
	  == NULL)
	return (-1);
      ret = my_prompt(str, path, env_list);
      if (ret == 1)
	return (0);
      else if (ret == -1)
	return (-1);
    }
  rm_list(env_list);
  return (-1);
}

int			main(int ac, char **av, char **env)
{
  (void)ac;
  (void)av;
  if (my_minishell(env) == -1)
    return (-1);
  my_putstr(DEFAULT);
  return (0);
}
