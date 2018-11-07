#include "network.h"
#include "random.h"
#include "simulation.h"
#include <iostream>

RandomNumbers RNG;

int main(int argc, char **argv) {
    Network net;
    Simulation sim(&net);
    int errcode = 0;
    try {
        sim.initialize(argc, argv);
        sim.run();
    } catch(TCLAP::ArgException &e) {
        std::cerr << "Error: " + e.error() + " " + e.argId();
        errcode = 2;
    }
      catch (std::invalid_argument &e) { //catch string errors thrown during the running program. Here they are treated by a display on the terminal
        std::cerr << e.what() << std::endl;
        errcode = 1;
    }
    return errcode;
}
