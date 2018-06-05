#include <SFML/Graphics.hpp>
#include<iostream>
#include "Test.h"
#include "Entity.h"
#include <vector>
#include <fstream>
#include "Question.h"
#include "Button.h"

#include "MouseEvents.h"

using namespace std;

fstream fin_Tests;

vector <Entity> entities;

vector <Test> tests;


//variabile si functii globale pt meniul profesorului
bool t_menu=false;
bool solve_menu=false,quest_menu=false,rasp_input=false,rasp_apasat=false;
bool user_input=false;
bool m_apasat=false;
int type=0,input_text_size,scor,nr_intrebare_rasp;
int nr_test,nr_intrebare, pozx_input,pozy_input;
string input_text;
string rasp1="raspuns",rasp2="raspuns",rasp3="raspuns",rasp4="raspuns",rasp5="raspuns";





sf::Texture questions[6];
sf::Texture Elev_1, Elev_2, Profesor_1, Profesor_2,Elev_background,Profesor_background,Add_1,Add_2,Back_1,Back_2;
sf::Texture Blank_1,Blank_2,Forward_1,Forward_2,Blank_background,Blank_background_2;
sf::Texture punctaj0,punctaj20,punctaj40,punctaj60,punctaj80,punctaj100;
sf::Font font;
void LoadTextures()
{
    if(!questions[1].loadFromFile("Intrebare1.jpg")) cout<<"Can't load the first texture!"<<'\n';
    if(!questions[2].loadFromFile("Intrebare2.jpg")) cout<<"Can't load the second texture!"<<'\n';
    if(!questions[3].loadFromFile("Intrebare3.jpg")) cout<<"Can't load the second texture!"<<'\n';
    if(!questions[4].loadFromFile("Intrebare4.jpg")) cout<<"Can't load the second texture!"<<'\n';
    if(!questions[5].loadFromFile("Intrebare5.jpg")) cout<<"Can't load the second texture!"<<'\n';
    if(!Elev_1.loadFromFile("Elev_1.jpg")) cout<<"Can't load the third texture!"<<'\n';
    if(!Elev_2.loadFromFile("Elev_2.jpg")) cout<<"Can't load the fourth texture!"<<'\n';
    if(!Profesor_1.loadFromFile("Profesor_1.jpg")) cout<<"Can't load the fifth texture!"<<'\n';
    if(!Profesor_2.loadFromFile("Profesor_2.jpg")) cout<<"Can't load the sixth texture!"<<'\n';
    if(!Elev_background.loadFromFile("MenuElev.jpg")) cout<<"Can't load the seventh texture!"<<'\n';
    if(!Profesor_background.loadFromFile("MenuProfesor.jpg")) cout<<"Can't load the eighth texture!"<<'\n';
    if(!Add_1.loadFromFile("Add_1.jpg")) cout<<"Can't load the ninth texture!"<<'\n';
    if(!Add_2.loadFromFile("Add_2.jpg")) cout<<"Can't load the tenth texture!"<<'\n';
    if(!Back_1.loadFromFile("Back_1.png")) cout<<"Can't load the eleventh texture!"<<'\n';
    if(!Back_2.loadFromFile("Back_2.png")) cout<<"Can't load the twelfth texture!"<<'\n';
    if(!Blank_1.loadFromFile("Blank_1.jpg")) cout<<"Can't load the thirteenth texture!"<<'\n';
    if(!Blank_2.loadFromFile("Blank_2.jpg")) cout<<"Can't load the fourteenth texture!"<<'\n';
    if(!Forward_1.loadFromFile("Forward_1.png")) cout<<"Can't load the fifteenth texture!"<<'\n';
    if(!Forward_2.loadFromFile("Forward_2.png")) cout<<"Can't load the fifteenth texture!"<<'\n';
    if(!Blank_background.loadFromFile("Blank_background.jpg")) cout<<"Can't load the sixteenth texture!"<<'\n';
    if(!Blank_background_2.loadFromFile("Blank_background_2.jpg")) cout<<"Can't load the seventeenth texture!"<<'\n';
    if(!punctaj0.loadFromFile("Punctaj0.jpg")) cout<<"Cant't load the 18th texture!"<<'\n';
    if(!punctaj20.loadFromFile("Punctaj20.jpg")) cout<<"Can't load the 19th texture!"<<'\n';
    if(!punctaj40.loadFromFile("Punctaj40.jpg")) cout<<"Can't load the 20th texture!"<<'\n';
    if(!punctaj60.loadFromFile("Punctaj60.jpg")) cout<<"Can't load the 21th texture!"<<'\n';
    if(!punctaj80.loadFromFile("Punctaj80.jpg")) cout<<"Can't load the 22th texture!"<<'\n';
    if(!punctaj100.loadFromFile("Punctaj100.jpg")) cout<<"Can't load the 23th texture!"<<'\n';

    if(!font.loadFromFile("phagspab.ttf")) cout<<"Can't load the font!"<<'\n';
}

void MainMenu();
void ProfesorMenu();
void ElevMenu();
void ProfesorReadTest(int nr_test);
void ElevSolveTest(int nr_test);
void ProfesorMenuButtons();
void Calculeaza();

void LoadTests()
{
    fin_Tests.open("Tests.txt",ios::in);
    char stringg[101];
    do
    {
        fin_Tests.getline(stringg,101);
        Test t;
        t.setTestName(stringg);
        for(int j=1; j<=5; ++j)
        {
            fin_Tests.getline(stringg,101);
            Question q;
            q.ReadQ(stringg);
            fin_Tests>>stringg;
            q.ReadRA(stringg);
            for(int k=1; k<=5; ++k)
            {
                fin_Tests>>stringg;
                q.ReadWA(stringg);
            }
            fin_Tests.get();
            t.AddQuestion(q);
        }
        tests.push_back(t);
    }
    while(fin_Tests);
    fin_Tests.clear();
    fin_Tests.close();
    tests.pop_back();
}

void Save()
{
    fin_Tests.open("Tests.txt",ios::out);
    for(int i=0; i<(int)tests.size(); ++i)
    {
        fin_Tests<<tests[i].getTestName()<<'\n';
        for(int j=0; j<5; ++j)
        {
            fin_Tests<<tests[i].getQuestion(j).GetQ()<<'\n';
            fin_Tests<<tests[i].getQuestion(j).GetRA()<<' ';
            for(int k=0; k<5; ++k)
            {
                fin_Tests<<tests[i].getQuestion(j).GetWA(k);
                if(k<4) fin_Tests<<' ';
            }
            fin_Tests<<'\n';
        }
    }
    fin_Tests.close();
}

int main()
{
    LoadTests();
    LoadTextures();
    sf::RenderWindow window(sf::VideoMode(1072, 721), "Evaluator");
    //window.setFramerateLimit(60);
    MainMenu();
    while (window.isOpen())
    {

        sf::Vector2i poz=sf::Mouse::getPosition(window);
        MouseEvents::mouse_x=poz.x;
        MouseEvents::mouse_y=poz.y;
        //cout<<poz.x<<" "<<poz.y<<endl;
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // cout<<"AICI!!"<<endl;
                window.close();
            }
            else if(event.type==sf::Event::MouseButtonPressed)
            {
                MouseEvents::released=false;
                MouseEvents::pressed=true;
            }
            else if(event.type==sf::Event::MouseButtonReleased)
            {
                MouseEvents::released=true;
                MouseEvents::pressed=true;
            }
            else if(user_input&&event.type==sf::Event::TextEntered)
            {
                if(event.text.unicode==13)
                {
                    user_input=false;
                    if(type==1)
                    {
                        Question q=tests[nr_test].getQuestion(nr_intrebare);
                        q.ReadQ(input_text);
                        tests[nr_test].setQuestion(nr_intrebare,q);
                    }
                    else if(type==0)
                    {
                        Question q=tests[nr_test].getQuestion(nr_intrebare);
                        q.ReadRA(input_text);
                        tests[nr_test].setQuestion(nr_intrebare,q);
                    }
                    else if(type==2)
                    {
                        tests[nr_test].setTestName(input_text);
                    }
                    input_text.clear();

                }
                else if(event.text.unicode==32&&type) input_text+=(char) event.text.unicode;
                else if(event.text.unicode>=65&&event.text.unicode<=90||(event.text.unicode>=97&&event.text.unicode<=122)||(event.text.unicode>=48&&event.text.unicode<=57)) input_text+=(char)event.text.unicode;
            }
            else if(rasp_input&&event.type==sf::Event::TextEntered)
            {

                if(event.text.unicode==13)
                {
                    rasp_input=false;
                    if(nr_intrebare_rasp==0) rasp1=input_text;
                    if(nr_intrebare_rasp==1) rasp2=input_text;
                    if(nr_intrebare_rasp==2) rasp3=input_text;
                    if(nr_intrebare_rasp==3) rasp4=input_text;
                    if(nr_intrebare_rasp==4) rasp5=input_text;
                    input_text.clear();
                }
                else if(event.text.unicode==32) input_text+=(char) event.text.unicode;
                else if(event.text.unicode>=65&&event.text.unicode<=90||(event.text.unicode>=97&&event.text.unicode<=122)||(event.text.unicode>=48&&event.text.unicode<=57)) input_text+=(char)event.text.unicode;
            }
        }
        window.clear();
        for(int i=0; i<(int)entities.size(); ++i)
        {
            window.draw(entities[i]);
            entities[i].Update();
        }
        if(t_menu)
        {
            sf::Text tests_text;
            tests_text.setFont(font);
            tests_text.setCharacterSize(40);
            tests_text.setColor(sf::Color::White);
            for(int i=0; i<(int)tests.size(); ++i)
            {
                tests_text.setString(tests[i].getTestName());
                tests_text.setPosition(100,200+65*i);
                window.draw(tests_text);
            }
        }

        else if(solve_menu)
        {

            sf::Text text_intrebari[5],text_rasp[5],nume_test;
            nume_test.setFont(font);
            nume_test.setCharacterSize(30);
            nume_test.setString(tests[nr_test].getTestName());
            nume_test.setPosition(480,572);
            text_intrebari[0].setPosition(70,105);
            text_intrebari[1].setPosition(410,105);
            text_intrebari[2].setPosition(752,105);
            text_intrebari[3].setPosition(239,348);
            text_intrebari[4].setPosition(582,348);
            text_rasp[0].setPosition(206,192);
            text_rasp[1].setPosition(549,192);
            text_rasp[2].setPosition(890,192);
            text_rasp[3].setPosition(377,434);
            text_rasp[4].setPosition(719,434);
            for(int i=0; i<5; ++i)
            {
                text_intrebari[i].setString(tests[nr_test].getQuestion(i).GetQ());
                if(user_input&&type==1&&i==nr_intrebare) text_intrebari[i].setString("");
                text_intrebari[i].setCharacterSize(10);
                text_intrebari[i].setFont(font);
                text_intrebari[i].setColor(sf::Color::White);
                text_rasp[i].setString(tests[nr_test].getQuestion(i).GetRA());
                if(user_input&&type==0&&i==nr_intrebare) text_rasp[i].setString("");
                text_rasp[i].setCharacterSize(10);
                text_rasp[i].setFont(font);
                window.draw(text_intrebari[i]);
                window.draw(text_rasp[i]);
            }
            if(user_input&&type==2) nume_test.setString("");
            window.draw(nume_test);
            if(MouseEvents::pressed)
            {
                if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                {
                    int pozmx=MouseEvents::mouse_x;
                    int pozmy=MouseEvents::mouse_y;
                    input_text_size=10;
                    if(pozmx>=64&&pozmx<=300&&pozmy>=76&&pozmy<=139)
                    {
                        user_input=true;
                        type=true;
                        nr_intrebare=0;
                        pozx_input=70;
                        pozy_input=105;
                    }
                    else if(pozmx>=407&&pozmx<=642&&pozmy>=76&&pozmy<=139)
                    {
                        user_input=true;
                        type=true;
                        nr_intrebare=1;
                        pozx_input=410;
                        pozy_input=105;
                    }
                    else if(pozmx>=749&&pozmx<=985&&pozmy>=76&&pozmy<=139)
                    {
                        user_input=true;
                        type=true;
                        nr_intrebare=2;
                        pozx_input=752;
                        pozy_input=105;
                    }
                    else if(pozmx>=236&&pozmx<=471&&pozmy>=319&&pozmy<=380)
                    {
                        user_input=true;
                        type=true;
                        nr_intrebare=3;
                        pozx_input=239;
                        pozy_input=348;
                    }
                    else if(pozmx>=578&&pozmx<=813&&pozmy>=319&&pozmy<=380)
                    {
                        user_input=true;
                        type=true;
                        nr_intrebare=4;
                        pozx_input=582;
                        pozy_input=348;
                    }
                    else if(pozmx>=204&&pozmx<=301&&pozmy>=164&&pozmy<=228)
                    {
                        user_input=true;
                        type=false;
                        nr_intrebare=0;
                        pozx_input=206;
                        pozy_input=192;
                    }
                    else if(pozmx>=545&&pozmx<=644&&pozmy>=164&&pozmy<=228)
                    {
                        user_input=true;
                        type=false;
                        nr_intrebare=1;
                        pozx_input=549;
                        pozy_input=192;
                    }
                    else if(pozmx>=888&&pozmx<=985&&pozmy>=164&&pozmy<=228)
                    {
                        user_input=true;
                        type=false;
                        nr_intrebare=2;
                        pozx_input=890;
                        pozy_input=192;
                    }
                    else if(pozmx>=374&&pozmx<=472&&pozmy>=405&&pozmy<=469)
                    {
                        user_input=true;
                        type=false;
                        nr_intrebare=3;
                        pozx_input=377;
                        pozy_input=434;
                    }
                    else if(pozmx>=716&&pozmx<=814&&pozmy>=405&&pozmy<=469)
                    {
                        user_input=true;
                        type=false;
                        nr_intrebare=4;
                        pozx_input=719;
                        pozy_input=434;
                    }
                    else if(pozmx>=477&&pozmx<=709&&pozmy>=559&&pozmy<=621)
                    {
                        user_input=true;
                        type=2;
                        pozx_input=480;
                        pozy_input=572;
                        input_text_size=30;
                    }
                }
            }
            //cout<<nr_intrebare_rasp<<' '<<input_text<<endl;
            if(user_input)
            {
                sf::Text text;
                text.setPosition(pozx_input,pozy_input);
                text.setString(input_text);
                text.setFont(font);
                text.setCharacterSize(input_text_size);
                window.draw(text);
            }
        }
        if(quest_menu)
        {
            sf::Text nume_test;

            nume_test.setFont(font);
            nume_test.setCharacterSize(50);
            nume_test.setString(tests[nr_test].getTestName()+":");
            nume_test.setPosition(50,50);

            sf::Text text_quest[5];
            text_quest[0].setFont(font);
            text_quest[0].setCharacterSize(20);
            text_quest[0].setPosition(410,31);
            text_quest[0].setString(tests[nr_test].getQuestion(0).GetQ());
            text_quest[1].setFont(font);
            text_quest[1].setCharacterSize(20);
            text_quest[1].setPosition(410,168);
            text_quest[1].setString(tests[nr_test].getQuestion(1).GetQ());
            text_quest[2].setFont(font);
            text_quest[2].setCharacterSize(20);
            text_quest[2].setPosition(410,305);
            text_quest[2].setString(tests[nr_test].getQuestion(2).GetQ());
            text_quest[3].setFont(font);
            text_quest[3].setCharacterSize(20);
            text_quest[3].setPosition(410,437);
            text_quest[3].setString(tests[nr_test].getQuestion(3).GetQ());
            text_quest[4].setFont(font);
            text_quest[4].setCharacterSize(20);
            text_quest[4].setString(tests[nr_test].getQuestion(4).GetQ());
            text_quest[4].setPosition(410,573);

            sf::Text rasp_text[5];

            rasp_text[0].setFont(font);
            rasp_text[0].setCharacterSize(20);
            rasp_text[0].setString(rasp1);
            if(rasp_input&&nr_intrebare_rasp==0) rasp_text[0].setString("");
            rasp_text[0].setPosition(432,100);
            rasp_text[1].setFont(font);
            rasp_text[1].setCharacterSize(20);
            rasp_text[1].setString(rasp2);
            if(rasp_input&&nr_intrebare_rasp==1) rasp_text[1].setString("");
            rasp_text[1].setPosition(432,238);
            rasp_text[2].setFont(font);
            rasp_text[2].setCharacterSize(20);
            rasp_text[2].setString(rasp3);
            if(rasp_input&&nr_intrebare_rasp==2) rasp_text[2].setString("");
            rasp_text[2].setPosition(432,373);
            rasp_text[3].setFont(font);
            rasp_text[3].setCharacterSize(20);
            rasp_text[3].setString(rasp4);
            if(rasp_input&&nr_intrebare_rasp==3) rasp_text[3].setString("");
            rasp_text[3].setPosition(432,508);
            rasp_text[4].setFont(font);
            rasp_text[4].setCharacterSize(20);
            rasp_text[4].setString(rasp5);
            if(rasp_input&&nr_intrebare_rasp==4) rasp_text[4].setString("");
            rasp_text[4].setPosition(432,645);



            if(MouseEvents::pressed)
            {

                if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!m_apasat)
                {
                    m_apasat=true;
                    int pozmx=MouseEvents::mouse_x;
                    int pozmy=MouseEvents::mouse_y;
                    if(pozmx>=428&&pozmx<=661&&pozmy>=81&&pozmy<=143)
                    {
                        rasp_input=true;
                        pozx_input=432;
                        pozy_input=100;
                        nr_intrebare_rasp=0;
                        input_text_size=20;
                    }
                    else if(pozmx>=428&&pozmx<=661&&pozmy>=217&&pozmy<=277)
                    {
                        rasp_input=true;
                        pozx_input=432;
                        pozy_input=238;
                        nr_intrebare_rasp=1;
                    }
                    else if(pozmx>=428&&pozmx<=661&&pozmy>=354&&pozmy<=415)
                    {
                        rasp_input=true;
                        pozx_input=432;
                        pozy_input=373;
                        nr_intrebare_rasp=2;
                    }
                    else if(pozmx>=428&&pozmx<=661&&pozmy>=488&&pozmy<=549)
                    {
                        rasp_input=true;
                        pozx_input=432;
                        pozy_input=508;
                        nr_intrebare_rasp=3;
                    }
                    else if(pozmx>=428&&pozmx<=661&&pozmy>=625&&pozmy<=687)
                    {
                        rasp_input=true;
                        pozx_input=432;
                        pozy_input=645;
                        nr_intrebare_rasp=4;
                    }
                }
                else if(MouseEvents::released) m_apasat=false;

            }

            for(int i=0; i<5; ++i)
            {
                window.draw(text_quest[i]);
                window.draw(rasp_text[i]);
            }
            window.draw(nume_test);
            if(rasp_input)
            {
                sf::Text text;
                text.setPosition(pozx_input,pozy_input);
                text.setString(input_text);
                text.setFont(font);
                text.setCharacterSize(input_text_size);
                window.draw(text);
            }
        }
        window.display();
    }
    Save();
    return 0;
}

void MainMenu()
{
    t_menu=false;
    solve_menu=false;
    quest_menu=false;
    Button elev_Button(535,0,535,720,ElevMenu);
    Button prof_Button(0,0,535,720,ProfesorMenu);
    elev_Button.setTexture_mOn(Elev_2);
    elev_Button.setTexture_mOff(Elev_1);
    prof_Button.setTexture_mOn(Profesor_2);
    prof_Button.setTexture_mOff(Profesor_1);
    entities.clear();
    entities.push_back(prof_Button);
    entities.push_back(elev_Button);
}
void ElevMenu()
{
    t_menu=true;
    solve_menu=false;
    quest_menu=false;
    Button background(0,0,1070,720);
    Button back(30,650,70,54,MainMenu);
    background.setTexture_mOff(Elev_background);
    background.Deactivate();
    back.setTexture_mOff(Back_1);
    back.setTexture_mOn(Back_2);
    entities.clear();
    entities.push_back(background);
    entities.push_back(back);
    int lg=tests.size();
    for(int j=0; j<lg; ++j)
    {
        Button b1(90,205+j*65,300,45,ElevSolveTest,j);
        b1.setTexture_mOff(Blank_1);
        b1.setTexture_mOn(Blank_2);
        Button b2=b1;
        entities.push_back(b2);
    }
}
void ProfesorMenu()
{
    t_menu=true;
    solve_menu=false;
    quest_menu=false;
    Button background(0,0,1070,720);
    Button add(940,45,70,60);
    Button back(30,650,70,54,MainMenu);
    background.setTexture_mOff(Profesor_background);
    background.Deactivate();
    add.setTexture_mOff(Add_1);
    add.setTexture_mOn(Add_2);
    back.setTexture_mOff(Back_1);
    back.setTexture_mOn(Back_2);
    entities.clear();
    entities.push_back(background);
    entities.push_back(add);
    entities.push_back(back);
    int lg=tests.size();
    for(int j=0; j<lg; ++j)
    {
        Button b1(90,205+j*65,300,45,ProfesorReadTest,j);
        b1.setTexture_mOff(Blank_1);
        b1.setTexture_mOn(Blank_2);
        entities.push_back(b1);
    }
}

void ProfesorReadTest(int nr)
{
    t_menu=false;
    solve_menu=true;
    quest_menu=false;
    nr_test=nr;
    Button intrebare1(42,42,300,200);
    Button intrebare2(384,42,300,200);
    Button intrebare3(726,42,300,200);
    Button intrebare4(213,284,300,200);
    Button intrebare5(555,284,300,200);
    Button background(0,0,1070,720);
    Button back(30,350,70,54,ProfesorMenu);
    intrebare1.Deactivate();
    intrebare2.Deactivate();
    intrebare3.Deactivate();
    intrebare4.Deactivate();
    intrebare5.Deactivate();
    background.Deactivate();
    intrebare1.setTexture_mOff(questions[1]);
    intrebare2.setTexture_mOff(questions[2]);
    intrebare3.setTexture_mOff(questions[3]);
    intrebare4.setTexture_mOff(questions[4]);
    intrebare5.setTexture_mOff(questions[5]);
    background.setTexture_mOff(Blank_background);
    back.setTexture_mOff(Back_1);
    back.setTexture_mOn(Back_2);
    entities.clear();
    entities.push_back(background);
    entities.push_back(intrebare1);
    entities.push_back(intrebare2);
    entities.push_back(intrebare3);
    entities.push_back(intrebare4);
    entities.push_back(intrebare5);
    entities.push_back(back);
}
void ElevSolveTest(int nr)
{
    t_menu=false;
    solve_menu=false;
    quest_menu=true;
    nr_test=nr;
    Button intrebari[5];
    Button b1(400,20,300,45);
    Button forward(800,600,70,54,Calculeaza);
    forward.setTexture_mOff(Forward_1);
    forward.setTexture_mOn(Forward_2);
    b1.setTexture_mOff(Blank_1);
    b1.Deactivate();
    intrebari[0]=b1;
    b1=Button(400,157,300,45);
    b1.setTexture_mOff(Blank_1);
    b1.Deactivate();
    intrebari[1]=b1;
    b1=Button(400,295,300,45);
    b1.setTexture_mOff(Blank_1);
    b1.Deactivate();
    intrebari[2]=b1;
    b1=Button(400,427,300,45);
    b1.setTexture_mOff(Blank_1);
    b1.Deactivate();
    intrebari[3]=b1;
    b1=Button(400,562,300,45);
    b1.setTexture_mOff(Blank_1);
    b1.Deactivate();
    intrebari[4]=b1;
    Button background(0,0,1070,720);
    background.setTexture_mOff(Blank_background_2);
    background.Deactivate();
    Button back(30,350,70,54,ElevMenu);
    back.setTexture_mOff(Back_1);
    back.setTexture_mOn(Back_2);
    entities.clear();
    entities.push_back(background);
    entities.push_back(intrebari[0]);
    entities.push_back(intrebari[1]);
    entities.push_back(intrebari[2]);
    entities.push_back(intrebari[3]);
    entities.push_back(intrebari[4]);
    entities.push_back(back);
    entities.push_back(forward);
    rasp1=rasp2=rasp3=rasp4=rasp5="raspuns";
}
void Calculeaza()
{
    t_menu=false;
    solve_menu=false;
    quest_menu=false;
    Button background(0,0,1070,720);
    Button back(30,350,70,54,ElevMenu);
    back.setTexture_mOff(Back_1);
    back.setTexture_mOn(Back_2);
    int scor=0;
    if(rasp1==tests[nr_test].getQuestion(0).GetRA())
    {
        scor+=20;
        if(rasp2==tests[nr_test].getQuestion(1).GetRA())
        {
            scor+=20;
            if(rasp3==tests[nr_test].getQuestion(2).GetRA())
            {
                scor+=20;
                if(rasp4==tests[nr_test].getQuestion(3).GetRA()){
                    scor+=20;
                    if(rasp5==tests[nr_test].getQuestion(4).GetRA()){
                        scor+=20;
                    }
                }
            }
        }
    }
    if(scor==0) background.setTexture_mOff(punctaj0);
    else if(scor==20) background.setTexture_mOff(punctaj20);
    else if(scor==40) background.setTexture_mOff(punctaj40);
    else if(scor==60) background.setTexture_mOff(punctaj60);
    else if(scor==80) background.setTexture_mOff(punctaj80);
    else background.setTexture_mOff(punctaj100);
    background.Deactivate();
    entities.clear();
    entities.push_back(background);
    entities.push_back(back);
}
