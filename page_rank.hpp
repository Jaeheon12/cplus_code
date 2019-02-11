
#ifndef ASG1_WEB_HPP
#define ASG1_WEB_HPP

#define PROBABILITY 0.85
#define MAX_SIZE 2500

#include <iostream>

using namespace std;

class PageRank {
private:
    int readFromFile(string path, double *arrToFill);

public:
    PageRank();
    virtual ~PageRank();

    void process();
};


#endif //ASG1_WEB_HPP
