/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aybiouss <aybiouss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 17:08:25 by aybiouss          #+#    #+#             */
/*   Updated: 2022/10/26 17:00:14 by aybiouss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else
	{
		if (n > 9)
		{
			ft_putnbr_fd(n / 10, fd);
		}
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

// int	main()
// {
// 	int	fd = open("text.txt", O_WRONLY | O_CREAT);
// 	if (fd < 0)
// 		printf("No file found");
// 	printf("%d\n", fd);
// 	for (int i = 0; i < 100; i++)
// 	{
// 		ft_putnbr_fd(1 + i, fd);
// 		ft_putchar_fd('\n', fd);
// 	}
// }
