/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:54:34 by ateak             #+#    #+#             */
/*   Updated: 2022/06/14 20:21:39 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, char **argv, int argc)
{
	data->num_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
	{
		data->num_meals = ft_atoi(argv[5]);
		if (!data->num_meals)
			return (1);
	}
	else
		data->num_meals = -1;
	if (!data->num_philo || !data->time_to_die || !data->time_to_eat
		|| !data->time_to_sleep)
		return (1);
	data->start_time = timestamp();
	return (0);
}

int	init_mutex(t_data *data)
{
	size_t	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philo);
	if (!data->forks)
		return (1);
	while (i < data->num_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->output, NULL))
		return (1);
	if (pthread_mutex_init(&data->dead, NULL))
		return (1);
	if (pthread_mutex_init(&data->all_philos_full, NULL))
		return (1);
	return (0);
}

int	init_philosophers(t_data *data, t_philosophers **philos)
{
	size_t	i;

	i = 0;
	*philos = malloc(sizeof(t_philosophers) * data->num_philo);
	if (!*philos)
		return (1);
	memset(*philos, 0, sizeof(t_philosophers) * data->num_philo);
	while (i < data->num_philo)
	{
		(*philos)[i].data = data;
		(*philos)[i].id = i + 1;
		(*philos)[i].left_fork = i;
		if (i != data->num_philo - 1)
			(*philos)[i].right_fork = i + 1;
		(*philos)[i].mealtime = data->start_time;
		if (pthread_mutex_init(&(*philos)[i].meal, NULL))
			return (1);
		if (pthread_mutex_init(&(*philos)[i].full, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	init_threads(t_data *data, t_philosophers *philos)
{
	size_t	i;

	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&(philos[i].thread_id), NULL,
				philo_life, philos + i))
		{
			ft_free(data, &philos);
			return (1);
		}
		i++;
	}
	return (0);
}
