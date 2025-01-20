/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:21:35 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/12 14:08:55 by adrienmori       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// regler le number of time each philo has to eat

int	main(int argc, char **argv)
{
	int		i;
	t_data	*data;

	i = 0;
	if (argc < 5 || argc > 6)
		return (0);
	data = ft_init_data(argv, argc);
	pthread_create(&data->monitor->tid, NULL, &ft_monitor, data);
	while (i < ft_atoi(argv[1]))
	{
		pthread_create(&data->philo[i].tid, NULL, &routine, &data->philo[i]);
		i++;
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
	{
		pthread_join(data->philo[i].tid, NULL);
		i++;
	}
	pthread_join(data->monitor->tid, NULL);
	ft_ciao(data);
	free(data);
	return (0);
}
