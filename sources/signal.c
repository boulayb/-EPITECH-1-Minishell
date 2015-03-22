/*
** signal.c for minishell1 in /home/boulay_b/Rendu/PSU/PSU_2014_minishell1
**
** Made by arnaud boulay
** Login   <boulay_b@epitech.net>
**
** Started on  Sun Feb  1 14:49:42 2015 arnaud boulay
** Last update Sun Feb  1 17:41:50 2015 arnaud boulay
*/

#include <signal.h>
#include <stdlib.h>
#include "my.h"

void		catch_signal(int signal)
{
  if (signal == SIGINT || signal == SIGTSTP)
    {
      my_putchar('\n');
      disp_prompt(NULL);
    }
}

void		my_signal(void)
{
  signal(SIGINT, catch_signal);
  signal(SIGTSTP, catch_signal);
}
