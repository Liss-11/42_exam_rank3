#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <stdarg.h>
//cString  -> NULL
//decimal -> 0, positivo, negativo, max_int, min_int
//hexadecmal -> caso 0 -> 0, (vero lo qu printa), max unsigned int


//limits.h   -> mirarme la macro de MAX_INT MAX UNSIGNED INT

ssize_t	ft_putstr(char *str, int len);

void	ft_putnbr(int num, int *size);

int	ft_printf(const char *format, ... );

int	main(void)
{
	ft_printf("%s\n", "toto");
	printf("ORIGINAL %s\n", "toto");
	ft_printf("Magic %s is %d\n", "number", 4256);
	printf("ORIGINAL Magic %s is %d\n", "number", 4256);
//	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
//	printf("ORIGINAL Hexadecimal for %d is %x\n", 42, 42);

	return (0);
}


int	ft_printf(const char *format, ... )
{
	int	size;

	size = 0;
	va_list ap;
	va_start(ap, format);
	while(*format)
	{
		//comprbamos el contenido actual del puntero, y la posicion que sigue... corremos el puntero dos posiciones [símbolo '%' y el formato 's']
		if((*format == '%') && (*(format + 1) == 's') && (format += 2))
			size += (int)ft_putstr(va_arg(ap, char *), 0);
		//casteamos el resultado a (int), pasamos ap -> indicando que sera un (char *), y pasamos (len=0)
		else if(*format == '%' && *(format + 1) == 'd' && (format += 2))
			ft_putnbr(va_arg(ap, int), &size);
		//else if
		else
			write(1, format++, 1);

	}
	return (va_end(ap), size);

}

ssize_t	ft_putstr(char *str, int len)
{
	//si "str" no es NULL, si "str[len]" no es == '\0', avanzamos una posicion, aunmentando "len"
	while(str && str[len] && ++len);
	//un write, si todo ha ido bien, devueve el nubero de bytes escritos (devuelve un ssize_t, que puede ser (-1), si ha pasado un error)
	return (str ? write(1, str, len) : write(1, "(null)", 6));
}

/*int	ft_puthexa()
{

}*/

void	ft_putnbr(int num, int *size)
{
	char 	c;

	if(num > 9)
		ft_putnbr(num/10, size);
	c = (num % 10) + '0';
	*size += (int)write(1, &c, 1);
}
