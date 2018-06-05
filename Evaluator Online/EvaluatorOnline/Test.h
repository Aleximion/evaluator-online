#ifndef TEST_H
#define TEST_H
#include<vector>
#include "Question.h"
using namespace std;

class Test
{
private:
    string name;
    vector <Question> question;
public:
    int getNrQ()
    {
        int nr=question.size();
        return nr;
    }
    void AddQuestion(Question q)
    {
        question.push_back(q);
    }
    Question getQuestion(int poz)
    {
        return question[poz];
    }
    void setTestName(string name)
    {
        this->name=name;
    }
    string getTestName()
    {
        return this->name;
    }
    vector <Question> getQuestions()
    {
        return this->question;
    }
    void setQuestion(int poz,Question q){
    question[poz]=q;
    }
};

#endif // TEST_H
