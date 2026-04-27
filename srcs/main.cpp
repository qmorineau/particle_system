#include "Application.hpp"

int main(int argc, char **argv)
{
	long particles = 2000000;

	if (argc == 2)
	{
		particles = atol(argv[1]);
		if (particles <= 0)
		{
			std::cerr << "need positive number" << std::endl;
			return (0);
		}
	}
	try
	{
		Application app(argv[1]);
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}