/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iarrar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:22:26 by iarrar            #+#    #+#             */
/*   Updated: 2023/10/04 21:22:28 by iarrar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>

typedef struct s_philo
{
	int				nphilo;
	long int		pzeros;
	long int		pzerom;
	long int		start;
	int				die;
	int				count;
	int				ttd;
	int				tts;
	int				tte;
	int				round;
	int				meal_left;
	pthread_mutex_t	*lf;
	pthread_mutex_t	*rf;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*m_round;
	pthread_mutex_t	*mml;
	pthread_mutex_t	*write;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*time;
	pthread_t		tid;
}	t_philo;

typedef struct s_monitor
{
	pthread_mutex_t	*m_round;
	pthread_mutex_t	*time;
	pthread_mutex_t	*dead;
	pthread_mutex_t	*write;
	pthread_t		tid;
}	t_monitor;

typedef struct s_data
{
	t_monitor	*monitor;
	t_philo		*philo;
}	t_data;

void		*routine(void *arg);
void		ft_ciao(t_data *data);
void		*ft_monitor(void *arg);
int			ft_hungry(t_data *data);
int			ft_atoi(const char *str);
void		ft_bandb(t_philo *philo);
void		ft_im_odd(t_philo *philo);
void		ft_i_slip(t_philo *philo);
void		ft_eating(t_philo *philo);
void		ft_im_even(t_philo *philo);
void		ft_i_think(t_philo *philo);
long int	ft_timestamp(t_philo *philo);
int			ft_am_i_dead(t_philo *philo);
int			ft_monitor_init(t_data *data);
int			ft_anyone_dead(t_philo *philo);
void		ft_kill_them_all(t_data *data);
int			ft_time_left(t_data *data, int i);
t_data		*ft_init_data(char **argv, int argc);
int			ft_init_philo_mutex(t_data *data, char **argv);
int			ft_init_values(t_data *data, char **argv, int argc);

#endif
