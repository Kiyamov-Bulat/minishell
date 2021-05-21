#include "libft.h"

void	ft_shellsort(int v[], int n)
{
	int gap;
	int i;
	int j;

	gap = n / 2;
	while (gap > 0)
	{
		i = gap;
		while (i < n)
		{
			j = i - gap;
			while (j >= 0 && v[j] > v[j + gap])
			{
				ft_swap(v, j, j + gap);
				j -= gap;
			}
			i++;
		}
		gap /= 2;
	}
}
