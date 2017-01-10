/*
** exit.c for exit.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 16:44:37 2017 
** Last update Tue Jan 10 21:59:10 2017 
*/
#include "my.h"
#include "mysh.h"

unsigned int	exitsh(t_info *info, int index)
{
  int		i; 
  unsigned int	rt;

  i = -1;
  rt = 0;
  info->last = 1;
  while (info->cmd[index].argv[++i]);
  if (i == 1)
    rt = -1;
  else if (i == 2)
    {
      i = -1;
      while (info->cmd[index].argv[1][++i] && is_nb(info->cmd[index].argv[1][i]));
      if (!info->cmd[index].argv[1][i])
	{
	  rt = -1;
	  info->last = my_getnbr(info->cmd[index].argv[1]);
	}
      else if (!is_nb(info->cmd[index].argv[1][i]) && i > 0)
	my_puterror("exit: Badly formed number.\n");      
      else
	my_puterror("exit: Expression Syntax.\n");
    }
  else
    my_puterror("exit: Expression Syntax.\n");
  return (rt);
}
