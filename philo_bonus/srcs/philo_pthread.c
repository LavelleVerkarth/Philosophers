/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_pthread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:54:54 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/10 21:54:56 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_left_right(t_pthread	*ph)
{
	if (sem_wait(ph->philo->fork) || !print(ph->philo, \
		"has taken a fork", ft_get_time(ph->philo), ph->name))
		pthread_exit(0);
	if (sem_wait(ph->philo->fork) || !(++ph->status) || \
		!print(ph->philo, "is eating", ft_get_time(ph->philo), ph->name))
		pthread_exit(0);
}

void	ft_slep_and_think(t_pthread	*ph)
{
	if (!print(ph->philo, "is sleeping", ft_get_time(ph->philo), \
		ph->name) || !my_sleep(ph->philo, ph->philo->timslp) || \
			!print(ph->philo, "is thinking", \
				ft_get_time(ph->philo), ph->name))
		pthread_exit(0);
}

int	printdie(t_philo *philo, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (sem_wait(philo->print) != 0)
		return (0);
	printf("%ld %d %s\n", time, id + 1, str);
	return (1);
}

void	*ft_manager(void *buf)
{
	t_pthread	*pth;
	long		time_of_die;

	pth = buf;
	if (pthread_detach(pth->t))
		pthread_exit(0);
	while (1)
	{
		time_of_die = ft_get_time(pth->philo) - \
		(pth->laseat + pth->philo->timdie);
		if (time_of_die > 0 && !(pth->status))
		{
			printdie(pth->philo, "is dead", ft_get_time(pth->philo), pth->name);
			sem_post(pth->philo->kill);
			exit(0);
		}
	}
}

void	*ft_local_table_manners(void *buf)
{
	t_pthread	*ph;
	int			i;

	ph = buf;
	ph->laseat = ft_get_time(ph->philo);
	if (pthread_create(&ph->t, NULL, ft_manager, (void *)ph))
		return (0);
	i = -1;
	while (++i < ph->philo->maxeat || ph->philo->maxeat == 0)
	{
		if (i != 0)
			ft_slep_and_think(ph);
		ft_left_right(ph);
		ph->laseat = ft_get_time(ph->philo);
		if (!my_sleep(ph->philo, ph->philo->timeat) || \
			sem_post(ph->philo->fork) || sem_post(ph->philo->fork))
			pthread_exit(0);
		--ph->status;
		sem_post(ph->philo->meat);
	}
	++ph->status;
	exit(0);
}
