#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
//cString  -> NULL
//decimal -> 0, positivo, negativo, max_int, min_int
//hexadecmal -> caso 0 -> 0, (vero lo qu printa), max unsigned int


//limits.h   -> mirarme la macro de MAX_INT MAX UNSIGNED INT

void	ft_putstr(char *str, int *size);

void	ft_putnbr(long long int num, int base, int *size);

int	ft_printf(const char *format, ... );

int	main(void)
{
	ft_printf("ft_printf\t\t\t%s\n", "toto");
	printf("ORIGINAL\t\t\t%s\n", "toto");
	ft_printf("ft_printf Magic\t\t\t%s is %d\n", "number", 42565555555555);
	printf("ORIGINAL Magic\t\t\t%s is %d\n", "number", 42565555555555);
	ft_printf("ft_printf Hexadecimal for\t%d is %x\n", 42, 42);
	printf("ORIGINAL Hexadecimal for\t%d is %x\n", 42, 42);
	return (0);
}


int	ft_printf(const char *format, ... )
{
	int	size;

	size = 0;
	va_list pointer;
	va_start(pointer, format);
	while(*format)
	{
		//comprbamos el contenido actual del puntero, y la posicion que sigue... corremos el puntero dos posiciones [símbolo '%' y el formato 's']
		if((*format == '%') && (*(format + 1) == 's') && (format += 2))
			ft_putstr(va_arg(pointer, char *), &size);
		//casteamos a un long long int, para tenero los dos, el int y el unsigned int, indicamos la base, pasamos el puntero del size
		else if(*format == '%' && *(format + 1) == 'd' && (format += 2))
			ft_putnbr((long long int)va_arg(pointer, int), 10, &size);
		else if(*format == '%' && *(format + 1) == 'x' && (format += 2))
			ft_putnbr((long long int)va_arg(pointer, unsigned int), 16, &size);
		else
			write(1, format++, 1);
	}
	return (va_end(pointer), size);
}

void	ft_putstr(char *str, int *size)
{
	if(!str)
		str = "(null)";	
	while(*str)
		*size += write(1, str++, 1);
}

void	ft_putnbr(long long int num, int base, int *size)
{
	char *str = "0123456789abcdef";

	if(num < 0)
	{
		num *= -1;
		write(1, "-", 1);
	}
	if(num >= base)
		ft_putnbr((num/base), base, size);
	*size += write(1, &str[num%base], 1);


}

/*void	ft_puthexa()
{
	
}

void	ft_putnbr(int num, int *size)
{
	char 	c;

	if(num > 9)
		ft_putnbr(num/10, size);
	c = (num % 10) + '0';
	*size += (int)write(1, &c, 1);
}*/
