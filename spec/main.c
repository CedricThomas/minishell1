/*
** main.c for lol in /home/cedric/delivery/PSU/PSU_2016_minishell1/spec
** 
** Made by 
** Login   <cedric.thomas@epitech.eu>
** 
** Started on  Mon Jan 16 17:06:14 2017 
** Last update Mon Jan 16 17:08:15 2017 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *p;

  __asm__("pushf\n"
	              "orl $0x40000, (%rsp)\n"
	  "popf");

  /*  
   * malloc() always provides aligned memory. 
   * Do not use stack variable like a[9], depending on the compiler you use, 
   * a may not be aligned properly. 
   */
  p = malloc(sizeof(int) + 1);
  memset(p, 0, sizeof(int) + 1);

  /* making p unaligned */
  p++;

  printf("%d\n", *(int *)p);

  return 0;
}  
