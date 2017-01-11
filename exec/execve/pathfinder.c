/*
** fork.c for mysh.c in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Tue Jan 10 16:30:38 2017 
** Last update Wed Jan 11 17:18:05 2017 
*/
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

void		check_error(char *pathabs, t_info *info, char *str)
{
  int		isadir;
  t_stat	mstat;

  isadir = 0;
  if (!stat(pathabs, &mstat))
    isadir = S_ISDIR(mstat.st_mode);
  if (pathabs && (access(pathabs, F_OK) || !is_in('/', pathabs)))
    {
      my_puterror(str);
      my_puterror(": Command not found.\n");
      info->last = 1;
    }
  else if (pathabs && access(pathabs, X_OK) || isadir)
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
  while (path[++i] && !baccess && !is_in('/', str))
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

int		my_exec(t_info *info, int index)
{
  char		**dup;
  char		*pathabs;
  int		ret;
  int		status;

  info->last = 0;
  dup = replacepath(info, index, &pathabs);
  ret = 0;
  if (!info->last)
    ret = my_fork(dup, pathabs, info);
  free_tab(dup);
  free(pathabs);
  return (ret);
}
