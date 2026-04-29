#include "Application.hpp"

int main(int argc, char **argv)
{
	try
	{
		char *arg = NULL;
		if (argc > 1)
			arg = argv[1];
		Application app(arg);
		app.run();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}