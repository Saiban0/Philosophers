/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_double_array.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchedru <bchedru@student.42lehavre.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:49:58 by ttaquet           #+#    #+#             */
/*   Updated: 2024/09/04 19:58:02 by bchedru          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libamoa.h"

void	ft_free_double_array(void **double_array)
{
	int	i;

	i = -1;
	if (!double_array)
		return ;
	while (double_array[++i])
		free(double_array[i]);
	free(double_array);
}
