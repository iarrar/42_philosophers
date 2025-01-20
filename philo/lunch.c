/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lunch.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:10:40 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/18 23:10:43 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_im_even(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	if (pthread_mutex_lock(philo->lf) == 0 && ft_am_i_dead(philo) == 0)
	{
		if (pthread_mutex_lock(philo->rf) == 0)
		{
			ft_eating(philo);
			pthread_mutex_unlock(philo->rf);
			pthread_mutex_unlock(philo->lf);
		}
		else
			pthread_mutex_unlock(philo->lf);
	}
	else
		pthread_mutex_unlock(philo->lf);
	return ;
}

void	ft_im_odd(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	if (pthread_mutex_lock(philo->rf) == 0 && ft_am_i_dead(philo) == 0)
	{
		if (pthread_mutex_lock(philo->lf) == 0)
		{
			ft_eating(philo);
			pthread_mutex_unlock(philo->lf);
			pthread_mutex_unlock(philo->rf);
		}
		else
			pthread_mutex_unlock(philo->rf);
	}
	else
		pthread_mutex_unlock(philo->rf);
	return ;
}

void	ft_eating(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	pthread_mutex_lock(philo->time);
	philo->start = ft_timestamp(philo);
	pthread_mutex_unlock(philo->time);
	pthread_mutex_lock(philo->write);
	printf("[timestamp = %ld ms] : philo %d has\
 taken a fork\n", ft_timestamp(philo), philo->count);
	printf("[timestamp = %ld ms] : philo %d has\
 taken a fork\n", ft_timestamp(philo), philo->count);
	pthread_mutex_unlock(philo->write);
	pthread_mutex_lock(philo->write);
	printf("[timestamp = %ld ms] : philo %d\
 is eating\n", ft_timestamp(philo), philo->count);
	pthread_mutex_unlock(philo->write);
	pthread_mutex_lock(philo->m_round);
	if (philo->round > 0)
		philo->round--;
	pthread_mutex_unlock(philo->m_round);
	usleep(philo->tte * 1000);
}
