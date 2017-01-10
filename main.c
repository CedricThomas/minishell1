/*
** main.c for mysh in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Tue Jan 10 21:47:50 2017 
*/
#include <signal.h>
#include <stdlib.h>
#include "my.h"
#include "mysh.h"
#include "my_printf.h"
#include "get_next_line.h"

void	free_info(t_info *info)
{
  free(info->old_pwd);
  free(info->pwd);
  free_tab(info->env);
  free_tab(info->builtins);
}

static int	try_env(t_info *info, char **ae)
{
  char	*temp;

  info->cmd = NULL;
  info->last = 0;
  info->old_pwd = my_strdup("");
  if ((info->env = tabdup(ae)) == NULL)
    return (0);
  if ((info->builtins = get_builtins()) == NULL)
    return (0);
  temp = getcleanpwd();
  if (getkey(info->env, "PWD", 0) == NULL)
    info->env = addkey(info->env, "PWD", temp, 0);
  else
    changekey(info->env, "PWD", temp, 0);
  info->pwd = temp;
  temp = getcleanhostname();
  if (getkey(info->env, "HOST", 0) == NULL)
    info->env = addkey(info->env, "HOST", temp, 0);
  free(temp);
  return (1);
}

static void	free_that(char *cmds, t_info *info, int i)
{
  if (info->cmd && cmds[0])
    free_tab(info->cmd[i].argv);
  if (info->cmd) 
    free(info->cmd[i].cmd);
}

static int	run(t_info *info)
{
  char		*cmds;
  int		exit;
  int		i;
  int		k;

  exit = 0;
  print_prompt(info);
  while (!exit && (cmds = get_next_line(0)))
    {
      i = -1;
      info->cmd = get_token(cmds);
      while (info->cmd && info->cmd[++i].cmd && !exit)
	{
	  exit = exec(info, i);
	  /* if (i > 0) */
	  /*   my_printf("--------------------------\n"); */
	  //	  my_printf("argc : %d, cmd : %s\nargcs :\n", info->cmd[i].argc, info->cmd[i].cmd);
	  //	  my_show_wordtab(info->cmd[i].argv);
	  free_that(cmds, info, i);
	}
      free(info->cmd);
      free(cmds);
      if (!exit)
	print_prompt(info);
    }
  my_putstr("exit\n");
  return (exit);
}

int		main(int ac, char **av, char **ae)
{
  t_info	info;

  signal(SIGINT, SIG_IGN);
  if (!try_env(&info, ae))
    return (84);
  run(&info);
  free_info(&info);
  return (info.last);
}
