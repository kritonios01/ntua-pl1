#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <climits>

using namespace std;

char decode_letter (char c, int distance) 
{
    int letter;
    char upp_or_low;
    if ('a' <= c && c <= 'z') upp_or_low = 'a';
    else if ('A' <= c && c <= 'Z') upp_or_low = 'A';
    else return c;

    letter = c - upp_or_low;
    letter = (letter + distance) % 26;
    c = letter + upp_or_low;
    return c;
}

string decode_word (string s, int distance)
{
    string decoded = "";
    for (int i = 0; s[i] != '\0'; i++)
        decoded += decode_letter (s[i], distance);
    return decoded;
}

double entropy (string s)
{
    double let_freqs[26] = {0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015, 
                           0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749, 
                           0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758, 
                           0.00978, 0.02360, 0.00150, 0.01974, 0.00074};

    //calculate letter frequency in string
    int total_letter_count = 0;
    int letter_count[26];
    for (int i = 0; i < 26; i++) 
        letter_count[i] = 0;

    for (int i = 0; s[i] != '\0'; i++)
    {
        char c = s[i];
        if ('a' <= c && c <= 'z') letter_count[c - 'a'] ++;
        else if ('A' <= c && c <= 'Z') letter_count[c - 'A'] ++;
        else continue;
        total_letter_count ++;
    }

    double letter_freqs_in_s[26]; 
    for (int i = 0; i < 26; i++)
        letter_freqs_in_s[i] = double(letter_count[i]) / total_letter_count; 

    double entropy = 0.0;
    for (int i = 0; i < 26; i++)
        entropy -= log(let_freqs[i]) * letter_freqs_in_s[i];  
    return entropy;
}

string decode_message (string message)
{
    string best_decoding_attempt;
    double min_entropy = INT_MAX;

    for (int i = 0; i < 26; i++)
    {
        string decoding_attempt = decode_word (message, i);
        double entr = entropy (decoding_attempt);
        if (entr < min_entropy)
        {
            min_entropy = entr;
            best_decoding_attempt = decoding_attempt;
        }
        //cout << decoding_attempt << "    " << entr << endl;
    }
    return best_decoding_attempt;
}

int main (int argc, char** argv)
{
    string filename = argv[1];
    ifstream text(filename);
    stringstream buffer;
    buffer << text.rdbuf();
    string message = buffer.str();
    string dec = decode_message(message);
    cout << dec << endl;
}