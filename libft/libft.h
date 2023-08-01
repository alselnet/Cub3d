/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aselnet <aselnet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 16:00:32 by aselnet           #+#    #+#             */
/*   Updated: 2023/07/06 02:23:04 by aselnet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdarg.h>

//BASIC LIBFT
int			ft_atoi(const char *str);
long long	ft_atol(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isinbase(int c, char const *set);
int			ft_isprint(int c);
char		*ft_itoa(int n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t n);
void		*ft_memmove(void *dest, const void *src, size_t n);
void		*ft_memset(void *s, int c, size_t n);
int			ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd, int *count);
int			ft_putstr_fd(char *s, int fd);
void		*ft_realloc(void *ptr, size_t size);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strdup(const char *s);
int			ft_strenvcmp(const char *s1, char *env, size_t n);
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
size_t		ft_strlcpy(char *dst, char const *src, size_t size);
size_t		ft_strlen(const char *s);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strmatch(const char *s, const char *charset);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char	*big, const char *little, size_t len);
char		*ft_strrchr(const char *s, int c);
void		ft_strrev(char *s);
int			ft_strslen(char const *s, int c);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char cz);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_tolower(int c);
int			ft_toupper(int c);

//BONUS LIBFT
typedef struct s_list
{
	int				content;
	struct s_list	*next;
	struct s_list	*prev;
}	t_list;

t_list		*ft_lstnew(int content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst);
void		ft_lstclear(t_list **lst);
void		ft_lstiter(t_list *lst, int (*f)(int));
t_list		*ft_lstmap(t_list *lst, int (*f)(int));

//GET_NEXT_LINE
char		*get_next_line(int fd);
int			ft_chr_is_in_base(const char *s, int c);
char		*ft_strjoin_gnl(char *s1, char *s2);

//PRINTF
int			ft_put_lower_hex_fd(unsigned long int value, int fd);
int			ft_put_upper_hex_fd(unsigned long int value, int fd);
int			ft_printaddr_fd(unsigned long long value, int fd);
void		ft_putunsigned_fd(unsigned int n, int fd, int *count);
int			ft_printf(char const *s, ...);

#endif