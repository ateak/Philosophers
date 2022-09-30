/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:03:37 by ateak             #+#    #+#             */
/*   Updated: 2022/06/14 20:21:13 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>

typedef struct s_data
{
	size_t			num_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;	
	size_t			num_meals;
	size_t			start_time;
	int				all_philos_full_flag;
	int				dead_flag;
	pthread_mutex_t	*forks;
	pthread_mutex_t	output;
	pthread_mutex_t	all_philos_full;
	pthread_mutex_t	dead;

}				t_data;

typedef struct s_philosophers
{
	pthread_t		thread_id;
	size_t			id;
	size_t			left_fork;
	size_t			right_fork;
	size_t			num_meals_flag;
	int				full_flag;
	size_t			mealtime;
	t_data			*data;
	pthread_mutex_t	full;
	pthread_mutex_t	meal;

}				t_philosophers;

int		init_data(t_data *data, char **argv, int argc);
int		init_mutex(t_data *data);
int		init_philosophers(t_data *data, t_philosophers **philos);
int		init_threads(t_data *data, t_philosophers *philos);
void	*philo_life(void *philo);
void	philo_thinks(t_philosophers	*philos);
void	philo_eats(t_philosophers *philos, size_t fork_1, size_t fork_2);
void	philo_sleeps(t_philosophers	*philos);
void	check_death(t_data *data, t_philosophers **philos);
int		philo_dies(t_data *data, t_philosophers	**philos);
int		check_all_philos_full(t_data *data, t_philosophers *philos,
			size_t *tmp);
size_t	timestamp(void);
void	ft_usleep(size_t time);
size_t	ft_atoi(const char *s);
void	ft_print(t_philosophers	*philos, char *str);
int		ft_error(char *str);
void	ft_free(t_data *data, t_philosophers **philos);

#endif
