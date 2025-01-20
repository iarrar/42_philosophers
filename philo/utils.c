/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:27:38 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/12 17:27:41 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	res;

	res = 0;
	i = 0;
	sign = 1;
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
	{
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
		{
			sign = -1;
		}
		i++;
	}
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * sign);
}

long int	ft_timestamp(t_philo *philo)
{
	long int		ts;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	ts = (((tv.tv_sec - philo->pzeros) * 1000000)
			+ (tv.tv_usec - philo->pzerom)) / 1000;
	return (ts);
}

int	ft_am_i_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->dead);
	pthread_mutex_lock(philo->m_round);
	if (philo->die == 1 || philo->round == 0)
	{
		pthread_mutex_unlock(philo->m_round);
		pthread_mutex_unlock(philo->dead);
		return (1);
	}
	pthread_mutex_unlock(philo->m_round);
	pthread_mutex_unlock(philo->dead);
	return (0);
}

void	ft_kill_them_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->monitor->dead);
	while (i < data->philo->nphilo)
	{
		data->philo[i].die = 1;
		i++;
	}
	pthread_mutex_unlock(data->monitor->dead);
}
