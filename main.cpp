#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

#include "database.hpp"
#include "models.hpp"
#include "exceptions.hpp"


using namespace std;


void manual_run() {}


int main() {
    init_database();
    manual_run();
    save_database();
}
