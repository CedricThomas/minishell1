/*
** mysh.h for mysh.h in /home/cedric/delivery/PSU/PSU_2016_minishell1
** 
** Made by Cédric Thomas
** Login   <cedric@epitech.net>
** 
** Started on  Wed Jan  4 12:56:25 2017 Cédric Thomas
** Last update Tue Jan 10 16:10:54 2017 
*/
#ifndef MYSH_H_
# define MYSH_H_

#define QUOTE	"\"\'"

typedef struct		s_cmmd
{
  char			*cmd;
  char			**argv;
  int			argc;
}			t_cmmd;

typedef struct		s_info
{
  char			**env;
  char			**builtins;
  t_cmmd		*cmd;
  unsigned char		last;
  char			*old_pwd;
  char			*pwd;
}			t_info;

typedef struct		stat t_stat;

/*
**prompt/prompt.c
*/
void	print_prompt(t_info *info);

/*
**str.c
*/
char	*strappend(char *s1, char *s2, int freeit);
int	my_nullstrlen(char *str);
char	**tabdup(char **tab);
char	*replaceinstr(char *tochange, char *tofind, char *toreplace);
int	my_strtocharlen(char *str, char c);

/*
**env/env.c
*/
char	*getkey(char **ae, char *str, int dup);
int	changekey(char **ae, char *str, char *value, int freeit);
char	**deletekey(char **ae, char *key, int freeit);
char	**addkey(char **ae, char *key, char *value, int freeit);

/*
**env/key.c
*/
char	*getcleanpwd();
char	*getcleanhostname();

/*
**misc.c
*/
int	is_full_of(char *str, char c);
char	*my_strndup(char *str, int n);
int	skipthat(char *str, int *i, char c);
char	*my_getstr(int value);

/*
**parse/cmds.c
*/
t_cmmd	*get_token(char *cmds);
int	my_token_len(char *str, char c, int *index);

/*
**parse/args.c
*/
t_cmmd	*get_args(t_cmmd *cmds);
char	*dequotificator(char *str);
/*
**exec/exec.c
*/
int	exec(t_info *info, int index);
char    **get_builtins();

/*
**exec/builtins/exit.c
*/
unsigned int	exitsh(t_info *info, int index);

/*
**exec/builtins/cd.c
*/
unsigned int	cd(t_info *info, int index);

/*
**exec/builtins/setenv.c
*/
unsigned int	setenvsh(t_info *info, int index);


/*
**exec/builtins/setenv.c
*/
unsigned int	unsetenvsh(t_info *info, int index);

#endif /* !MYSH_H_ */
