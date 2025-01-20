/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 21:04:43 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/07 21:04:46 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_init_values(t_data *data, char **argv, int argc)
{
	int				i;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		data->philo[i].nphilo = ft_atoi(argv[1]);
		data->philo[i].round = -1;
		if (argc == 6)
			data->philo[i].round = ft_atoi(argv[5]);
		data->philo[i].pzeros = tv.tv_sec;
		data->philo[i].pzerom = tv.tv_usec;
		data->philo[i].ttd = ft_atoi(argv[2]);
		data->philo[i].start = ft_timestamp(data->philo);
		data->philo[i].count = i;
		data->philo[i].tte = ft_atoi(argv[3]);
		data->philo[i].tts = ft_atoi(argv[4]);
		data->philo[i].die = 0;
		i++;
	}
	return (0);
}

int	ft_init_philo_mutex(t_data *data, char **argv)
{
	int	i;

	i = 0;
	data->philo->mutex = malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	data->philo->write = malloc(sizeof(pthread_mutex_t));
	data->philo->m_round = malloc(sizeof(pthread_mutex_t));
	data->philo->dead = malloc(sizeof(pthread_mutex_t));
	data->philo->time = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(data->philo->write, NULL);
	pthread_mutex_init(data->philo->m_round, NULL);
	pthread_mutex_init(data->philo->dead, NULL);
	pthread_mutex_init(data->philo->time, NULL);
	while (i < data->philo->nphilo)
	{
		pthread_mutex_init(&data->philo->mutex[i], NULL);
		data->philo[i].m_round = data->philo->m_round;
		data->philo[i].lf = &data->philo->mutex[i];
		data->philo[i].rf = &data->philo->mutex[(i + 1) \
				% data->philo[i].nphilo];
		data->philo[i].write = data->philo->write;
		data->philo[i].dead = data->philo->dead;
		data->philo[i].time = data->philo->time;
		i++;
	}
	return (0);
}

int	ft_monitor_init(t_data *data)
{
	data->monitor->write = data->philo->write;
	data->monitor->dead = data->philo->dead;
	data->monitor->time = data->philo->time;
	data->monitor->m_round = data->philo->m_round;
	return (0);
}

t_data	*ft_init_data(char **argv, int argc)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->philo = malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	data->monitor = malloc(sizeof(t_monitor));
	ft_init_values(data, argv, argc);
	ft_init_philo_mutex(data, argv);
	ft_monitor_init(data);
	return (data);
}
