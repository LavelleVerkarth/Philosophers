/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lverkart <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 11:38:28 by lverkart          #+#    #+#             */
/*   Updated: 2021/07/08 11:38:31 by lverkart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>

# define ERROR_ARG "./philo number_of_philosophers time_to_die time_to_eat \
time_to_sleep [number_of_times_each_philosopher_must_eat]"

typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	int				numphi;
	int				timdie;
	int				timeat;
	int				maxeat;
	int				timslp;
	int				begsec;
	int				begusec;
	int				general;
	pthread_t		*allpth;
	t_mutex			*allfork;
	t_mutex			*genmut;
	pthread_t		t;
}				t_philo;

typedef struct s_pthread
{
	t_philo		*philo;
	t_mutex		*left;
	t_mutex		*right;
	pthread_t	*pth;
	int			name;
	long		laseat;
	int			status;

}				t_pthread;

int			ft_atoi(const char *str);
int			ft_error(char *str);
void		ft_free_table(t_pthread	**pth, t_philo *philo);
int			ft_free_error(t_philo *philo, t_pthread **pth, int i);
int			ft_parse_philo(int argc, char **argv, t_philo *philo);
int			ft_beginning_of_time(t_philo *philo);
t_pthread	**ft_table_setting(t_philo *philo);
int			print(t_philo *philo, const char *str, long time, int id);
long		ft_get_time(t_philo *philo);
void		*ft_local_table_manners(void *buf);
void		*ft_manager(void *buf);
int			print_dead(t_philo *philo, const char *str, long time, int id);

#endif
