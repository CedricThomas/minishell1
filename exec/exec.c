/*
** exec.c for exec_selector in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 14:13:47 2017 
** Last update Thu Jan 19 23:39:25 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

char	**get_builtins()
{
  char	**builtins;

  if ((builtins = malloc(sizeof(char *) * (6) )) == NULL)
    return (NULL);
  builtins[5] = NULL;
  builtins[0] = my_strdup("exit");
  builtins[1] = my_strdup("cd");
  builtins[2] = my_strdup("setenv");
  builtins[3] = my_strdup("unsetenv");
  builtins[4] = my_strdup("env");
  return (builtins);
}

void	**get_fct(int	(*fct[6])(t_info *info, int index))
{
  fct[0] = &exitsh;
  fct[1] = &cd;
  fct[2] = &setenvsh;
  fct[3] = &unsetenvsh;
  fct[4] = &envsh;
}

int		try_builtins(t_info *info, int index, int *exit)
{
  int		i;
  int		(*fct[6])(t_info *info, int index);
  int		rt;

  i = -1;
  rt = 1;
  get_fct(fct);
  while (info->builtins[++i] && rt == 1)
    {
      if (!my_strcmp(info->builtins[i], info->cmd[index].argv[0]))
      	rt = fct[i](info, index);
    }
  if (rt < 0)
    *exit = 1;
  return (rt);
}

int	exec(t_info *info, int index)
{
  int	exit;

  exit = 0;
  if (try_builtins(info, index, &exit) > 0)
    exit = my_exec(info, index);
  return (exit);
}
