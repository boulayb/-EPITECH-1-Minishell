/*
** my.h for minishell2 in /home/boulay_b/Rendu/SE2/PSU/PSU_2014_minishell2
**
** Made by Boulay Arnaud
** Login   <boulay_b@epitech.net>
**
** Started on  Wed Mar 11 20:35:31 2015 Boulay Arnaud
** Last update Wed Mar 11 20:37:50 2015 Boulay Arnaud
*/

#ifndef	MY_H_
# define MY_H_

# define BUFFER_SIZE	4096
# define LIGHT_BLUE	"\033[94m"
# define BLUE		"\033[34m"
# define GREEN		"\033[32m"
# define RED		"\033[31m"
# define DEFAULT	"\033[39m"
# define MY_PATH	"PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/heimdal/bin:/usr/heimdal/sbin"

typedef struct		s_env
{
  char			*str;
  struct s_env		*next;
  struct s_env		*back;
}			t_env;

typedef struct		s_builtins
{
  char			*str;
  int			(*ptr)(char **tab, char **path, char **tabsep,
			       t_env *env_list);
}			t_builtins;

int			my_getnbr(char *str);
int			is_inside(char *str, char *str2);
int			add_path(char *str, t_env *env_list);
int			check_env(t_env *env_list);
int			cd_to_oldpath(t_env *env_list);
int			cd_null(char **tab, t_env *env_list);
int			cd_to_home(char **tab, t_env *env_list);
int			find_options(char **tab, t_env *tmp_env, int *exec,
				     int *options);
int			exec_fake_env(char **tab, char **path, t_env *tmp_env,
				      int options);
int			remove_path(t_env *env_list);
int			pwd_to_home(t_env *env_list);
int			swap_pwd(t_env *env_list);
int			add_chain(t_env *env_list, char *str);
int			my_cd(char **tab, char **path, char **tabsep,
			      t_env *env_list);
int			my_env(char **tab, char **path, char **tabsep,
			       t_env *env_list);
int			my_setenv(char **tab, char **path, char **tabsep,
				  t_env *env_list);
int			my_unsetenv(char **tab, char **path, char **tabsep,
				    t_env *env_list);
int			my_exit(char **tab, char **path, char **tabsep,
				t_env *env_list);
int			my_strlen(char *str);
int			remove_env(t_env *env_list, char *str);
int			change_pwd(char **tab, char **path, t_env *env_list);
int			change_oldpwd(char **tab, t_env *env_list);
int			my_strcmp(char *str1, char *str2);
int			exec_program(char **tab, char **path, t_env *env_list);
char			*change_for_home(char *str, t_env *env_list);
char			*get_next_line(const int fd);
char			*my_strdup(char *str);
char			*my_strcatdup(char *dest, char *src, int l, char c);
char			*my_strcpy(char *dest, char *src);
char			*get_env(char *str, t_env *env_list);
char			**my_strtowordtab(char **tab, char *str, char sep);
char			**my_listtotab(char **env, t_env *env_list);
void			my_putchar(char c);
void			my_putstr(char *str);
void			my_putnbr(int nb);
void			free_tab(char **tab);
void			rm_chain(t_env *chain);
void			rm_list(t_env *env_list);
void			disp_env(t_env *env_list);
void			disp_prompt(t_env *env_list);
void			my_signal(void);
void			empty_list(t_env *env_list);
t_env			*create_env(t_env *env_list);
t_env			*create_list(char **env);

#endif /* !MY_H_ */
