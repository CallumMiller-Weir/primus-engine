#include <iostream>
#include "package/repository.h"

using namespace primus;

int main(int argc, char** argv) {
    Repository *config = Repository::fromDirectory("config/");
    std::string configList = config->listPackages();
    std::cout << configList << std::endl;

    return 0;
}