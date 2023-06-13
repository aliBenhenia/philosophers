#include "../includes/philo.h"

// unsigned long get_time()
// {
// 	struct timeval tv;
// 	unsigned long time;
// 	gettimeofday(&tv,NULL);
// 	time = tv.tv_usec / 1000 + (tv.tv_sec * 1000);
// 	return(time);
// }

// void custom_sleep(int ms)
// {
// 	unsigned long time;

// 	time = get_time();
// 	while (get_time() - time < (unsigned long)ms)
// 		usleep(200);
// }
