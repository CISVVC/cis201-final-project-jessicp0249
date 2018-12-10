/**
File: word.h
Description: Header file for Word class.
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
    std::string m_spelling;
    vector<int> m_line_number;
    int m_count;

public:
    Word(std::string spelling, int line);
    std::string get_spelling();
    void occurs_again_at(int line);
    void print_word()

};

Word::Word(std::string spelling, int line)
{
    m_spelling = spelling;
    m_line_number.push_back(line);
    m_count = 1;
}

std::string Word::get_spelling()
{
    return m_spelling;
}

void Word::occurs_again_at(int line)
{
    m_line_number.push_back(line);
    m_count++;
}

void Word::print_word()
{
    std::cout << m_spelling << " : " << m_count << " : ";
    for(int i=0; i<m_line_number.size(); i++)
    {
        std::cout << m_line_number[i];
        if(i == (m_line_number.size()-1))
            std::cout << std::endl;
        else
            std::cout << ", ";
    }
}

#endif
