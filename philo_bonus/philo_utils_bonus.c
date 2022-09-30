/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 19:58:49 by ateak             #+#    #+#             */
/*   Updated: 2022/07/06 12:56:21 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_error(char *str)
{
	printf("%s", str);
	return (1);
}

size_t	ft_atoi(const char *str)
{
	int			i;
	size_t		n;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		n = n * 10 + str[i] - 48;
		i++;
	}
	return (n);
}

size_t	timestamp(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((size_t)t.tv_sec * 1000 + (size_t)t.tv_usec / 1000);
}

void	ft_print(t_philosophers	*philos, char *str)
{
	sem_wait(philos->data->output);
	if (philos->data->output_dead)
	{
		sem_post(philos->data->output);
		return ;
	}
	printf("%zu %zu %s\n", timestamp() - philos->data->start_time,
		philos->id, str);
	sem_post(philos->data->output);
}

void	ft_usleep(size_t time)
{
	size_t	res;

	res = timestamp() + time;
	while (timestamp() < res)
	{
		usleep(50);
	}
}
