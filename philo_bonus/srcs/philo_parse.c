/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 21:45:20 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/10 21:45:22 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_parse_philo(int argc, char **argv, t_philo *philo)
{
	int	i;
	int	n;

	i = -1;
	while (++i < argc)
	{
		n = -1;
		while (argv[i][++n])
		{
			if (argv[i][n] < 48 || argv[i][n] > 57)
				return (ft_error("arguments must be unsigned integers"));
		}
	}
	philo->numphi = ft_atoi(argv[0]);
	philo->timdie = ft_atoi(argv[1]);
	philo->timeat = ft_atoi(argv[2]);
	philo->timslp = ft_atoi(argv[3]);
	philo->maxeat = 0;
	if (argc == 5)
		philo->maxeat = ft_atoi(argv[4]);
	return (0);
}

int	ft_beginning_of_time(t_philo *philo)
{
	struct timeval	current_time;

	if (gettimeofday(&current_time, NULL) == -1)
		return (1);
	philo->begsec = current_time.tv_sec;
	philo->begusec = current_time.tv_usec;
	return (0);
}

int	ft_creat_fthread(t_philo *philo, t_pthread	**pth, int i)
{
	pth[i] = malloc(sizeof(t_pthread));
	if (!pth[i])
		return (ft_free_error(philo, pth, i));
	pth[i]->philo = philo;
	pth[i]->name = i;
	pth[i]->status = 0;
	pth[i]->laseat = ft_get_time(philo);
	return (0);
}

t_pthread	**ft_table_setting(t_philo *philo)
{
	t_pthread	**pth;
	int			i;

	pth = malloc(sizeof(t_pthread *) * (philo->numphi + 1));
	if (!pth)
		return (NULL);
	i = -1;
	while (++i < philo->numphi)
		if (ft_creat_fthread(philo, pth, i))
			return (NULL);
	pth[i] = NULL;
	philo->general = 0;
	sem_unlink("/fork");
	sem_unlink("/print");
	sem_unlink("/kill");
	sem_unlink("/meat");
	philo->fork = sem_open("/fork", O_CREAT, 0666, philo->numphi);
	philo->print = sem_open("/print", O_CREAT, 0666, 1);
	philo->kill = sem_open("/kill", O_CREAT, 0666, 0);
	philo->meat = sem_open("/meat", O_CREAT, 0666, 0);
	if (philo->fork == SEM_FAILED || philo->print == SEM_FAILED \
		|| philo->kill == SEM_FAILED)
		return (NULL);
	return (pth);
}

int	print(t_philo *philo, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (sem_wait(philo->print) != 0)
		return (0);
	printf("%ld %d %s\n", time, id + 1, str);
	if (sem_post(philo->print) != 0)
		return (0);
	return (1);
}
