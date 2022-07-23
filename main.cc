#include "City.h"
#include "Person.h"
#include "Plotter.h"
int main(int argc, char* argv[])
{
        srand(time(0));
        City city {argc, argv};
        city.evolution();
        city.painting();


        return 0;
}

