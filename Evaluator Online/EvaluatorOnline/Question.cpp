#include "Question.h"


void Question::ReadQ(string q)
{
    this->Q=q;
}

void Question::ReadRA(string ra)
{
    this->RA=ra;
}

void Question::ReadWA(string wa)
{
    this->WA.push_back(wa);
}

string Question::GetQ()
{
    return this->Q;
}

string Question::GetRA()
{
    return this->RA;
}

string Question::GetWA(int nr)
{
    return this->WA[nr];
}
void Question::addWA(string wa){
        this->WA.push_back(wa);
}
