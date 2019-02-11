#include <iostream>

using namespace std;

#include "page_rank.hpp"
#include "connectivity_matrix.hpp"

int main() {
    PageRank *pr = new PageRank();
    pr->process();

    delete pr;
    pr = NULL;

    return 0;
}