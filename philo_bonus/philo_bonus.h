/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ateak <ateak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 20:03:37 by ateak             #+#    #+#             */
/*   Updated: 2022/07/06 12:57:37 by ateak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	size_t			num_philo;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;	
	size_t			num_meals;
	size_t			start_time;
	int				output_dead;
	sem_t			*forks;
	sem_t			*output;
	sem_t			*death;

}				t_data;

typedef struct s_philosophers
{
	pthread_t		monitor_tid;
	size_t			id;
	t_data			*data;
	size_t			num_meals_flag;
	size_t			mealtime;
	sem_t			*meal;

}				t_philosophers;

int		init_data(t_data *data, char **argv, int argc);
int		init_sem(t_data *data, t_philosophers *philos);
void	init_philosophers(t_data *data);
void	philo_life(t_data *data, size_t i);
void	ft_destroy_sem(t_data *data, t_philosophers *philos);
int		ft_error(char *str);
size_t	ft_atoi(const char *str);
size_t	timestamp(void);
void	ft_print(t_philosophers	*philos, char *str);
void	ft_usleep(size_t time);

#endif
