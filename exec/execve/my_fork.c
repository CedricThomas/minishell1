/*
** my_fork.c for my_fork in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Jan 11 10:34:47 2017 
** Last update Fri Jan 13 07:53:22 2017 Cédric Thomas
*/
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"
#include "my.h"

void	check_sig(int status)
{
  if (WTERMSIG(status) == SIGSEGV)
    my_puterror("Segmentation fault");
  if (WTERMSIG(status) == SIGFPE)
    my_puterror("Floating point exception");
  if (WCOREDUMP(status))
    my_puterror(" (core dumped)");
  my_puterror("\n");
}

int	son(char **argv, char *name, t_info *info)
{
  signal(SIGINT, SIG_DFL);
  execve(name, argv, info->env);
}

int		father(char **argv, char *name, t_info *info, int son)
{
  int	wstatus;

  wait(&wstatus);
  if (WIFEXITED(wstatus))
    info->last = WEXITSTATUS(wstatus);
  else if (WIFSIGNALED(wstatus))
    {
      info->last = wstatus;
      check_sig(wstatus);
    }
}

int	my_fork(char **argv, char *name, t_info *info)
{
  int	forkvalue;

  forkvalue = fork();
  if (forkvalue == 0)
    son(argv, name, info);
  else if (forkvalue > 0)
    father(argv, name, info, forkvalue);
  else
    my_puterror("fork: the creation of the child failed.\n");
  return (!forkvalue ? -1 : 0);
}
