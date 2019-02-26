/* Hangman.cpp
 Chaweinta Hale, Nami Kim, Erin Tolman
 11/30/17
 Hangman game which has two players, player 1 set up a word and player 2 has to guess that word with less than 6 wrong guesses.
 */
#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;
#include <vector>
using std::vector;
#include <sstream>
using std::istringstream;
#include <algorithm>
using std::count;

//introduction to the game
void intro()
{
    
    cout << "**************************************" << endl;
    
    cout << "********* WELCOME TO HANGMAN *********" << endl;
    
    cout << "**************************************" << endl;
    
    cout << endl;
    
    cout << "This game requires two players. Player 1 must enter a word with a maximum length of 10 characters, \nand Player 2 will guess letters until the word has been guessed correctly \nor if all 6 tries have been used." << endl << endl;
    
    cout << "Note: Player 2 can only guess letters, DO NOT enter full words." << endl << endl;
}
bool correctCharacters(string answer)
{
    int wrongCharacter = 0;
    for(int i = 0; i < answer.size(); i ++)
    {
        char l = answer[i];
        if((l < 65 || l > 90) && (l < 97 || l > 122))
        {
            ++wrongCharacter;
        }
    }
    if(wrongCharacter > 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}
//Check to see if word length is in the correct range and does not contain spaces or tabs
string acceptable(string a)
{
    string feedback;
    if (a == "")
    {
        feedback = "Must enter a word to continue.";
        return feedback;
    }
    else if(a.size()>10)
    {
        feedback = "Word is too big.";
        return feedback;
    }
    else if(a.size()< 3)
    {
        feedback = "Word is not long enough.";
        return feedback;
    }
    else if(count(a.begin(), a.end(), ' ')> 0 || count(a.begin(), a.end(), '\t')> 0)
    {
        feedback = "No tabs and no spaces in your word please.";
        return feedback;
    }
    else if(!(correctCharacters(a)))
    {
        feedback = "Word must contain only letters.";
        return feedback;
    }
    feedback = "";
    return feedback;
}
//Get word from Player 1
string getAnsw()
{
    string answ = "";
    string response;
    while(true)
    {
        cout << "Player 1 enter a word: ";
        response = "";
        getline(cin,answ);
        response = acceptable(answ);
        if(response != "")
        {
            cout << response << endl;
            continue;
        }
        else
        {
            break;
        }
    }
    cout << "That word fits the requirements, time to start!" << endl;
    return answ;
}
//function for the actual visual hangman
void figure(int wrong)
{
    if(wrong==0)
    {
        cout << "   I===" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
    }
    else if(wrong==1)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
    }
    else if(wrong==2)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I  |" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
    }
    else if(wrong==3)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I -|" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
    }
    else if(wrong==4)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I -|-" << endl;
        cout << "   I" << endl;
        cout << "   I" << endl;
    }
    else if(wrong==5)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I -|-" << endl;
        cout << "   I /"  << endl;
        cout << "   I" << endl;
    }
    else if(wrong==6)
    {
        cout << "   I===" << endl;
        cout << "   I  O" << endl;
        cout << "   I -|-" << endl;
        cout << "   I / \\"<< endl;
        cout << "   I \nYOU ARE DEAD" << endl;
    }
}
//Gives Player 2 up to 2 hints, always first letter in the answer that they haven't guessed yet.
void hint(vector<char> a, vector<char> g, int h)
{
    cout << "You've asked for a hint, this is hint number " << h << "\nYou have " << (2-h) << " hints left after this." << endl;
    for(int i = 0; i < a.size(); i++)
    {
        if (a[i] != g[i])
        {
            cout << "Try guessing " << a[i] << endl;
            break;
        }
    }
}

int main()
{
    intro();
    string answer;
    answer = getAnsw();
    
    vector<char> answ (answer.size(),'_');
    //convert Player 1's word to lowercase letters
    for (int i = 0; i < answer.size(); i++)
    {
        answ[i] = tolower(answer[i]);
    }
    vector<int> avec;
    vector<char> gues (answ.size(),'_');
    vector<char> wrong (1,'\n');
    int guesses = 0;
    int found = 0;
    string input;
    string letter;
    char b;
    int hints = 0;
    int a;
    int app;
    for(int i = 0; i < 50; i++)
    {
        
        cout << "\n";
    }
    cout << "Player 2 START" << endl;
    while(guesses < 6)
    {
        //Player 2 guesses, can only exit loop once guess is within specifications and not guessed yet.
        while (true)
        {
            cout << "Guess a letter: " ;
            getline(cin,letter);
            //Make sure player 2 only guesses a single letter
            if (letter.size() > 1)
            {
                cout << "Only ONE letter please, try again." << endl;
                continue;
            }
            else if(letter.size() == 1)
            {
                //Once Player 2's letter is the "Perfect size" change it to lowercase and extract it into a char for easier reading.
                istringstream ssin(letter);
                ssin >> b;
                b = towlower(b);
                app = 0;
                //Check to make sure that the letter has not been use before, if it has been guessed already that triggers variable appearance aka("app")
                for(int i = 0; i < gues.size(); i++)
                {
                    if(gues[i] == b)
                    {
                        app++;
                    }
                }
                for(int i = 0; i < wrong.size(); i++)
                {
                    if(wrong[i] == b)
                    {
                        app++;
                    }
                }
                if (app > 0)
                {
                    cout << "Guessed that already!" << endl;
                    continue;
                }
                //If neither trigger the appearance it is a valid new letter guess and thus exits loop
                else if (app == 0)
                {
                    break;
                }
            }
        }
        //checks whether letter appears in answer and counts those places in case.
        for (int i = 0; i < answ.size(); i++)
        {
            if (answ[i]==b)
            {
                avec.push_back(i);
                found++;
            }
        }
        //Tell player 2 that they guessed correctly
        //Put correctly guessed letter into underscore vector to show where it is in the word
        if(found > 0)
        {
            cout << "\n\t" << letter << " is in the word!" << endl;
            for(int i = 0; i < avec.size(); i++)
            {
                a = avec[i];
                gues[a] = answ[a];
            }
        }
        //Tell player 2 that they guessed incorrectly and number of tries left
        else if(found == 0)
        {
            guesses++;
            cout << "\t" << letter << " is NOT in the word!" << endl;
            cout << "You now have " << (6-guesses) << " tries left." << endl;
            wrong.push_back(b);
        }
        avec.clear();
        //Compares current guess vector to actual answer vector, if they're identical loop is exited
        if (answ == gues)
        {
            cout << "\n\t\t\t\tHey that's it Player 2 wins!! **CONGRATULATIONS**\n\t\t\t\tSorry Player 1." << endl;
            break;
        }
        //Print figure and underscore vector to show how many letters are left
        cout << "\n\n";
        figure(guesses);
        cout << endl;
        cout << "\t";
        for(int i = 0; i < gues.size(); i++)
        {
            cout << gues[i];
        }
        cout << endl;
        cout << endl;
        found = 0;
        cout << "Known wrong letters: ";
        for(int i = 0; i < wrong.size(); i++)
        {
            cout << wrong[i] << " ";
        }
        cout << endl;
        found = 0;
        //Only gives Player 2 chance to ask for a hint if they have any left.
        if (hints != 2)
        {
            while(true)
            {
                cout << "Enter c if you would like to continue, h if you'd like a hint" << endl;
                getline(cin,input);
                if (input == "c")
                {
                    break;
                }
                else if (input == "h")
                {
                    hints++;
                    hint(answ,gues,hints);
                    break;
                }
                //They must choose to continue or ask for hint otherwise it keeps asking.
                else
                {
                    cout << "Only the letter \"c\" or \"h\" please" << endl;
                    continue;
                }
            }
        }
    }
    //If player 2 runs out of tries, prints the actual answer
    if (guesses >= 6)
    {
        cout << "Player 2 is out of tries! Player 1 wins!!" << endl;
        cout << "The correct word was " << answer << "." << endl;
    }
}

