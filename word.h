/**
File: word.h
Description: Header file for Word class.  Word object includes 3 data
        fields: spelling, number of occurences, and line numbers.
Author: Jessica Priester
Email: jessicp0249@student.vvc.edu
Date created: 12/7/2018
*/
#ifndef WORD_H
#define WORD_H

#include<iostream>
#include<vector>
#include<string>

class Word
{
private:
    std::string m_spelling;   // spelling of the word
    std::vector<int> m_line_number;   // line(s) where word appears
    int m_count;    // number of times Word appears

public:
    Word(std::string spelling, int line);
    std::string get_spelling();
    void occurs_again_at(int line);
    void print_word();

};

/**
Constructor - initializes data fields
@param spelling Spelling of the word
@param line Line number where word appears
@return Word object
*/
Word::Word(std::string spelling, int line)
{
    m_spelling = spelling;
    m_line_number.push_back(line);
    m_count = 1;    // Upon creation, word has appeared once
}

/**
Getter function returns spelling of the word
@return m_spelling string
*/
std::string Word::get_spelling()
{
    return m_spelling;
}

/**
Function increments number of times word occurs, adds new line number
@param line Line number for word's latest occurence
*/
void Word::occurs_again_at(int line)
{
    m_line_number.push_back(line);  // add new line number to vector
    m_count++;
}

/**
Function prints data fields in Word object in format:
m_spelling : m_count : m_line_number[0], ...m_line_number[n]
*/
void Word::print_word()
{
    std::cout << m_spelling << " : " << m_count << " : ";
    // Print each entry in vector m_line_number
    for(int i=0; i<m_line_number.size(); i++)
    {
        std::cout << m_line_number[i];
        // if it's the last entry, endline; else, comma
        if(i == (m_line_number.size()-1))
            std::cout << std::endl;
        else
            std::cout << ", ";
    }
}

#endif
