/*
** my_fork.c for my_fork in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Wed Jan 11 10:34:47 2017 
** Last update Fri Jan 20 09:11:32 2017 Cédric Thomas
*/
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "mysh.h"
#include "my.h"

void	check_errno(char *str)
{
  my_puterror(str);
  my_puterror(": ");
  if (errno == ENOEXEC)
    {
      my_puterror(str);
      my_puterror(": ");
      my_puterror("cannot execute binary file");
    }
  my_puterror("\n");
}

void	check_sig(int status)
{
  int	dump;

  dump = 0;
  if (WTERMSIG(status) == SIGSEGV && (dump = 1))
    my_puterror("Segmentation fault");
  if (WTERMSIG(status) == SIGFPE && (dump = 1))
    my_puterror("Floating exception");
  if (WTERMSIG(status) == SIGABRT && (dump = 1))
    my_puterror("Aborted");
  if (WTERMSIG(status) == SIGBUS && (dump = 1))
    my_puterror("Bus error");
  if (dump && WCOREDUMP(status))
    my_puterror(" (core dumped)");
  my_puterror("\n");
}

int	son(char **argv, char *name, t_info *info)
{
  signal(SIGINT, SIG_DFL);
  if (execve(name, argv, info->env) == -1)
    check_errno(name);
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
