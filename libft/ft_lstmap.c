#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *res;

	res = NULL;
	if (lst != NULL)
	{
		if ((res = ft_lstnew(f(lst->content))) == NULL)
			return (NULL);
		res->next = ft_lstmap(lst->next, f, del);
		if (res->next == NULL && lst->next != NULL)
		{
			del(res->content);
			free(res);
			return (NULL);
		}
	}
	return (res);
}
