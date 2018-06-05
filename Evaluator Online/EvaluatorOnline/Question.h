#ifndef QUESTION_H
#define QUESTION_H
#include<string>
#include<vector>
using namespace std;
class Question
{
private:
    string Q;
    int SA;
    string RA;
    vector<string> WA;
public:
    void ReadQ(string q);
    void ReadRA(string ra);
    void ReadWA(string wa);
    void addWA(string wa);
    string GetQ();
    string GetRA();
    string GetWA(int nr);
};

#endif // QUESTION_H
