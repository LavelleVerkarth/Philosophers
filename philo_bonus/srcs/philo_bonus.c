/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:44:05 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/08 11:44:12 by lverkart         ###   ########.fr       */
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

void	*ft_cooker(void *buf)
{
	t_pthread	*pth;
	int			i;

	i = -1;
	pth = buf;
	if (pthread_detach(pth->t))
		pthread_exit(0);
	while (++i < pth->philo->maxeat * pth->philo->numphi)
	{
		sem_wait(pth->philo->meat);
	}
	sem_post(pth->philo->kill);
	return (0);
}

int	t_please_to_the_table(t_pthread	**pth)
{
	int	i;

	i = -1;
	if (pth[0]->philo->maxeat)
		pthread_create(&pth[0]->t, NULL, ft_cooker, (void *)pth[0]);
	while (pth[++i] != NULL)
	{
		pth[i]->pid = fork();
		if (pth[i]->pid < 0)
			return (1);
		if (!pth[i]->pid)
			ft_local_table_manners(pth[i]);
	}
	i = -1;
	sem_wait(pth[0]->philo->kill);
	while (pth[++i] != NULL)
		kill(pth[i]->pid, SIGKILL);
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
