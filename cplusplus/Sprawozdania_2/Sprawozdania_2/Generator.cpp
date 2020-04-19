#include "Generator.h"
#include <cstdlib>
#include <ctime>

using namespace std;

Generator::Generator()
{
	//setGenerator();
	randomNumber = rand() % 20 + 1;
}

int Generator::getData()
{
	return randomNumber;
}

void Generator::setGenerator()
{
	srand(time(NULL));
}