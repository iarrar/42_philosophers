/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:12:36 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/18 23:12:38 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_time_left(t_data *data, int i)
{
	int	res;

	pthread_mutex_lock(data->monitor->time);
	res = (data->philo[i].start + data->philo[i].ttd) \
		- ft_timestamp(&data->philo[i]);
	pthread_mutex_unlock(data->monitor->time);
	return (res);
}

int	ft_check_meals(t_data *data)
{
	int	i;
	int	meals;

	meals = 0;
	i = 0;
	while (i < data->philo->nphilo)
	{
		pthread_mutex_lock(data->philo[i].m_round);
		if (data->philo[i].round == 0)
			meals++;
		pthread_mutex_unlock(data->philo[i].m_round);
		i++;
	}
	if (meals == data->philo->nphilo)
		return (1);
	else
		return (0);
}

int	ft_check_round(t_data *data, int i)
{
	pthread_mutex_lock(data->monitor->m_round);
	if (data->philo[i].round == 0)
	{
		pthread_mutex_unlock(data->monitor->m_round);
		return (0);
	}
	else
		pthread_mutex_unlock(data->monitor->m_round);
	return (1);
}

void	*ft_monitor(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (ft_check_meals(data) == 0)
	{
		i = 0;
		while (i < data->philo->nphilo)
		{
			if (ft_time_left(data, i) < -1 && ft_check_round(data, i) != 0)
			{
				pthread_mutex_lock(data->monitor->write);
				printf("[timestamp monitor = %ld ms] philo %d died \
					\n", ft_timestamp(&data->philo[i]), i);
				pthread_mutex_unlock(data->monitor->write);
				ft_kill_them_all(data);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
