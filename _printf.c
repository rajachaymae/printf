#include "main.h"

void print_buffer(char buffer[], int *buff_indicator);

/**
 * _printf - function that produces output according to a format.
 * @format:  is a character string.
 * Return:  the number of characters printed.
 */
int _printf(const char *format, ...)
{
	if (format == NULL)
		return (-1);
	int pr = 0;
	int print_char = 0;
	int i = 0;
	int flags, width, precision, size, buff_indicator = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	va_start(list, format);
	while (format && format[i] != '\0')
	{
		if (format[i] != '%')
		{
			buffer[buff_indicator++] = format[i];
			if (buff_indicator == BUFF_SIZE)
				print_buffer(buffer, &buff_indicator);
			/* write(1, &format[i], 1);*/

			print_char++;
		}
		else
		{
			print_buffer(buffer, &buff_indicator);
			flags = get_flags(format, &i);
			width = get_width(format, &i, list);
			precision = get_precision(format, &i, list);
			size = get_size(format, &i);
			++i;
			pr = handle_print(format, &i, list, buffer, flags, width, precision, size);
			if (pr == -1)
				return (-1);
			print_char += pr;
		}
		i++;
	}
	printing(buffer, &buff_indicator);
	va_end(list);

	return (print_char);
}

/**
 * print_buffer -here we  Prints, in case of existance the buffer, the contents
 * @buffer: define an array of chars types
 * @buff_indicator: represents the length.
 */
void printing(char buffer[], int *buff_indicator)
{
	if (*buff_indicator > 0 && buff_indicator != '\0')
		write(1, &buffer[0], *buff_indicator);

	*buff_indicator = 0;
}
