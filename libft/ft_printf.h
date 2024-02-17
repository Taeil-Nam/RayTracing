#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *str, ...);
void	ft_puthex_lower(unsigned int nbr, int *bytes);
void	ft_puthex_upper(unsigned int nbr, int *bytes);
void	ft_putunbr(unsigned int nbr, int *bytes);
void	ft_putaddr(uintptr_t ptr, int *bytes);
void	ft_putchar_pf(char c, int *bytes);
void	ft_putstr_pf(char *str, int *bytes);
void	ft_putnbr_pf(int nbr, int *bytes);
void	base_rec(unsigned int nbr, int *bytes, unsigned int b_len, char *base);

#endif
