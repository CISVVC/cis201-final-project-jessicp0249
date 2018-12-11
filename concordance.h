/**
File: concordance.h
Description: Header file for Concordance class.
Author: Jessica Priester
Email: jessicp0249@student.vvc.edu
Date created: 12/7/2018
*/

#ifndef CONCORDANCE_H
#define CONCORDANCE_H

#include<iostream>
#include<fstream>
#include<string>
#include<cctype>
#include<vector>
#include "word.h"

class Concordance
{
private:
    std::vector<Word> m_words;
    std::string m_filename;
    std::vector<char> m_punctuation;

public:
    Concordance(std::string filename);
    void parse();
    std::string next_word(std::ifstream &input);
    void add_word(std::string word, int line);
    int find_word(std::string word);
    int get_current_line(std::ifstream &input);
    bool is_whitespace(char c);
    bool is_punctuation(char c, std::ifstream &input);
    bool is_apostrophe(char c, std::ifstream &input);
    void eat_whitespace(std::ifstream &input);
    void print();
};

// Function will construct a Concordance object
// @param filename Name of the file used to fill Concordance
// @return Concordance object
Concordance::Concordance(std::string filename)
{
    m_filename = filename;

    // define all forms of punctuation
    m_punctuation.push_back('"');
    m_punctuation.push_back(',');
    m_punctuation.push_back(';');
    m_punctuation.push_back(';');
    m_punctuation.push_back('.');
    m_punctuation.push_back('?');
    m_punctuation.push_back('(');
    m_punctuation.push_back(')');
    m_punctuation.push_back('/');
    m_punctuation.push_back('\\');
    m_punctuation.push_back('-');
}

// Function will parse words from file specified in m_filename
// Function will add words to vector m_words as Word objects
void Concordance::parse()
{
    std::ifstream file(m_filename.c_str());
    while(!file.eof())
    {
        std::string word = next_word(file);
        int line = get_current_line(file);

        int word_position = find_word(word);
        if(word_position > 0)
            m_words[word_position].occurs_again_at(line);
        else
            add_word(word, line);
        
        std::cout << word << std::endl;
    }
}

// Function will return a word from input stream
//@param input Input stream for function to read
//@return word as a string
std::string Concordance::next_word(std::ifstream &input)
{
    std::string word;
    for(;;)
    {
        char c;
        input.get(c);
        if(input.eof())
            break;
        if(!is_whitespace(c) && !is_punctuation(c, input))
            word += tolower(c);
        else
        {
            eat_whitespace(input);
            break;
        }
    }
    return word;
}

// Function will find given word in vector, return position
// @param word The word to find in vector
// @return Position in vector. Negative int if not found.
int Concordance::find_word(std::string word)
{
    for(int i=0; i<m_words.size(); i++)
    {
        if( word == m_words[i].get_spelling())
            return i;
    }
    
    // If word does not exist in vector, return negative
    int j = -1;
    return j;
}

void Concordance::add_word(std::string s, int line)
{
   Word w(s, line); 
   m_words.push_back(w);
}

int Concordance::get_current_line(std::ifstream &input)
{
    const int LINE_LENGTH = 60;  // characters in a line
    long position = input.tellg();  // current position
    int line_number;

    // if current position is at the end of current line,
    // line number = exact number of completed lines
    if(position%LINE_LENGTH == 0)
        line_number = position/LINE_LENGTH;
    // else, add 1 for the current (incomplete) line
    else
        line_number = position/LINE_LENGTH + 1;

    return line_number;
}

bool Concordance::is_whitespace(char c)
{
    return(c==' ' || c=='\n' || c=='\t');
}

// Function checks whether given character is punctuation
// @param c Character to check
// @return If true, character is punctuation
bool Concordance::is_punctuation(char c, std::ifstream &input)
{
    if(c=='\'' || c=='\'')
    {
        return(!is_apostrophe(c, input));
    }
    else
        {
            for(int i=0; i<m_punctuation.size(); i++)
            {
                if(c == m_punctuation[i])
                    return true;
            }
        }
    return false;
}

// Function checks whether given character is an apostrophe
//    or a single quote. (Single quotes have punctuation or
//    white space next to them)
// @param c Character to check
// @param input File stream character came from
// @return True if character is an apostrophe
bool Concordance::is_apostrophe(char c, std::ifstream &input)
{

    return false;

#if 0
    // if current read position is end of file
    if(input.eof())
        return false;

    long position = input.tellg();  // current read position in file
    input.seekg((position - 2), std::ios::beg);  // shift read position

    char d;
    input.get(d);   // read in character right before char c

    if(is_whitespace(d) || is_punctuation(d, input))
    {
        input.seekg(position);  // restore original position
        return false;
    }
    else
    {
       // shift position to skip over char c
        input.seekg((position + 1), std::ios::beg);
        input.get(d);
        input.seekg(position);  // restore original position
        if(is_whitespace(d) || is_punctuation(d, input))
            return false;
    }
#endif
}

void Concordance::eat_whitespace(std::ifstream &input)
{
    for(;;)
    {
        char c;
        input.get(c);
        if(input.eof()) 
            break; 
        if(!is_whitespace(c) && !is_punctuation(c, input))
        {
            input.putback(c);
            break;
        }
    }
}

void Concordance::print()
{
    for(int i=0; i<m_words.size(); i++)
        m_words[i].print_word();
}

#endif
