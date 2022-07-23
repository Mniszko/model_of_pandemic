OBJS = main.o Plotter.o Person.o City.o
HEAD = Plotter.h Person.h City.h

covidSimulation: $(OBJS)
g++ -o $@ $^ -lpython3.6m

%.o:%.cc $(HEAD)
g++ -c -I/usr/include/python3.6m $<

clear:
rm *.o
rm covidSimulation
