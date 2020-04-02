#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "protein.h"
using namespace std;

//function to find max of two numbers
int max(int a, int b) {
    if (a > b)
        return a;
    else
        return b;
}
//function that finds LCS sourced from "https://www.geeksforgeeks.org/cpp-program-for-longest-common-subsequence/"
int LCS (string p1, string p2, int x, int y) { 
   int N[x + 1][y + 1];//an array to that is built bottom up
   
   for (int i = 0; i <= x; i++) {
       for(int j = 0; j <= y; j++) {
           if (i == 0 || j == 0)
                N[i][j] = 0;
            else if (p1[i -1] == p2[j - 1])
                N[i][j] = N[i - 1][j-1] + 1;
            else
                N[i][j] = max(N[i - 1][j], N[i][j - 1]);
       }
   }
   
   return N[x][y];//contains length of LCS
}

int main() {
    ifstream fin; //input stream variable
    string temp_s; //string to read in input data
    protein temp_p; //temporary protein structure to read in data
    int temp_i = 0;
    vector<protein> proteins; //array that holds all protein strings

    fin.open("tulp3_relatives.txt"); //opens the file and checks for error
    if (fin.fail()) {
        cout << "Failed to open file" << endl;
        exit(EXIT_FAILURE);
    }

    if(fin) { //reads in each protein sequence
        while(getline(fin, temp_s)) {
            if (temp_i == 0) {//reads in protein title
                temp_p.protein_title = temp_s;
                ++temp_i;
            }
            else if (temp_i == 1) {//reads in protein sequence
                temp_p.protein_seq = temp_s;
                ++temp_i;
            }
            else { //adds the protein to the array and skips the blank lines
                temp_i = 0;
                proteins.push_back(temp_p);
                //cout << temp_p.protein_title << endl << temp_p.protein_seq << endl << endl;
            }
        }
    }

    for (unsigned int i = 0; i < proteins.size(); ++i) { //compares each protein sequence to each other
        for (unsigned int j = i; j < proteins.size(); ++j) { //j = i so that sequences aren't repeatedly compared. Each sequence is compared to each other one exactly once
            if (i != j) {
                cout << "LCS of proteins: " << endl;
                cout << proteins.at(i).protein_title << endl;
                cout << proteins.at(j).protein_title << endl;
                cout << " = " << LCS(proteins.at(i).protein_seq, proteins.at(j).protein_seq, proteins.at(i).protein_seq.length(), proteins.at(j).protein_seq.length()) << endl << endl;
            }
        }
    }

    fin.close();
    return 0;
}

