/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:25:32 by ateak             #+#    #+#             */
/*   Updated: 2022/07/05 17:30:49 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_destroy_sem(t_data *data, t_philosophers *philos)
{
	sem_close(data->output);
	sem_unlink("output");
	sem_close(data->forks);
	sem_unlink("forks");
	sem_close(data->death);
	sem_unlink("death");
	sem_close(philos->meal);
	sem_unlink("meal");
}

int	main(int argc, char **argv)
{
	t_data			data;
	t_philosophers	philos;

	if (argc != 5 && argc != 6)
		return (ft_error("Error: Wrong number of arguments!\n"));
	memset(&data, 0, sizeof(t_data));
	if (init_data(&data, argv, argc))
		return (ft_error("Error: Init data failed\n"));
	if (init_sem(&data, &philos))
	{
		ft_destroy_sem(&data, &philos);
		return (ft_error("Error: Init sem failed\n"));
	}
	init_philosophers(&data);
	ft_destroy_sem(&data, &philos);
	return (0);
}
