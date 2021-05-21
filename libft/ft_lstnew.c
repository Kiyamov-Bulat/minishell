#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *l;

	if ((l = (t_list *)malloc(sizeof(t_list))) != NULL)
	{
		l->content = content;
		l->next = NULL;
	}
	return (l);
}
