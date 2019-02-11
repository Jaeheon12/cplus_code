#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

#include "connectivity_matrix.hpp"
#include "page_rank.hpp"

PageRank::PageRank() {
}

PageRank::~PageRank() {
}

/***
 * readFromFile
 *
 * paramater path : string - this string is the path for the file where there are values of matrix
 * paramater arrToFill : a pointer to an array of double - this array stores the values in the text file
 *
 * return int - the size of the array after reading from the file
 *
 * This function reads from a file where there are values of matrix
 *              ,and counts and returns its total size
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
int PageRank::readFromFile(string path, double *arrToFill) {
    ifstream fin{path};
    if (!fin.is_open()) {
        cout << "Failed to open a file : \"" << path << "\"" << endl;
        exit(1);
    }

    double curDbl;
    int size = 0;
    while (fin >> curDbl) {
        arrToFill[size++] = curDbl;
    }

    fin.close();
    return size;
}

/***
 * process
 *
 * This function conducts the Google Page Rank algorithm.
 *
 * Programmer : Jaeheon Jung
 * Date : 02/FEB/2019
 */
void PageRank::process() {
    double arr[MAX_SIZE];

    int arrSize = readFromFile("../connectivity.txt", arr);

    Matrix initMatrix(arr, arrSize);

    cout << "Input matrix : " << endl;
    cout << initMatrix << endl;

    initMatrix.getImportance();

    Matrix teleportQ(4);
    teleportQ.getTeleportation();

    initMatrix *= PROBABILITY;
    teleportQ *= 1 - PROBABILITY;

    Matrix transitionM(4);
    transitionM = initMatrix + teleportQ;


    Matrix matrixRank(4,1);
    matrixRank++;

    Matrix rankResult;
    while (true) {
        rankResult = transitionM * matrixRank;
        if (rankResult == matrixRank) {
            break;
        }
        matrixRank = rankResult;
    }

    double sum = rankResult.getSum();
    rankResult *= (1/sum);

    cout << "Rank Result " << endl;
    //cout << rankResult << endl;
    rankResult.printFormattedResult();
}

