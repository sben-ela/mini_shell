
# ifndef MINI_SHELL_H
# define  MINI_SHELL_H

#define		STRING 3
#define		INFILE 0
#define		OUTFILE 1
#define		APPEND 5
#define		DELIMITER 4
#define		PIPE 1
#define		CMD 3
#define		SINGLE_QUOTE 2
#define		DOUBLE_QUOTE 1
#define		WITHOUT_QUOTE 0
#include	<stdio.h>
#include	<stdlib.h>
#include	<unistd.h>
#include	<readline/readline.h>
#include	<readline/history.h>
#include	<fcntl.h>
#include	<sys/wait.h>
#include	<sys/errno.h>
#include	<string.h>
#include	<dirent.h>

int	status;

typedef struct s_env_elem
{
	char				*key;
	char				*value;
	int					equal;
	struct s_env_elem	*next;
	struct s_env_elem	*prev;
}	t_env_elem;

typedef struct s_env
{
	t_env_elem	*head;
	char		**env;
	int			size;
}	t_env;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct redire
{
	int		type;
	char	*infile;
	char	*outfile;
	char	*delimiter;
	int		quotes;
	struct redire *next;
}	t_redire;

typedef	struct cmd
{
	char		*cmd;
	t_fd		fd;
	struct cmd	*next;
}	t_cmd;

typedef	struct	shell
{
	t_cmd			*cmd;
	t_redire		*redir;
	char			**cmds;
	int				index;
	int				type;
	int				pipe;
	struct shell	*next;
}	t_shell;

typedef	struct content
{
	char	*content;
	int		quotes;
}	t_content;

//PARSING
// t_redire    *new_redir(t_content *content, int type);
void		mini_shell(t_env *ev, t_shell *shell, char *read, char *line);
t_redire    *new_redir(t_content *content, int type);
t_content	*parseword(char *word, char **env);
void		sigint_handler(int sig);
t_shell		*parse_line(char *line, char **env);
char		**full_cmds(t_cmd *cmd);
int			cmd_size(t_cmd *cmds);
char		*ft_strchrr(const char *s, int c);
char		**ft_split(char const *str, char c);
char		*parse_redirect(char *line);
t_redire	*redilast(t_redire *lst);
void		redi_add_back(t_redire **lst, t_redire *new);
t_cmd		*last_cmd(t_cmd *lst);
void		cmd_add_back(t_cmd **lst, t_cmd *new);
t_cmd		*new_cmd(char *content);
char	*parse_read(char *read, char *line, int i, int j);
int			check_edges(char *str);

// ENV utils
char		**convert_array(t_env *env);
void		del_env(t_env *env);
void		print_env(t_env *env);
t_env		*create_env(char **tab);
t_env		*init_env(t_env *env);
t_env_elem	*new_env_elem(char *line);
void		add_env_elem(t_env *env, t_env_elem *new);
t_env_elem	*search_env_elem(t_env *env, char *key);
void		del_env_elem(t_env *env, t_env_elem *elem);
char		*expand_env(char *line, char **env);
char		*get_expanded_value(char **line, char **env);
char		*search_env_var(char *key, char **env);

// ERROR
int			ft_puterr(char *cmd, char *arg, char *msg, int errnum);
int			ft_perror(char *msg, char *utils);

// UTILS
int 		ft_strcmp(char *s1, char *s2);
char		*ft_strjoinfree(char *s1, char *s2);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		ft_putstr_fd(char *s, int fd);
void		ft_putnstr(char *str, int n);
void		ft_putchar(char c);
int			ft_isalpha(int c);
char		*ft_strdup(char *str);
char		*ft_substr(char *s, int start, int len);
int			ft_strlen(const char *str);
char		**ft_split_v2(char const *str, char c);
int			ft_isalnum(int c);
char		*ft_itoa(int n);
int			ft_isalpha(int c);
int			count_redirect(char *line);
t_shell		*ft_lstlast(t_shell *lst);
void		ft_lstadd_back(t_shell **lst, t_shell *new);
int			count_char(char *str, char c);
char		*handle_param(char *str, char c);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strjoin(char *left_str, char *buff);
void		ft_putstr_fd(char *s, int fd);
int			parse_syntax(char *line, char c);
int			count_single_quotes(char *line);
int			count_double_quotes(char *line);
char		*expand(char *str,char **env);
int			ft_isalnum(int c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strdup(char *source);
int 		handle_pipes(char *line);
char		*ft_strtrimfree(char *s1, char *set);
char		*ft_strtrim(char *s1, char *set);
void		freedouble(char **args);
char		*ft_substrr(char const *s, unsigned int start, size_t len);
int			ft_strchr(char const *s, int c);
char		*ft_strtrime(char const *s1, char const *set);
	
//EXECUTION
void	exec_redir(t_shell *shell);
void		execute(t_shell *shell, t_env *env);
void	ft_execute(t_shell *shell, t_env *env);
int	check_builtins(char *cmd);
int exec_redir_in(char *infile, int *in);
void		execute_cmd(t_shell *shell, char **env);
void check_fd(t_cmd *cmd);
int			ft_lstsize(t_shell *lst);
void	dup_close(t_fd *fd);
void		ft_which_cmd(char **cmd, t_env *env);
int			check_builtins(char *cmd);
void	execute_cmd(t_shell *shell, char **env);
char		**get_paths(char **env, t_shell *shell);
char		*get_cmd(char **paths, char *cmd);
void		error(char *str, int n);
void		check_fd(t_cmd *cmd);
int			exec_redir_in(char *infile, int *in);
void		free_paths(char **paths);
void		here_doc(t_redire *redir, char **env);

// builtin cd
int			cd_builtin(char **cmd, t_env *env);
void		set_dir(t_env *ev, char *cwd, char *owd);

//builtin echo
int			echo_builtin(char **cmd);
void		echo(char **str, int pos);
void		ft_putstr(char *s);
void		ft_putchar(char c);
	
// builtin env
int			env_builtin(char **cmd, t_env *env);
	
// builtin exit
int			exit_builtin(char **cmd, t_env *env);
	
//builtin export
int			export_builtin(char **cmd, t_env *env);
void		ft_sort(t_env *env);
void		print_sorted_env(t_env *env);
void		add_var(t_env *env, char *cmd);
	
//builtin pwd
int			pwd_builtin(char *cmd);
	
//builtin unset
int			unset_builtin(char **cmd, t_env *env);

#endif
