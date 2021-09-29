/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:38:06 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/10 21:38:07 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int				minus;
	int				i;
	long long int	sum;

	i = 0;
	minus = 1;
	sum = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		minus = -minus;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		sum = sum * 10 + str[i] - '0';
		i++;
	}
	return (minus * sum);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_error(char *str)
{
	write(2, "Error: ", ft_strlen("Error: "));
	write(2, str, ft_strlen(str));
	write(1, "\n", 1);
	return (1);
}

void	ft_free_table(t_pthread	**pth, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->numphi)
		free(pth[i]);
	free(pth);
}

int	ft_free_error(t_philo *philo, t_pthread **pth, int i)
{
	(void)philo;
	while (--i <= 0)
		free(pth[i]);
	free(pth);
	return (1);
}
