/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:57:32 by ateak             #+#    #+#             */
/*   Updated: 2022/06/14 20:41:16 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleeps(t_philosophers	*philos)
{
	ft_print(philos, "is sleeping");
	ft_usleep(philos->data->time_to_sleep);
	usleep(100);
}

void	philo_eats(t_philosophers *philos, size_t fork_1, size_t fork_2)
{
	pthread_mutex_lock(&philos->data->forks[fork_1]);
	ft_print(philos, "has taken a fork");
	pthread_mutex_lock(&philos->data->forks[fork_2]);
	ft_print(philos, "has taken a fork");
	pthread_mutex_lock(&philos->meal);
	philos->mealtime = timestamp();
	pthread_mutex_unlock(&philos->meal);
	ft_print(philos, "is eating");
	ft_usleep(philos->data->time_to_eat);
	pthread_mutex_unlock(&philos->data->forks[fork_1]);
	pthread_mutex_unlock(&philos->data->forks[fork_2]);
	philos->num_meals_flag++;
	if (philos->num_meals_flag >= philos->data->num_meals
		&& philos->data->num_meals)
	{
		pthread_mutex_lock(&philos->full);
		philos->full_flag = 1;
		pthread_mutex_unlock(&philos->full);
	}
}

void	philo_thinks(t_philosophers *philos)
{
	ft_print(philos, "is thinking");
}

void	*philo_life(void *philo)
{
	t_philosophers	*phil;

	phil = (t_philosophers *)philo;
	while (1)
	{
		pthread_mutex_lock(&phil->data->all_philos_full);
		pthread_mutex_lock(&phil->data->dead);
		if (phil->data->dead_flag || phil->data->all_philos_full_flag)
		{
			pthread_mutex_unlock(&phil->data->dead);
			pthread_mutex_unlock(&phil->data->all_philos_full);
			break ;
		}
		pthread_mutex_unlock(&phil->data->dead);
		pthread_mutex_unlock(&phil->data->all_philos_full);
		philo_thinks(phil);
		if (phil->id % 2)
			philo_eats(phil, phil->left_fork, phil->right_fork);
		else
			philo_eats(phil, phil->right_fork, phil->left_fork);
		philo_sleeps(phil);
	}
	return (0);
}
