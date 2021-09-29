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
	if (i == 0)
		pth[i]->left = &philo->allfork[philo->numphi - 1];
	else
		(pth[i])->left = &philo->allfork[i - 1];
	pth[i]->right = &philo->allfork[i];
	pthread_mutex_init(pth[i]->right, NULL);
	pth[i]->pth = &philo->allpth[i];
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
	philo->allfork = malloc(sizeof(t_pthread) * (philo->numphi + 1));
	philo->allpth = malloc(sizeof(t_pthread) * (philo->numphi + 1));
	if (!philo->allfork || !philo->allpth || !pth)
	{
		free(pth);
		free(philo->allfork);
		free(philo->allpth);
		return (NULL);
	}
	i = -1;
	while (++i < philo->numphi)
		if (ft_creat_fthread(philo, pth, i))
			return (NULL);
	pth[i] = NULL;
	philo->general = 0;
	philo->genmut = malloc(sizeof(pthread_mutex_t));
	if (!philo->genmut || pthread_mutex_init(philo->genmut, NULL))
		return (0);
	return (pth);
}

int	print(t_philo *philo, const char *str, long time, int id)
{
	if (time == -1)
		return (0);
	if (pthread_mutex_lock(philo->genmut) != 0)
		return (0);
	printf("%ld %d %s\n", time, id + 1, str);
	if (pthread_mutex_unlock(philo->genmut) != 0)
		return (0);
	return (1);
}
