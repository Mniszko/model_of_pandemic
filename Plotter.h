#ifndef Plot_
#define Plot_

#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>

#include "Person.h"
#include "matplotlibcpp.h"


class Plotter
{
        private:
                void scatter(std::vector<Person>&, double);
        public:
                void makeFrame(std::vector<Person>&, int, double);
                void mergeFrames(bool);

                Plotter(){}
                ~Plotter(){}
};
#endif
