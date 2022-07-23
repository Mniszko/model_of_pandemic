//#include <SFML/Graphics.hpp> //SFML przydaje się w przypadku w którym działa funkcja City::paint()
#include "City.h"
//wygodnie mi jest definiować sam wykres
namespace plt = matplotlibcpp;

//konstruktor z argumentami funkcji main
City::City(int argc, char* argv[])
{
        this->testConfiguration();
        this->write = true;
        this->doFrames = true;
        this->saveN = 1;

        this->parseParameters(argc, argv);
 }

//odbijanie się od ścian
void City::cityBoundary()
{
        for (Person& man : this->people)
        {
                if (man.getx()<0 or man.getx()>boxSize)
                {
                        man.setvx(-man.getvx());
                }

                if (man.gety()<0 or man.gety()>boxSize)
                {
                        man.setvy(-man.getvy());
                }
        }
        return;
}

//poruszanie się
void City::move_people()
{
        for (Person& man : this->people)
        {
                man.setx(man.getx() + dt * man.getvx());
                man.sety(man.gety() + dt * man.getvy());
        }
        return;
}


//zmiana koloru
void City::infection()
{
        for (Person& man : this->people)
        {
                for(Person& human : this->people)
                {
                        if
                                (
                                        man.get_color() == "green" and
                                        human.get_color() == "red" and
                                        (man.get_radius()+human.get_radius()) * (man.get_radius()+human.get_radius()) >
                                        man+human
                                )
                        {
                                man.change_color();
                        }

                }
        }
        return;
}

//dodanie czasu
void City::increaseTimeR()
{
        for (Person& man : this->people)
        {
                if (man.get_color() == "red")
                {
                        man.set_timeR(man.get_timeR() + dt);
                        if (man.get_timeR() >= recoveryTime)
                        {
                                man.change_color();
                        }
                }
        }
        return;
}



void City::round()
{
        this->increaseTimeR();
        this->move_people();
        this->cityBoundary();
        this->infection();
}


//evolution wykonuje pętle po poprzednich funkcjach i rysuje wykres za pomocą klasy Plotter
void City::evolution()
{
        Plotter plot;
        for (int k=0 ; k<this->nIter ; ++k)
        {
                if (k == this->saveN-1 and this->write==true)
                {
                        this->writeToFile();
                }
                
                this->round();
		if(this->doFrames)
        	{
			plt::figure();        
        		plt::figure_size(500, 500);
        		plot.makeFrame(this->people, k, this->boxSize);
        	}
        	printSick(k);
        }
        plot.mergeFrames(this->doFrames);
}

void City::testConfiguration()
{
// ustalenie zmiennych konfiguracji testowej zostało przeniesione do parsParameters
        this->people.clear();
        Person per1 {0.1, 0.2, 0.1, 0.2, 0.02, std::string("green")};
        Person per2 {0.1, 0.1, 0.5, 0.3, 0.05, std::string("green")};
        Person per3 {0.2, 0.1, 0.3, 0.6, 0.03, std::string("red")};
        this->people.push_back(per1);
        this->people.push_back(per2);
        this->people.push_back(per3);
        //this->nPeople = 3;

        //this->nIter = 100;
        //this->saveN = nIter;
        //this->dt = 0.02;
        //this->recoveryTime = 0.5;
        //this->boxSize = 0.25;
}

void City::randomConfiguration()
{
//        this->boxSize = 1;
//        this->nIter = 50;
//        this->saveN = nIter;
//        this->recoveryTime = 0.7;
//        this->dt = 0.02;
        this->people.clear();
        for (int k=0 ; k<this->nPeople ; ++k)
        {
                double x = this->boxSize*double(rand())/double(RAND_MAX);
                double y = this->boxSize*double(rand())/double(RAND_MAX);
                double vx = (2*double(rand())/double(RAND_MAX)-1);
                double vy = (2*double(rand())/double(RAND_MAX)-1);
                double rad = 0.01+double(rand())/double(RAND_MAX)/25;
                std::string str = "green";
                if (k>int(0.9*this->nPeople))
                {
                        str = "red";
                }

                Person per {x, y, vx, vy, rad, str};
                this->people.push_back(per);
        }
}

bool City::readConfiguration()
{
        //this->people.clear();
        //this->boxSize = 1;
        //this->nIter = 50;
        //this->recoveryTime = 0.7;
        //this->dt = 0.02;
        this->people.clear();
        std::fstream file("input_configuration.txt");
        if (file.fail())
        {
                return false;
        }
        double x, y, vx, vy, rad;
        std::string str;
        char garbage;
        int iterator;
        while (true)
        {
                file >> x, file >> y, file >> vx, file >> vy, file >> rad, file >> str;
                file >> garbage;
                Person per{x, y, vx, vy, rad, str};
                this->people.push_back(per);
                if (file.fail())
                {
                        file.close();
                        return true;
                }
                ++iterator;
        }
        this->nPeople = iterator;
}

//funkcja rysująca symulację na żywo (biblioteka SFML). Nie uwzględniłem tego w Makefile
void City::painting()
{
/*
        int factor = 1000;
        sf::RenderWindow window(sf::VideoMode(boxSize*factor, boxSize*factor), "uproszczona symulacja pandemii");
//klatki na sekundę
        window.setFramerateLimit(15);
        while (window.isOpen())
        {
                round();
                sf::Event event;
                while (window.pollEvent(event))
                {
                        if (event.type == sf::Event::Closed)
                                window.close();
                }
                window.clear();
                for (int k = 0 ; k < int(people.size()) ; ++k)
                {
                        Person& human = people.at(k);
                        sf::CircleShape shape(human.get_radius()*factor);
                        if (human.get_color() == "green")
                        {
                                shape.setFillColor(sf::Color(0, 255, 0));
                        }
                        else if (human.get_color() == "red")
                        {
                                shape.setFillColor(sf::Color(255, 0, 0));
                        }
                        else
                        {
                                shape.setFillColor(sf::Color(0, 0, 255));
                        }
                        shape.setPosition((human.getx()-human.get_radius())*factor, (human.gety()-human.get_radius())*factor);
                        window.draw(shape);
                }
                window.display();
        }
*/
}
void City::parseParameters(int argc, char* argv[])
{
        //elementy konfiguracji testowej tak wpisane umożliwiają zbudowanie konfiguracji na podanych wartościach
        this->nIter = 100;
        this->saveN = 20;
        this->dt = 0.02;
        this->recoveryTime = 0.5;
        this->boxSize = 0.25;
        this->nPeople = 3;
        this->sick = 1;
        std::string conf; //zmienna potrzebna do uruchomienia konfiguracji jako ostatniej

        if (argc<3 or 16<argc)
        {
                std::cout << "poprawne polecenia to (w nawiasach podano opcje): --input{random, read, test} --nIter{liczba całkowita} --dt{liczba wymierna} --nPeople{liczba całkowita} --boxSize{liczba wymierna} --recoveryTime{liczba wymierna} --output{true, false} --doFrames{true, false}" << std::endl;
                return;
        }
//czytanie flag
        for (int k=1 ; k<argc ; ++k)
        {

                if (std::string(argv[k])=="--nIter")
                {
                        this->nIter = atof(argv[k+1]);
                }
                if (std::string(argv[k])=="--dt")
                {
                        this->dt = atof(argv[k+1]);
                }
                if (std::string(argv[k])=="--nPeople")
                {
                        this->nPeople = atof(argv[k+1]);
                        this->sick = this->nPeople * 0.1;
                        this->people = std::vector<Person>();
                }
                if (std::string(argv[k])=="--boxSize")
                {
                        this->boxSize = atof(argv[k+1]);
                }
                if (std::string(argv[k])=="--recoveryTime")
                {
                        this->recoveryTime = atof(argv[k+1]);
                }
                if (std::string(argv[k])=="--output")
                {
                        if (std::string(argv[k+1]) == "true" )
                        {
                                this->write = true;
                        } else {
                                this->write = false;
                        }
                }
                if (std::string(argv[k])=="--doFrames")
                {
                        if (std::string(argv[k+1])=="true")
                        {
                                this-> doFrames = true;
                        } else {
                                this->doFrames = false;
                        }
                }
                if (std::string(argv[k])=="--input")
                {
                        conf = std::string(argv[k+1]);
                }
        }
//uruchamianie konfiguracji
        if(conf == "random")
        {
                this->randomConfiguration();
        }
        else if(conf == "read")
        {
                this->readConfiguration();
        }
        else
        {

                this->testConfiguration();
        }
}

//zapis do pliku (możliwy do wykożystania w sprecyzowanym za pomocą zmiennej saveN)
void City::writeToFile()
{
        std::ofstream file;
        std::string plik;
        std::cout << "podać nazwę pliku zapisu: " << '\t';
        std::cin >> plik;
        file.open(plik);
        for(Person human : people)
        {
                file << human;
        }
        file.close();
}
//nieprzetestowaneXXX**********************
void City::printSick(int n)
{
	int tempSick = 0;
	for (Person human : this->people)
	{
		if (human.get_color()==std::string("red"))
		{
			++tempSick;
		}			
	}
	int tSick = tempSick-this->sick;
	
	std::cout << "razem chorych: " << this->sick << std::endl;
	std::cout << "w chwili " << this->dt*n << " zachorowało: " << tSick << std::endl;
	this->sick += tSick;
}
