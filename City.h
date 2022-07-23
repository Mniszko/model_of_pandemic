#ifndef Klasa_
#define Klasa_

#include <cstdlib>
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include "Person.h"
#include "Plotter.h"

class City
{
        private:
                int nIter;
                std::vector<Person> people;
                double dt;
                double boxSize;
                double recoveryTime;

                bool write;
                bool doFrames;
                int nPeople;
                int saveN;

		int sick;

                void cityBoundary();
                void move_people();
                void infection();
                void increaseTimeR();
                void testConfiguration();
                void randomConfiguration();
                bool readConfiguration();

                void parseParameters(int, char* argv[]);
                void writeToFile();
                void printSick(int);
        public:
                void round();
                void evolution();

//akcesory
                int getnIter()
                {return this->nIter;}
                double getdt()
                {return this->dt;}
                double getboxSize()
                {return this->boxSize;}
                double getrecoveryTime()
                {return this->recoveryTime;}

                int getPeople()
                {return int(this->people.size());}
                void setnIter(int n)
                {this->nIter = n;return;}
                void setdt(double n)
                {this->dt = n;return;}
                void setboxSize(double n)
                {this->boxSize = n;return;}
                void setrecoveryTime(double n)
                {this->recoveryTime = n;return;}
//konstruktor i destruktor
                City(){}
                City(int, char* argv[]);
                ~City(){};

//funkcja używana tylko wewnątrz biblioteki SFML (zakomentowanej)
                void painting();
};
#endif
