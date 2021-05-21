#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

int				ft_toupper(int c);
int				ft_tolower(int c);
int				ft_isprint(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
int				ft_atoi(const char *str);
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strnstr(const char *big, const char *little, size_t len);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memset(void *s, int c, size_t n);
void			ft_bzero(void *s, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_calloc(size_t nmemb, size_t size);
char			*ft_strdup(const char *s);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strtrim(char const *s1, char const *set);
char			**ft_split(char const *s, char c);
char			*ft_itoa(int n);
char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int				ft_putchar_fd(char c, int fd);
int				ft_putstr_fd(char *s, int fd);
int				ft_putendl_fd(char *s, int fd);
int				ft_putnbr_fd(int n, int fd);
void			ft_lstadd_back(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstclear(t_list **lst, void (*del)(void*));
void			ft_lstdelone(t_list *lst, void (*del)(void*));
void			ft_lstiter(t_list *lst, void (*f)(void *));
void			ft_lstadd_front(t_list **lst, t_list *new);
t_list			*ft_lstlast(t_list *lst);
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *),
				void (*del)(void *));
t_list			*ft_lstnew(void *content);
int				ft_lstsize(t_list *lst);

/*
** Additional functions
*/

# define SPACE_SET "\t\r\f\v\n "

int				ft_isspace(int c);
int				ft_isstrempty(const char *s);
int				ft_isstrnum(const char *s);
int				ft_hasc(const char *s, int c);
int				ft_free_matrix(void ***m);
int				ft_putendl(char *s);
int				ft_puts(char *s);
int				ft_putc(char c);
int				ft_strequal(const char *s1, const char *s2);
int				ft_indexof(const char *s, const char *ss, \
					int from_index);
int				ft_getchar(int fd);
void			ft_swap(int v[], int i, int j);
void			ft_shellsort(int v[], int n);
void			ft_desc_shellsort(int v[], int n);
void			ft_qsort(int v[], int left, int right);
char			*ft_strcpy(char *dst, char *src);
char			*ft_strstr(const char *s1, const char *s2);
char			**ft_ssplit(const char *s, const char *set);

/*
** Function get_next_line
*/

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 512
# endif
# define CHUNK_SIZE 512

char			*ft_realloc_str(char **buf, unsigned long int size);
void			free_n_null(char **buf);
int				get_next_line(int fd, char **line);

#endif
