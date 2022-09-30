/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:25:32 by ateak             #+#    #+#             */
/*   Updated: 2022/06/14 20:18:49 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_free(t_data *data, t_philosophers **philos)
{
	size_t	i;

	pthread_mutex_destroy(&data->output);
	pthread_mutex_destroy(&data->all_philos_full);
	pthread_mutex_destroy(&data->dead);
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_destroy(&(*philos)[i].meal);
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&(*philos)[i].full);
		i++;
	}
	if (*philos)
		free(*philos);
	if (data->forks)
		free(data->forks);
}

int	check_all_philos_full(t_data *data, t_philosophers *philos, size_t *tmp)
{
	pthread_mutex_lock(&philos->full);
	if (philos->full_flag)
		*tmp = *tmp + 1;
	pthread_mutex_unlock(&philos->full);
	if (*tmp == data->num_philo)
	{
		pthread_mutex_lock(&data->all_philos_full);
		data->all_philos_full_flag = 1;
		pthread_mutex_unlock(&data->all_philos_full);
		return (1);
	}
	return (0);
}

int	philo_dies(t_data *data, t_philosophers	**philos)
{
	size_t	i;
	size_t	tmp;

	tmp = 0;
	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_lock(&(*philos)[i].meal);
		if (timestamp() - (*philos)[i].mealtime > data->time_to_die)
		{
			pthread_mutex_lock(&data->dead);
			data->dead_flag = 1;
			pthread_mutex_unlock(&data->dead);
			pthread_mutex_unlock(&(*philos)[i].meal);
			printf("%zu %zu is dead\n", timestamp() - data->start_time,
				(*philos)[i].id);
			return (1);
		}
		pthread_mutex_unlock(&(*philos)[i].meal);
		if (check_all_philos_full(data, &(*philos)[i], &tmp))
			return (1);
		i++;
	}
	return (0);
}

void	check_death(t_data *data, t_philosophers **philos)
{
	size_t	i;

	while (1)
	{
		if (philo_dies(data, philos))
			break ;
	}
	i = 0;
	while (i < data->num_philo)
	{
		if (data->num_philo == 1)
			pthread_detach((*philos)[i].thread_id);
		pthread_join((*philos)[i].thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosophers	*philos;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: Wrong number of arguments!\n"));
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argv, argc))
		return (ft_error("Error: Init data failed\n"));
	if (init_mutex(&data))
	{
		ft_free(&data, &philos);
		return (ft_error("Error: Init mutex failed\n"));
	}
	if (init_philosophers(&data, &philos))
	{
		ft_free(&data, &philos);
		return (ft_error("Error: Init philosophers failed\n"));
	}
	if (init_threads(&data, philos))
		return (ft_error("Error: Init threads failed\n"));
	check_death(&data, &philos);
	ft_free(&data, &philos);
	return (0);
}
