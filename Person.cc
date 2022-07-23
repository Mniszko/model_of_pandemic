#include "Person.h"

// proste akcesory są zdefiniowane w piku Person.h

Person::Person(double xx, double yy, double vxx, double vyy, double rad, std::string str)
{
        this->x = xx;
        this->y = yy;

        this->vx = vxx;
        this->vy = vyy;

        this->radius = rad;
        this->color = str;
        this->timeR = 0;
}



void Person::change_color()
{

        if (this->color == "green")
        {
                this->color = "red";
                return;
        }
        else if (color == "red")
        {
                this->color = "blue";
                return;
        }
        else {return;}
}

double Person::operator+(const Person& human)
{
        return (this->x-human.x)*(this->x-human.x)+(this->y-human.y)*(this->y-human.y);
}

std::ostream& operator<<(std::ostream& os, const Person man)
{
        os << man.x << ' '
           << man.y << ' '
           << man.vx << ' '
           << man.vy << ' '
           << man.radius << ' '
           << man.color << ' '
           << std::endl;
        return os;
}
