#ifndef Person_
#define Person_

#include <string>
#include <cmath>
#include <vector>
#include <iostream>

//#pragma once

class Person
{
        private:
                double x, y;
                double vx, vy;
                double radius;
                std::string color;
                double timeR;


        public:
                void setx(double xx)
                {x = xx;return;}
                void sety(double yy)
                {y = yy;return;}
                void setvx(double vxx)
                {vx = vxx;return;}
                void setvy(double vyy)
                {vy = vyy;return;}

                double getx()
                {return x;}
                double gety()
                {return y;}
                double getvx()
                {return vx;}
                double getvy()
                {return vy;}

                void change_radius (double rad)
                {radius = rad;}
                std::string get_color ()
                {return color;}
                double get_radius ()
                {return radius;}
                void set_timeR(double tim)
                {timeR = tim;return;}
                double get_timeR()
                {return timeR;}



                void change_color (); //zielony>czerwony>niebieski

                Person(double, double, double, double, double, std::string);
                ~Person(){};

//operatory

                double operator+(const Person &);
                friend std::ostream& operator<<(std::ostream&, const Person);
};

#endif
