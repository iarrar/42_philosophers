/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   desinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 17:30:19 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/12 17:30:22 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_ciao(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo->nphilo)
	{
		pthread_mutex_destroy(data->philo[i].lf);
		i++;
	}
	pthread_mutex_destroy(data->monitor->write);
	pthread_mutex_destroy(data->monitor->dead);
	free(data->philo->mutex);
	free(data->monitor->m_round);
	free(data->monitor->time);
	free(data->monitor->write);
	free(data->monitor->dead);
	free(data->philo);
	free(data->monitor);
}
