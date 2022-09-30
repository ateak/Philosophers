/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 17:57:32 by ateak             #+#    #+#             */
/*   Updated: 2022/07/06 12:55:16 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_sleeps(t_philosophers	*philos)
{
	ft_print(philos, "is sleeping");
	ft_usleep(philos->data->time_to_sleep);
}

static void	philo_eats(t_philosophers *philos)
{
	sem_wait(philos->data->forks);
	ft_print(philos, "has taken a fork");
	sem_wait(philos->data->forks);
	ft_print(philos, "has taken a fork");
	ft_print(philos, "is eating");
	sem_wait(philos->meal);
	philos->mealtime = timestamp();
	sem_post(philos->meal);
	ft_usleep(philos->data->time_to_eat);
	sem_post(philos->data->forks);
	sem_post(philos->data->forks);
	philos->num_meals_flag++;
}

static void	philo_thinks(t_philosophers *philos)
{
	ft_print(philos, "is thinking");
}

static void	*check_death(void *args)
{
	t_philosophers	*ph;

	ph = (t_philosophers *)args;
	while (1)
	{
		sem_wait(ph->meal);
		if (timestamp() - ph->mealtime > ph->data->time_to_die)
		{
			ph->data->output_dead = 1;
			printf("%zu %zu is dead\n", timestamp() - ph->data->start_time,
				ph->id);
			sem_post(ph->data->death);
			sem_post(ph->meal);
			return (0);
		}
		sem_post(ph->meal);
		ft_usleep(1);
	}
}

void	philo_life(t_data *data, size_t i)
{
	t_philosophers	philos;

	philos.data = data;
	philos.id = i + 1;
	philos.num_meals_flag = 0;
	philos.mealtime = data->start_time;
	pthread_create(&philos.monitor_tid, NULL, check_death, &philos);
	pthread_detach(philos.monitor_tid);
	while (philos.num_meals_flag != data->num_meals)
	{
		philo_thinks(&philos);
		philo_eats(&philos);
		philo_sleeps(&philos);
	}
	exit (0);
}
