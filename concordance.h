/**
File: concordance.h
Description: Header file for Concordance class. Once initialized with a file name, a Concordance object can parse words from the file, store them in a vector as Word objects, and print them.
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
    std::vector<Word> m_words;  // words collected from file
    std::string m_filename;   // name of file to read
    std::vector<char> m_punctuation;    // punctuation to ignore

public:
    Concordance(std::string filename);
    void parse();
    std::string get_next_word(std::ifstream &input);
    void add_word(std::string word, int line);
    int find_word(std::string word);
    int get_current_line(std::ifstream &input);
    bool is_valid_char(char c, std::ifstream &input);
    bool is_whitespace(char c);
    bool is_punctuation(char c);
    bool is_apostrophe(char c, std::ifstream &input);
    void eat_whitespace(std::ifstream &input);
    void print();
};

/**
Function will construct a Concordance object
@param filename Name of the file used to fill Concordance
@return Concordance object
*/
Concordance::Concordance(std::string filename)
{
    m_filename = filename;

    // define all forms of punctuation
    m_punctuation.push_back('"');
    m_punctuation.push_back(',');
    m_punctuation.push_back(';');
    m_punctuation.push_back(':');
    m_punctuation.push_back('.');
    m_punctuation.push_back('?');
    m_punctuation.push_back('!');
    m_punctuation.push_back('(');
    m_punctuation.push_back(')');
    m_punctuation.push_back('/');
    m_punctuation.push_back('\\');
    m_punctuation.push_back('-');
}

/**
Function parses words from file and adds them to vector m_words
*/
void Concordance::parse()
{
    // open file stream to read
    std::ifstream file(m_filename.c_str());
    while(!file.eof())  // until end of file...
    {
        // get next word and its line number from file
        std::string word = get_next_word(file);
        int line = get_current_line(file);

        // find entry for word in vector, add latest occurence
        int word_position = find_word(word);
        if(word_position > 0)
            m_words[word_position].occurs_again_at(line);
        else    // if no entry exists, make one
            add_word(word, line);
        
        // print word
        std::cout << word << " ";
    }
    std::cout << std::endl << std::endl;
}

/**
Function collects a word from input stream
@param input Input stream for function to read
@return word as a string
*/
std::string Concordance::get_next_word(std::ifstream &input)
{
    std::string word;
    for(;;)
    {
        char c;
        input.get(c);   // read next character
        if(input.eof())
            break;  // stop at end of file
        // if not whitespace or punctuation, add char c to word
        if(is_valid_char(c, input))
            word += tolower(c);
        else
        {
            eat_whitespace(input);
            break;
        }
    }
    return word;
}

/**
Function will locate given word in vector
@param word The word to find in vector
@return Position in vector. Negative int if not found.
*/
int Concordance::find_word(std::string word)
{
    // position is negative unless match is found
    int position = -1;

    for(int i=0; i<m_words.size(); i++)
    {
        // if match is found...
        if( word == m_words[i].get_spelling())
        {
            // ...set to current position in vector
            position = i;
        }
    }
    
    return position;
}

/**
Function will add new Word object to m_words vector
@param s Word spelling
@param line Line number of word
*/
void Concordance::add_word(std::string s, int line)
{
   Word w(s, line); 
   m_words.push_back(w);
}

/**
Function will calculate line number from position in file stream
@param input File stream
@return Line number
*/
int Concordance::get_current_line(std::ifstream &input)
{
    const int LINE_LENGTH = 60;  // characters per line
    long position = input.tellg();  // current position
    int line_number;

    // if current position is at the end of current line,
    // line number = exact number of completed lines
    if(position%LINE_LENGTH == 0)
        line_number = position/LINE_LENGTH;
    // else, add 1 for current (incomplete) line
    else
        line_number = position/LINE_LENGTH + 1;

    return line_number;
}

/**
Function checks whether given character is part of a word
@param c Character to check
@return True if character is part of a word
*/
bool Concordance::is_valid_char(char c, std::ifstream &input)
{
    // check whether c is an apostrophe
    if(c=='\'')
        return(is_apostrophe(c, input));
    //check whether c is whitespace or punctuation
    else
        return(!is_whitespace(c) && !is_punctuation(c));
}


/**
Function will check whether given character is whitespace
@param c Character to check
@return True if character is whitespace
*/
bool Concordance::is_whitespace(char c)
{
    return(c==' ' || c=='\n' || c=='\t');
}

/**
Function checks whether given character is punctuation
@param c Character to check
@return If true, character is punctuation
*/
bool Concordance::is_punctuation(char c)
{
    for(int i=0; i<m_punctuation.size(); i++)
    {
        // c matches entry in punctuation vector
        if(c == m_punctuation[i])
            return true;
    }
    return false;   // no matches in vector
}

/**
Function checks whether given character is an apostrophe or single quote.
(Single quotes have punctuation or white space next to them)
@param c Character to check
@param input File stream character came from
@return True if character is an apostrophe
*/
bool Concordance::is_apostrophe(char c, std::ifstream &input)
{

    char b, d;  // characters before and after c
    input.get(d);   // get character after c

    // shift postion to read character before c
    long position = input.tellg();
    input.seekg((position - 3), std::ios::beg);  
    input.get(b);   // get character before c

    input.get(c);   // read c again to resume original position in file

    // true if b and d are NOT whitespace or punctuation
    return!(is_whitespace(b) || is_whitespace(d) || is_punctuation(b) || is_punctuation(d));
}

/**
Function consumes all whitespace and punctuation before next valid character
@param input File stream to read
*/
void Concordance::eat_whitespace(std::ifstream &input)
{
    for(;;)
    {
        char c;
        input.get(c);   // consume next character
        if(input.eof())   // stop at end of file 
            break; 
        // put character back if it's not whitespace or punctuation
        if(is_valid_char(c, input))
        {
            input.putback(c);
            break;
        }
    }
}

/**
Function prints all Word objects in m_words vector
*/
void Concordance::print()
{
    for(int i=0; i<m_words.size(); i++)
        m_words[i].print_word();
}

#endif
