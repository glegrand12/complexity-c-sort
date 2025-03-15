#include <stdlib.h>
#include <time.h>
#include "test_recherche.h"

int main() {
    srand(time(NULL));  // Initialize random seed
    tester_recherche_elements();
    return 0;
}

