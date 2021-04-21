/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 17:12:59 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/21 22:26:03 by zenotan       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "ghostshell.h"

void	ft_dlsreversetiter(t_dlist *lst, void (*f)(void *))
{
	t_dlist *temp;

	if (!lst)
		return ;
	temp = lst;
	while (temp)
	{
		f(temp->content);
		temp = temp->prev;
	}
}

void	del_test(t_dlist **list)
{
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");
	
	ft_dlstdelone(list, 11, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 10, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 9, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 8, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 7, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 6, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 6, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 5, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 4, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 3, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 2, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 1, del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlstdelone(list, 0, del_content);
	free(*list);
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item1")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item2")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item3")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item4")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item5")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item6")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item7")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item8")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item9")));
	ft_dlstadd_back(list, ft_dlstnew(ft_strdup("item10")));
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");

	ft_dlstclear(list, del_content);
	printf("lst:");
	ft_dlstiter(*list, print_data);
	printf("\n");
	printf("lst:");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");
}

void	getpos_test(t_dlist **list)
{
	t_dlist *lst = *list;

	printf("content[%s], pos[%i]\n", lst->next->next->next->next->content, ft_dlstgetpos(lst->next->next->next->next));
	ft_dlstdelone(list, ft_dlstgetpos(lst->next->next->next->next), del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	printf("content[%s], pos[%i]\n", lst->next->next->next->next->content, ft_dlstgetpos(lst->next->next->next->next));
	ft_dlstdelone(list, ft_dlstgetpos(lst->next->next->next->next), del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
}

// void	insertion_test(t_dlist **list)
// {
// 	t_dlist *lst = *list;
// 	t_dlist *new = NULL;

// 	ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace1")));
// 	// ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace2")));
// 	// ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace3")));


// 	ft_dlstreplace(&lst->next->next->next->next->next->next->next->next->next, new, del_content);
	
// 	ft_dlstiter((*list), print_data);
// 	printf("\n");
// 	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
// 	printf("\n");
	
// 	ft_dlstreplace(&lst, new, del_content);

// 	ft_dlstiter((*list), print_data);
// 	printf("\n");
// 	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
// 	printf("\n");
	
// }

void	new_delone_test(t_dlist **list)
{
	t_dlist *lst = *list;

	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");

	// ft_dlstdelone(&lst->next, 11, del_content);
	// ft_dlstiter(*list, print_data);
	// printf("\n");
	// ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	// printf("\n");
	
	ft_dlstdelone(list, ft_dlstgetpos(lst), del_content);
	ft_dlstiter(*list, print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");
}


void	insertion_test_new(t_dlist **list)
{
	t_dlist *new = NULL;

	ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace1")));
	// ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace2")));
	// ft_dlstadd_back(&new, ft_dlstnew(ft_strdup("replace3")));


	dreplace(list, new, ft_dlstgetpos((*list)->next->next->next->next->next->next->next->next->next), del_content);
	
	ft_dlstiter((*list), print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");
	
	dreplace(list, new, ft_dlstgetpos((*list)), del_content);

	ft_dlstiter((*list), print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");
	
}

void	env_test(t_dlist **list)
{
	// char *str = "test=LOL";
	char *str = "test=";

	if (valid_val(str) == 2)
	{
		printf("lesgoo\n");
		dreplace(list, split_env(str) , ft_dlstgetpos((*list)->next->next->next->next), del_content);
	}
	// if (valid_val(str) == 1)
	// 	list
	ft_dlstiter((*list), print_data);
	printf("\n");
	ft_dlsreversetiter(ft_dlstlast(*list), print_data);
	printf("\n");	
}

void	replace_env_test()
{
	
}

void	test()
{
	t_dlist *list = NULL;

	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item1")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item2")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item3")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item4")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item5")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item6")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item7")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item8")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item9")));
	ft_dlstadd_back(&list, ft_dlstnew(ft_strdup("item10")));
	ft_dlstiter(list, print_data);
	printf("\n");

	// del_test(&list);
	// getpos_test(&list);
	// insertion_test(&list);
	// new_delone_test(&list);
	// insertion_test_new(&list);
	env_test(&list);

}

// char	*get_env(t_shell **ghost, char *name)
// {
// 	char **list;
// 	int i;
// 	int j;

// 	if ((*ghost)->env)
// 		list = (*ghost)->env;
// 	i = 0;
// 	while (list[i])
// 	{
// 		j = 0;
// 		while (name[j] == list[i][j])
// 			j++;
// 		if (list[i][j] == '=')
// 			return (ft_substr(list[i], j + 1, ft_strlen(list[i])));
// 		i++;
// 	}
// 	return (NULL);
// }

// void	handle_env(t_shell **ghost, char **content)
// {
// 	free(*content);
// 	*content = get_env(ghost, *content);
// 	if (!*content)
// 		error_handler(ghost, INVALID_ENV,  "Failed to recognize env", *content);
// }

// // lft_utils
// size_t	ft_strlen(const char *s);
// void	*ft_memcpy(void *dst, const void *src, size_t n);
// void	ft_putstr_fd(char *str, int fd);
// int		ft_strcmp(const char *str1, const char *str2);
// void	ft_putnbr_fd(int n, int fd);
// void	ft_putchar_fd(char c, int fd);
// char	**ft_split(char const *s, char c);
// char	*ft_strchr(const char *s, int c);
// char	*ft_strdup(const char *s1);
// size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// char	*ft_strjoin(char *s1, char const *s2);
// int		ft_strncmp(const char *s1, const char *s2, size_t n);
// char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
// void	ft_bzero(void *s, size_t n);
// int		ft_isdigit(int c);
// int		ft_isalpha(int c);
// int		ft_isalnum(int c);
// int		ft_atoi(const char *str);

// # LFT = ft_putstr_fd.c \
// # 		ft_putnbr_fd.c \
// # 		ft_putchar_fd.c \
// # 		ft_strlen.c \
// # 		ft_split.c \
// # 		ft_memcpy.c \
// # 		ft_strchr.c \
// # 		ft_strdup.c \
// # 		ft_strlcpy.c \
// # 		ft_substr.c \
// # 		ft_strjoin.c \
// # 		ft_strnstr.c \
// # 		ft_strcmp.c \
// # 		ft_bzero.c \
// # 		ft_lstadd_back_bonus.c \
// # 		ft_lstclear_bonus.c \
// # 		ft_lstdelone_bonus.c \
// # 		ft_lstiter_bonus.c \
// # 		ft_lstnew_bonus.c \
// # 		ft_lstsize_bonus.c \
// # 		ft_lstadd_front_bonus.c

// # LFT_PREFIX = $(addprefix lft_utils/, $(LFT))