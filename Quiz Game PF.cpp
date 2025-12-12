#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <ctime>
using namespace std;
//ye hum ne function bnaya hai jo hm 50-50 lifeline k liye use kren gy
void lifeline5050(string options[], char correct) {
    int wrong[3],w=0;
    //Array mn wrong answers store karain ge
    for (int i = 0; i < 4; i++) {
        char letter = 'A' + i;
		//A,B,C,D ko letters assign kiye hain
        if (letter != correct) {
            wrong[w] = i;
            w++;
            //wrong array mn wrong answer k index store kr rhe
        }
    }
    int keep = wrong[rand() % 3];// aik random index select karain ge jahan pe aik wrong answer pra hoo ga
    for (int i = 0; i < 4; i++) {
        char letter = 'A' + i;
        if (letter == correct || i == keep)
            cout << options[i] << endl;
        else
            cout << "----" << endl;
    }
}
//ye hm ne function bnaya hai jo ke hm istemal kaarain ge Question access k liye mukhtalif txt files se question lain ge mukhtalif difficulty or category k hisab se
void QuestionAccess(double& Score, int a, int& Lifelines, int& i,int &Difficulty) {
    ifstream fin;
    if (a == 1)
        fin.open("scienceeasy.txt");
    else if (a == 2)
        fin.open("science(medium).txt");
    else if (a == 3)
        fin.open("science(hard).txt");
    else if (a == 4)
        fin.open("logic(easy).txt");
    else if (a == 5)
        fin.open("logic(medium).txt");
    else if (a == 6)
        fin.open("logic(hard).txt");
    else if (a == 7)
        fin.open("computer(easy).txt");
    else if (a == 8)
        fin.open("computer(medium).txt");
    else if (a == 9)
        fin.open("computer(hard).txt");

    if (!fin.is_open()) {
        cout << "Error opening file" << endl;
    }
    else {
        string QNO;
        int count = 0;
        while (getline(fin, QNO)) {//total lines count  karain ge file mn
            count++;
        }
		int target = ((rand() % (count - 5)) / 6) + 1;//targetline choose karain ge rand function se count se 5 minus karain gy kyun ke har question k sath 5 lines hoti hain question or options or answer aur hm akhri 5 lines ko consider nahi karain gy
        fin.clear();//ye use hota hai file ko reset krne k liye take us mn koi error flag na aye
        fin.seekg(0);//file reading start se shuru k liye
        int current = 0;
        while (getline(fin, QNO)) {
            current++;
            string options[4];
             int TIME_LIMIT = 10;//timer ki limit set ki
			 if (target * 6 + 1 == current) {//6 lines per question hain is liye 6 se multiply kiya or 1 add kiya kyun ke hum question pr poohonch jain
                 cout << QNO << endl;
                 for (int i = 0; i < 4; i++) {//loop options print krwane k liye
                     getline(fin, options[i]);
                     cout << options[i] << endl;
                 }
                 time_t start_time = time(nullptr);//time start kiya

                 string answer;
                 cout << "Enter your answer (A/B/C/D) or E for Lifeline: ";
                 cin >> answer;
                 answer[0] = toupper(answer[0]);//function use kiya agar user lowercase bhi dale ga too bhi usko uppercase kr de ga
                 time_t end_time = time(nullptr);
                 double time_taken = difftime(end_time, start_time);//time check kiya
                 cout << "Time taken: " << time_taken << " seconds\n";
                 if (time_taken > TIME_LIMIT) {
                     cout << "Too slow! Answer counted as wrong.\n";
                     if (Difficulty == 1)
                         Score -= 2;
                     else  if (Difficulty == 2)
                         Score -= 3;
                     else if (Difficulty == 3)
                         Score -= 5;
                     cout << "Current Score=" << Score << endl;
                     return;
                 }
                 else {//answer check kr rhe
                     string correct;
                     getline(fin, correct);
                     char correctChar = correct[0];

                     if (answer == correct) {
                         cout << "Correct Answer!\n";
                         Score += 10;
                         cout << "Current Score=" << Score << endl;
                         return;
                     }
                     else if (answer == "E") {//lifelines use krne k liye
                         if (Lifelines <= 0) {
                             cout << "No lifelines remaining.\n";
                         }
                         else {
                             cout << "1. 50/50\n2. Skip Question\n3. Swap Question\n4.Extend Time\n";
                             int option;
                             cin >> option;
                             if (option == 1) {
                                 Lifelines--;
                                 cout << "50/50 Lifeline Activated:\n";
                                 lifeline5050(options, correctChar);
                                 cout << "Enter answer: ";
                                 cin >> answer;
                                 answer[0] = toupper(answer[0]);
                                 if (answer == correct) {
                                     cout << "Correct!\n";
                                     Score += 10;
                                     cout << "Current Score=" << Score << endl;
                                 }
                                 else {
                                     cout << "Wrong! Correct answer was " << correct << endl;
                                     fin.seekg(current);
                                     Score -= 5;
                                     cout << "Current Score=" << Score << endl;
                                 }
                             }
                             else if (option == 2) {
                                 Lifelines--;
                                 cout << "Question Skipped! Correct answer was " << correct << endl;
                                 Score += 10;
                                 cout << "Current Score=" << Score << endl;
                             }
                             else if (option == 3) {
                                 Lifelines--;
                                 cout << "Question Swapped!";
                                 i--;
                                 return;
                             }
                             else if (option == 4) {
                                 cout << "Extra time granted. Enter answer: ";
                                 TIME_LIMIT = time_taken + 10;
                                 time_t start_time = time(nullptr);
                                 cin >> answer;
                                 answer[0] = toupper(answer[0]);
                                 time_t end_time = time(nullptr);
                                 double time_taken = difftime(end_time, start_time);
                                 cout << "Time taken: " << time_taken << " seconds\n";
                                 if (time_taken > TIME_LIMIT) {
                                     cout << "Too slow! Answer counted as wrong.\n";
                                     Score -= 5;
                                 }
                                 else {
                                     if (answer == correct) {
                                         cout << "Correct!\n";
                                         Score += 10;
                                         cout << "Current Score=" << Score << endl;
                                     }
                                     else {
                                         cout << "Wrong! Correct answer was " << correct << endl;
                                         Score -= 5;
                                         cout << "Current Score=" << Score << endl;
                                     }
                                 }
                                 return;
                             }
                         }
                         if (Difficulty == 1)
                             Score -= 2;
                         else  if (Difficulty == 2)
                             Score -= 3;
                         else if (Difficulty == 3)
                             Score -= 5;
                         cout << "Current Score=" << Score << endl;
                         return;
                       
                     }
                     else {
                         if (Difficulty == 1)
                             Score -= 2;
                         else  if (Difficulty == 2)
                             Score -= 3;
                         else if (Difficulty == 3)
                             Score -= 5;
                         cout << "Current Score=" << Score << endl;
                         return;
                     }
                 }
             }
            }
        }
    }
	void UpdateLeaderboard(string& playerName, double& currentScore) {//ye function leaderboard update krne k liye hai
    string names[1000];
    double scores[1000];
    int count = 0;
    bool found = false;
    ifstream fin("Leaderboard.txt");
    if (fin.is_open()) {
        while (count < 1000 && fin >> names[count] >> scores[count]) {
            if (names[count] == playerName) {
                scores[count] = currentScore;
                found = true;
            }
            count++;

        }
        fin.close();
    }
    if (!found && count < 1000) {
        names[count] = playerName;
        scores[count] = currentScore;
        count++;
    }
    ofstream fout("Leaderboard.txt");
    if (fout.is_open()) {
        for (int i = 0; i < count; i++) {
            fout << names[i] << " " << scores[i] << endl;
        }
        fout.close();
        cout << "Leaderboard updated successfully!" << endl;
    }
    else {
        cout << "Error saving Leaderboard." << endl;
    }
}
	int main() {//main function
    srand(time(0));
    int Menu, Category, Difficulty, a;
    int Next,streak=0;
    int Lifelines = 3;
    double Score = 0;
	bool NameEntered = false;
    string Name;
	//welcome message
    cout << "				==========================\n					 Quiz Game\n				==========================\n\n";
    cout << "Welcome to the Quiz Game! Test your knowledge with a series of questions.\n\n";
	do {//name input aur check lgaya hoa hai ke name empty na ho
        cout << "Enter Your Name=";
        NameEntered = false;
        getline(cin, Name);
        if (Name.length() == 0) {
            cout << "Name cannot be empty. ";
			NameEntered = true;
        }
    } while (NameEntered );
            Lifelines = 3;
    do {
        do {
            cout << "\nChoose what do you want to do:\n1.  Start New Quiz\n2.  View Leaderboard\n3.  Exit\n";
            cout << "Choose Option=";
            cin >> Menu;

			while (cin.fail()) {//input validationq
        cin.clear();            
        cin.ignore(1000, '\n'); 
        cout << "\nInvalid input! Enter a number= ";
        cin >> Menu;
    }
   
        } while (Menu < 1 || Menu>3);
        if (Menu == 1) {
            Score = 0;

            cout << "\nYou have 3 Lifelines!\nYou will earn points for each correct answer. Good luck!\n\n";
			do {//category selection
                cout << "==========================================\n	Choose a category:\n==========================================\n\n";
                cout << "\n1.  Science\n2.  Logic\n3.  Computer\n";
                cout << "Choose Option=";
                cin >> Category;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Enter a number= ";
                    cin >> Category;
                }
            } while (Category < 1 || Category>3);
            if (Category == 1) {
                do {
                    cout << "==========================================\n	Choose Difficulty Level:\n==========================================\n\n";
                    cout << "\n1.  Easy\n2.  Medium\n3.  Hard\n";
                    cout << "Choose Option=";
					cin >> Difficulty;//difficulty selection
                    while (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Enter a number= ";
                        cin >> Difficulty;
                    }
                } while (Difficulty < 1 || Difficulty>3);
                if (Difficulty == 1) {
					a = 1;//file konsi select krni function mn us k liye
                    cout << "\n================================\n	Science - Easy Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines,i,Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;
               
                                cout << "Streak Score Added +5";
                               
                            }
                            if (streak == 5) {
                                Score += 15 ;
                                cout << "Streak of 5, Score Added +15";
                                streak=0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 2) {
                    a = 2;
                    cout << "\n================================\nScience - Medium Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";
                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 3) {
                    a = 3;
                    cout << "\n================================\nScience - Hard Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);//Function call kiya question access krne k liye 
                        if (previousScore + 10 == Score) {//streaks checking 
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";

                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
            }
            else if (Category == 2) {//same as category 1
                cout << "==========================================\n	Choose Difficulty Level:\n==========================================\n\n";
                cout << "\n1.  Easy\n2.  Medium\n3.  Hard\n";
                cout << "Choose Option=";
                cin >> Difficulty;
                if (Difficulty == 1) {
                    a = 4;
                    cout << "\n================================\nLogic - Easy Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";
                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 2) {
                    a = 5;
                    cout << "\n================================\nLogic - Medium Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";

                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 3) {
                    a = 6;
                    cout << "\n================================\nLogic - Hard Level\n================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";
                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
            }
            else if (Category == 3) {
                cout << "==========================================\n	Choose Difficulty Level:\n==========================================\n\n";
                cout << "\n1.  Easy\n2.  Medium\n3.  Hard\n";
                cout << "Choose Option=";
                cin >> Difficulty;
                while (cin.fail()) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input! Enter a number= ";
                    cin >> Difficulty;
                }
                if (Difficulty == 1) {
                    a = 7;
                    cout << "\n=====================================\nComputer - Easy Level\n=====================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";

                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 2) {
                    a = 8;
                    cout << "\n=====================================\nComputer - Medium Level\n=====================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;
                                cout << "Streak Score Added +5";

                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
                else if (Difficulty == 3) {
                    a = 9;
                    cout << "\n=====================================\nComputer - Hard Level\n=====================================\n";
                    for (int i = 0; i < 10; i++) {
                        int previousScore = Score;
                        QuestionAccess(Score, a, Lifelines, i, Difficulty);
                        if (previousScore + 10 == Score) {
                            streak++;
                            if (streak == 3) {
                                Score += 5;

                                cout << "Streak Score Added +5";

                            }
                            if (streak == 5) {
                                Score += 15;
                                cout << "Streak of 5, Score Added +15";
                                streak = 0;
                            }
                        }
                        else
                            streak = 0;
                        cout << "\nYour Total Score=" << Score;
                        cout << "\n=====================================================\n\n";
                    }
                    cout << "Your Total Score=" << Score;
                }
            }

            cout << "\nQuiz Finished! Total Score: " << Score << endl;
            UpdateLeaderboard(Name, Score);
        }
        else {
			if (Menu == 2) {//leaderboard display
                cout << "\n=============================\n       Leaderboard\n=============================\n";
				ifstream fin("Leaderboard.txt");//OPENING FILE
                if (!fin.is_open()) {
                    cout << "\nNo Leaderboard data found. Play a game first!\n";
                }
                else {
                    string names[1000];
                    double scores[1000];
                    int count = 0;
                    while (fin >> names[count] >> scores[count]) {
                        count++;
                        if (count >= 1000)
                            break;
                    }
                    fin.close();
					for (int i = 0; i < count - 1; i++) {//sorting leaderboard according to scores
                        for (int j = 0; j < count - i - 1; j++) {
                            if (scores[j] < scores[j + 1]) {
                                double tempScore = scores[j];
                                scores[j] = scores[j + 1];
                                scores[j + 1] = tempScore;
                                string tempName = names[j];
                                names[j] = names[j + 1];
                                names[j + 1] = tempName;
                            }
                        }
                    }
                    cout << "Rank\tName\tScore\n";
                    cout << "-----------------------------\n";

                    int limit = (count < 5) ? count : 5;

					for (int i = 0; i < limit; i++) {//displaying top 5 players ya phr jitne players hain
                        cout << i + 1 << "  " << names[i] << "  " << scores[i] << endl;
                    }

                    cout << endl;
                }
            }
            else if (Menu == 3) {
                cout << "\nThank you for playing the Quiz Game! Goodbye!\n";
                return 0;
            }
			}do {//agar user main menu pr wapis ana chahta hai ya exit krna chahta hai
            cout << "\nDo you want to return to the main menu?\n1. Yes\n2. No (Exit)\nChoose Option=";
            cin >> Next;
            if (Next == 2)
                return 0;
            while (cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input! Enter a number= ";
                cin >> Next;
               
            }
		} while (Next < 1 || Next > 2);
    } while (Next == 1);
    return 0;
}
