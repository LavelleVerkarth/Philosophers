/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:44:05 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/08 11:44:12 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_dead(t_philo *philo, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (pthread_mutex_lock(philo->genmut) != 0)
		return (0);
	usleep(1000);
	printf("%ld %d %s\n", time, id + 1, str);
	return (1);
}

long	ft_get_time(t_philo *philo)
{
	struct timeval	tv2;
	struct timeval	dtv;

	if (gettimeofday(&tv2, NULL) == -1)
		return (-1);
	dtv.tv_sec = tv2.tv_sec - philo->begsec;
	dtv.tv_usec = tv2.tv_usec - philo->begusec;
	if (dtv.tv_usec < 0)
	{
		dtv.tv_sec--;
		dtv.tv_usec += 1000000;
	}
	return (dtv.tv_sec * 1000 + dtv.tv_usec / 1000);
}

int	t_please_to_the_table(t_pthread	**pth)
{
	int	i;

	i = -1;
	if (pthread_create(&pth[0]->philo->t, NULL, ft_manager, (void *)pth))
		return (1);
	while (pth[++i] != NULL)
	{
		if (pthread_create(pth[i]->pth, NULL, \
			ft_local_table_manners, (void *)pth[i]))
			return (1);
	}
	if (pthread_join(pth[0]->philo->t, NULL))
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo		philo;
	t_pthread	**pth;

	if (argc < 5 || argc > 6)
		return (ft_error(ERROR_ARG));
	if (ft_parse_philo(argc - 1, &argv[1], &philo))
		return (1);
	pth = ft_table_setting(&philo);
	if (!pth)
		return (ft_error("no memory allocated for the table"));
	if (ft_beginning_of_time(&philo))
		return (ft_error("there won't be The Big Bang"));
	if (t_please_to_the_table(pth))
		return (ft_error("the fthread broke"));
	ft_free_table(pth, &philo);
	return (0);
}	
