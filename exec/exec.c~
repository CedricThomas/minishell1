/*
** exec.c for exec_selector in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Sun Jan  8 14:13:47 2017 
** Last update Tue Jan 10 11:00:59 2017 
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

void	**get_fct(unsigned int	(*fct[6])(t_info *info, int index))
{
  fct[0] = &exitsh;
  fct[1] = &cd;
  fct[2] = &setenvsh;
  fct[3] = &unsetenvsh;
}

int		try_builtins(t_info *info, int index, int *exit)
{
  int		i;
  unsigned int	(*fct[6])(t_info *info, int index);
  unsigned int	rt;

  i = -1;
  rt = 1;
  get_fct(fct);
  while (info->builtins[++i] && rt)
    {
      if (!my_strcmp(info->builtins[i], info->cmd[index].argv[0]))
      	rt = fct[i](info, index);
      if (!my_strcmp("exit", info->cmd[index].argv[0]) && !rt)
  	*exit = 1;
    }
  return (rt);
}

int	exec(t_info *info, int index)
{
  int	exit;

  exit = 0;
  if (try_builtins(info, index, &exit));
  /*   try_exec(info, index); */
  return (exit);
}
