/*
** mysh.h for mysh.h in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 12:56:25 2017 Cédric Thomas
** Last update Wed Jan  4 21:16:53 2017 Cédric Thomas
*/
#ifndef MYSH_H_
# define MYSH_H_

typedef struct		s_cmmd
{
  char			*cmd;
  char			*name;
  char			**argv;
}			t_cmmd;

typedef struct		s_info
{
  char			**env;
  t_cmmd		*cmd;
}			t_info;


/*
**misc.c
*/
char	**tabdup(char **tab);
void	print_prompt(char **ae);
/*
**str.c
*/
char	*strappend(char *s1, char *s2, int freeit);
int	my_nullstrlen(char *str);

/*
**env.c
*/
char	*getkey(char **ae, char *str, int dup);
int	changekey(char **ae, char *str, char *value, int freeit);
char	**deletekey(char **ae, char *key, int freeit);
char	**addkey(char **ae, char *key, char *value, int freeit);

#endif /* !MYSH_H_ */
