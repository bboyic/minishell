/*
    ==REDIRECT STRUCTURE==
    contains the type of
    redirect and path to
    the file
*/
typedef struct s_redirect
{
    int     type;
    char    *path;
}   t_redirect;
/*
    ==PIPE STRUCTURE==
    contains info about
    pipe
    out = stdout
    in = input
*/
typedef struct s_pipe
{
    int in;
    int out;
}   t_pipe;
typedef struct s_heredoc
{
    int     on;
    char    *stop_word;
}   t_heredoc;
/*
    ==COMANDS STRUCTURE==
    contains:
    command aruments
    redirect structure
    pipe input
    pipe output
*/
typedef struct s_commands
{
    struct s_commands   *next;
    char                **arg;
    t_redirect          redirect;
    int                 var_or;
    t_pipe              pipe;
    t_heredoc           heredoc;
}   t_commands;
