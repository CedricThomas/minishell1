/*
** fork.c for mysh.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 16:30:38 2017 
** Last update Tue Jan 10 22:54:33 2017 
*/
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void   	check_error(char *pathabs, t_info *info, char *str)
{
  if (pathabs && access(pathabs, F_OK))
    {
      my_puterror(str);
      my_puterror(": Command not found.\n");
      info->last = 1;
    }
  else if (pathabs && access(pathabs, X_OK))
    {
      my_puterror(str);
      my_puterror(": Permission denied.\n");
      info->last = 1;
    }
}

char	*try_path(char *str, char **path, t_info *info)
{
  int	i;
  char	*pathabs;
  int	baccess;

  i = -1;
  baccess = 0;
  pathabs = NULL;
  while (path[++i] && !baccess)
    if (!access(str, X_OK))
      baccess = 1;
    else if (!access(path[i], F_OK))
      {
	baccess = 1;
	if (!access(path[i], X_OK))
	  {
	    pathabs = my_strdup(path[i]);
	  }
      }
  free_tab(path);
  return (pathabs ? pathabs : my_strdup(str));
}

char	**replacepath(t_info *info, int index, char **pathabs)
{
  int	i;
  char	*home;
  char	**dup;
  char	**path;

  i = -1;
  if ((dup = tabdup(info->cmd[index].argv)) == NULL)
    return (NULL);
  if ((path = my_split(getkey(info->env, "PATH", 0), ':')) == NULL)
    if ((path = my_split("/bin:/usr/bin", ':')) == NULL)
      exit(84);
  home = getkey(info->env, "HOME", 0);
  while (dup[++i] && home != NULL)
    dup[i] = replaceinstr(dup[i], "~", home);
  i = -1;
  while (path && path[++i])
    {
      if (path[i][my_strlen(path[i])] != '/')
	path[i] = strappend(path[i], "/", 1);
      path[i] = strappend(path[i], dup[0], 1);
    }
  *pathabs = try_path(dup[0], path, info);
  check_error(*pathabs, info, info->cmd[index].argv[0]);
  return (dup);
}

void		print_out(int value, t_info *info)
{
  info->last = value;
  if (value == SIGSEGV)
    my_puterror("Segmentation fault\n");
  else if (value == SIGFPE)
    my_puterror("Floating exception\n");
}

int		my_exec(t_info *info, int index)
{
  char		**dup;
  char		*pathabs;
  int		pid;
  int		exit;

  info->last = 0;
  dup = replacepath(info, index, &pathabs);
  if (!info->last && (pid = fork()))
      if (pid == 0)
  	{
  	  signal(SIGINT, SIG_DFL);
  	  execve(pathabs, dup, info->env);
	  free(pathabs);
	  free_tab(dup);
	  free_info(info);
  	  return (-1);
  	}
      else
	{
	  waitpid(pid, &exit, 0);
	  print_output(exit, info);
	}
  free_tab(dup);
  free(pathabs);
  return (0);
}
