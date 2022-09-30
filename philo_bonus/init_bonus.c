/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:54:34 by ateak             #+#    #+#             */
/*   Updated: 2022/07/06 12:52:10 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	init_sem(t_data *data, t_philosophers *philos)
{
	data->output = sem_open("output", O_CREAT | O_EXCL, 0664, 1);
	if (data->output == SEM_FAILED)
	{
		ft_destroy_sem(data, philos);
		return (1);
	}
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0664, data->num_philo);
	if (data->forks == SEM_FAILED)
	{
		ft_destroy_sem(data, philos);
		return (1);
	}
	data->death = sem_open("death", O_CREAT | O_EXCL, 0664, 0);
	if (data->death == SEM_FAILED)
	{
		ft_destroy_sem(data, philos);
		return (1);
	}
	philos->meal = sem_open("meal", O_CREAT | O_EXCL, 0664, 0);
	if (philos->meal == SEM_FAILED)
	{
		ft_destroy_sem(data, philos);
		return (1);
	}
	return (0);
}

static void	ft_fork_philo(t_data *data, int *pid)
{
	size_t	i;

	i = 0;
	while (i < data->num_philo)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			while (i > 0)
			{
				kill(pid[i], SIGKILL);
				i--;
			}
			exit(1);
		}
		if (pid[i] == 0)
			philo_life(data, i);
		i++;
	}
}

void	init_philosophers(t_data *data)
{
	size_t	i;
	int		*pid;
	int		pid_killer;

	pid = malloc(sizeof(int) * data->num_philo);
	ft_fork_philo(data, pid);
	pid_killer = fork();
	if (pid_killer == 0)
	{
		sem_wait(data->death);
		i = 0;
		while (i < data->num_philo)
		{
			kill(pid[i], SIGKILL);
			i++;
		}
		exit (0);
	}
	i = 0;
	while (i < data->num_philo)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free (pid);
}
