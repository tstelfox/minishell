/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: ztan <ztan@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/05 17:12:59 by ztan          #+#    #+#                 */
/*   Updated: 2021/04/08 17:39:50 by zenotan       ########   odam.nl         */
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
	insertion_test_new(&list);

}