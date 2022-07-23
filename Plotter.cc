#include "Plotter.h"

namespace plt = matplotlibcpp;


void Plotter::scatter(std::vector<Person>& people, double sizeb)
{
        
        std::vector<double> x, y;
        double factor = 545;
        plt::xlim(double(0), sizeb);
        plt::ylim(double(0), sizeb);
        for (Person human : people)
        {
                x.push_back(human.getx());
                y.push_back(human.gety());
                
                plt::scatter(x, y, (human.get_radius()*factor/sizeb)*(human.get_radius()*factor/sizeb), {{"color", human.get_color()}});
                x.clear();
                y.clear();

        }
        
        return;
}
//funkcja zapisująca plik
void Plotter::makeFrame(std::vector<Person>& people, int n, double sizeb)
{
        this->scatter(people, sizeb);
        std::stringstream name;
        int n1 = n/1000;
        int n2 = n/100-n1*10;
        int n3 = n/10-n2*10-n1*100;
        int n4 = n-n3*10-n2*100-n1*1000;
        name << "frame_" << n1 << n2 << n3 << n4 << ".png";
        std::cout << n << std::endl;
        plt::save(name.str());
        return;
}

void Plotter::mergeFrames(bool boole)
{
        if (!boole){return;}
        else
        {
        std::system("mkdir plots");
        std::system("mv *.png ./plots/");
        std::system("python3 mergeFrames.py");
        return;
        }
}
