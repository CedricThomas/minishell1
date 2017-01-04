/*
** main.c for mysh in /home/cedric/delivery/ex
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Sat Oct 22 10:31:05 2016 Cédric Thomas
** Last update Wed Jan  4 21:17:31 2017 Cédric Thomas
*/
#include <stdlib.h>
#include "mysh.h"
#include "my.h"

int	main(int ac, char **av, char **ae)
{
  int	exit;
  char	**aedup;

  exit = 0;
  if ((aedup = tabdup(ae)) == NULL)
    return (84);
  print_prompt(aedup);
  free_tab(aedup);
  return (exit);
}
