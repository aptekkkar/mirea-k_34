#include "cl_screen.h"

cl_screen::cl_screen(cl_base* p_head_object) : cl_base(p_head_object, "cl_screen") // параметризированный конструктор объекта класса cl_screen
{
}

void cl_screen::print_message(std::string& message) // метод вывода сообщения
{
	if (!message.empty()) std::cout << std::endl << message;
}
