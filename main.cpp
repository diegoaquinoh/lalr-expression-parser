#include <iostream>
#include <string>
#include "automate.h"

using namespace std;

int main(void) {
    string chaine;
    getline(cin, chaine);

    Automate automate(chaine);
    automate.lecture();

    return 0;
}
