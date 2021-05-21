#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	t_list *temp;

	if (*lst != NULL)
	{
		temp = *lst;
		*lst = new;
		new->next = temp;
	}
	else
		*lst = new;
}
