/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:29:12 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/12 17:29:15 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*philo;
	int		i;
	int		j;

	i = 0;
	j = -1;
	philo = (t_philo *)arg;
	while (i == 0 && j != 0)
	{
		ft_bandb(philo);
		ft_i_think(philo);
		ft_i_slip(philo);
		pthread_mutex_lock(philo->dead);
		i = philo->die;
		pthread_mutex_unlock(philo->dead);
		pthread_mutex_lock(philo->m_round);
		j = philo->round;
		pthread_mutex_unlock(philo->m_round);
	}
	return (NULL);
}

void	ft_bandb(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	if (philo->nphilo == 1)
	{
		pthread_mutex_lock(philo->lf);
		printf("[timestamp = %ld ms] : philo %d \
has taken a fork\n", ft_timestamp(philo), philo->count);
		usleep(philo->ttd * 1100);
		pthread_mutex_unlock(philo->lf);
		return ;
	}
	else if (philo->count % 2 == 0)
		ft_im_even(philo);
	else
		ft_im_odd(philo);
	return ;
}

void	ft_i_think(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	pthread_mutex_lock(philo->write);
	printf("[timestamp = %ld ms] : philo %d \
is thinking\n", ft_timestamp(philo), philo->count);
	pthread_mutex_unlock(philo->write);
	return ;
}

void	ft_i_slip(t_philo *philo)
{
	if (ft_am_i_dead(philo) == 1)
		return ;
	pthread_mutex_lock(philo->write);
	printf("[timestamp = %ld ms] : philo %d \
is sleeping\n", ft_timestamp(philo), philo->count);
	pthread_mutex_unlock(philo->write);
	usleep(philo->tts * 1000);
	return ;
}
