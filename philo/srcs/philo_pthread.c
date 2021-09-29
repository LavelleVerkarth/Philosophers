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

int	my_sleep(t_philo *philo, long n)
{
	long	time;

	time = ft_get_time(philo) + n;
	if (time == n - 1)
		return (0);
	while (ft_get_time(philo) < time)
		usleep(100);
	return (1);
}

void	ft_left_right(t_pthread	*ph)
{
	if (ph->name % 2 == 0)
	{
		usleep(100);
		if (pthread_mutex_lock(ph->left) || !print(ph->philo, \
		"has taken a fork", ft_get_time(ph->philo), ph->name))
			pthread_exit(0);
		if (pthread_mutex_lock(ph->right) || !(++ph->status) \
			|| !print(ph->philo, "is eating", \
				ft_get_time(ph->philo), ph->name))
			pthread_exit(0);
	}
	else
	{
		if (pthread_mutex_lock(ph->right) || !print(ph->philo, \
			"has taken a fork", ft_get_time(ph->philo), ph->name))
			pthread_exit(0);
		if (pthread_mutex_lock(ph->left) || !(++ph->status) || \
		!print(ph->philo, "is eating", ft_get_time(ph->philo), ph->name))
			pthread_exit(0);
	}
}

void	ft_slep_and_think(t_pthread	*ph)
{
	if (!print(ph->philo, "is sleeping", ft_get_time(ph->philo), \
		ph->name) || !my_sleep(ph->philo, ph->philo->timslp) || \
			!print(ph->philo, "is thinking", \
				ft_get_time(ph->philo), ph->name))
		pthread_exit(0);
}

void	*ft_local_table_manners(void *buf)
{
	t_pthread	*ph;
	int			i;

	ph = buf;
	pthread_detach(*ph->pth);
	i = -1;
	ph->laseat = ft_get_time(ph->philo);
	while (++i < ph->philo->maxeat || ph->philo->maxeat == 0)
	{
		if (i != 0)
			ft_slep_and_think(ph);
		ft_left_right(ph);
		ph->laseat = ft_get_time(ph->philo);
		if (!my_sleep(ph->philo, ph->philo->timeat) || \
			pthread_mutex_unlock(ph->right) || pthread_mutex_unlock(ph->left))
			pthread_exit(0);
		--ph->status;
		if (ph->laseat == -1)
			pthread_exit(0);
	}
	++ph->status;
	pthread_mutex_lock(ph->philo->genmut);
	ph->philo->general++;
	pthread_mutex_unlock(ph->philo->genmut);
	pthread_exit(0);
}

void	*ft_manager(void *buf)
{
	t_pthread	**pth;
	int			i;
	long		time_of_die;

	pth = buf;
	while (1)
	{
		i = -1;
		while (pth[++i])
		{
			time_of_die = ft_get_time(pth[i]->philo) - \
			(pth[i]->laseat + pth[i]->philo->timdie);
			if (time_of_die > 0 && !(pth[i]->status))
			{
				print_dead(pth[i]->philo, "is dead", \
					ft_get_time(pth[i]->philo), pth[i]->name);
				pthread_exit(0);
			}
		}
		if (pth[0]->philo->general == pth[0]->philo->numphi)
			pthread_exit(0);
	}
}
