/*
** exit.c for exit.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 16:44:37 2017 
** Last update Wed Jan 11 17:38:32 2017 
*/
#include "my.h"
#include "mysh.h"

int	check_syntax(char *arg, t_info *info)
{
  int	i;

  i = -1;
  while (arg[++i] && (is_nb(arg[i]) || (i == 0 && arg[0] == '-')));
  if (!arg[i])
    {
      info->last = my_getnbr(arg);
      return (-1);
    }
  else if (!is_nb(arg[i]) && i > 0)
    my_puterror("exit: Badly formed number.\n");
  else if (!is_nb(arg[i]))
    my_puterror("exit: Expression Syntax.\n");
  info->last = 1;
  return (0);
}

int	exitsh(t_info *info, int index)
{
  int	i;
  int	rt;

  i = -1;
  rt = 0;
  while (info->cmd[index].argv[++i]);
  if (i == 1)
    rt = -1;
  else if (i == 2)
    rt = check_syntax(info->cmd[index].argv[1], info);
  else
    {
      info->last = 1;
      my_puterror("exit: Expression Syntax.\n");
    }
  return (rt);
}
