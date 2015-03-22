/*
** string.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Mon Jan 26 01:31:03 2015 arnaud boulay
** Last update Sun Feb 22 17:40:12 2015 Boulay Arnaud
*/

#include <stdlib.h>
#include "my.h"

int	is_inside(char *str, char *str2)
{
  int	i;
  int	j;

  i = -1;
  j = 0;
  while (str[++i] != '\0')
    if (str[i] == str2[j])
      {
	if (str2[++j] == '\0')
	  return (1);
      }
    else if (j != 0)
      return (0);
  return (0);
}

int	my_strcmp(char *str1, char *str2)
{
  int	i;

  i = 0;
  if (str1 == NULL || str2 == NULL)
    return (-1);
  while (str1[i] != '\0' && str2[i] != '\0')
    if (str1[i] == str2[i])
      ++i;
    else
      return (0);
  if (str1[i] == '\0' && str2[i] == '\0')
    return (1);
  else if (str1[i] == '\0')
    return (2);
  return (0);
}

char	*my_strcpy(char *dest, char *src)
{
  int	i;

  i = -1;
  while (src[++i] != '\0')
    dest[i] = src[i];
  dest[i] = '\0';
  return (dest);
}

char	*my_strdup(char *str)
{
  char	*new;

  if ((new = malloc(sizeof(char) * (my_strlen(str) + 1))) == NULL)
    {
      my_putstr("Error: Malloc failed in my_strdup.\n");
      return (NULL);
    }
  new = my_strcpy(new, str);
  return (new);
}

char	*my_strcatdup(char *dest, char *src, int l, char c)
{
  int	i;
  int	j;
  char	*str;

  i = -1;
  j = -1;
  if ((str = malloc(sizeof(char) * (my_strlen(dest) + my_strlen(src) + l)))
      == NULL)
    {
      my_putstr("Error: Malloc failed in my_strcatdup.\n");
      return (NULL);
    }
  while (dest[++i] != '\0')
    str[++j] = dest[i];
  i = -1;
  if (l == 2)
    str[++j] = c;
  while (src[++i] != '\0')
    str[++j] = src[i];
  str[++j] = '\0';
  return (str);
}
