/**
File: main.cpp
Description: This program will create and print a Concordance from a given text file.
Author: Jessica Priester
Email: jessicp0249@student.vvc.edu
Date created: 12/4/2018
*/
#include<iostream>
#include<string>
#include<vector>
#include "concordance.h"
#include "word.h"

/**
Function will prompt the User and get a file name from User input
@return String entered by User
*/
std::string get_filename()
{
    std::string filename;
//    std::cout << "Enter name of text file";
//    std::cin >> filename;
    filename = "alice.txt";
    return filename;
}

int main()
{
    std::string filename = get_filename();  // get filename (hard coded)
    Concordance conc(filename); // initialize concordance with filename
    conc.parse();   // build concordance from file
    conc.print(); // print results of concordance

    return 0;
}
