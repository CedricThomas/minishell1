/*
** env.c for env in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Jan 11 17:30:51 2017 
** Last update Wed Jan 11 17:33:25 2017 
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int	envsh(t_info *info, int index)
{
  info->last = 0;
  if (info->cmd[index].argc == 1 && info->cmd[index].argv)
    my_show_wordtab(info->env);
  else
    {
      my_puterror("env: Too many arguments.\n");
      info->last = 1;
    }
  return (0);
}
