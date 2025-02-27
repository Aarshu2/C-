#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <climits> 
using namespace std;



vector<vector<int>> difficultyChooser(string difficulty) {
    if (difficulty == "H") {

        vector<vector<int>> matrix1 = {
            {0, 0, 1, 0, 9, 0, 0, 3, 0},
            {9, 6, 3, 0, 0, 0, 0, 0, 0},
            {8, 0, 0, 7, 5, 0, 0, 0, 6},
            {0, 0, 0, 0, 7, 0, 5, 0, 0},
            {0, 0, 7, 0, 8, 5, 4, 2, 0},
            {1, 0, 4, 0, 6, 0, 0, 0, 0},
            {3, 1, 8, 6, 0, 0, 0, 5, 7},
            {0, 0, 0, 0, 0, 0, 0, 8, 4},
            {0, 9, 0, 0, 2, 0, 0, 0, 0}
        };

        return matrix1;
    }

    return vector<vector<int>>(9, vector<int>(9, 0));  // Return a 9x9 empty matrix if difficulty is not "H"
}

vector<vector<int>> displayBoard(vector<vector<int>> &matrix) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            
            if(i == 0 && j == 0) {
                cout << "   0 1 2 3 4 5 6 7 8" << endl;
                cout << "   _________________" << endl;
            }
            if(j == 0) {
                cout << i << " |" << matrix[i][j] << '|';
            } else {
                cout << matrix[i][j] << '|';
            }
        }
        cout << endl;     
    }
    cout << endl;

    return matrix;
}

bool isBoardFilled(vector<vector<int>> &matrix) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(matrix[i][j] == 0) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<int>> addNumToBoard(vector<vector<int>> &matrix, int xCord, int yCord, int number) {
    bool checker = true;

    int possibilitiesV = 0;
    int possibilitiesV2 = 0;
    int possibilitiesH = 0;
    int possibilitiesH2 = 0;
    for(int i = 0; i < 9; i++) {
        bool checkerV = true;
        bool checkerV2 = true;
        bool checkerH = true;
        bool checkerH2 = true;
        
        if(matrix[i][xCord] == number) {
            checker = false;
            break;
        }   
        else if(matrix[i][xCord] == 0) {
            for(int j = 0; j < 9; j++) {
                if(i != yCord) {
                    checkerV2 = false;
                }
                if(i == yCord && matrix[i][j] == number) {
                    checkerV2 = false;
                }
                else if (matrix[i][j] == number) {
                    checkerV = false;
                    break;
                }
            }
            if(checkerV) {
                possibilitiesV++;
            }
            if(checkerV2) {
                possibilitiesV2++;
            }
        }    

        if(matrix[yCord][i] == number) {
            checker = false;
            break;
        }
        else if(matrix[yCord][i] == 0) {
            for(int j = 0; j < 9; j++) { 
                if(i != xCord) {
                    checkerH2 = false;
                }
                if(i == xCord && matrix[j][i] == number) {
                    checkerH2 = false;
                }
                else if (matrix[j][i] == number) {
                    checkerH = false;
                    break;
                }
            }
            if(checkerH) {
                possibilitiesH++;
            }
            if(checkerH2) {
                possibilitiesH2++;
            }
        
        }     
    }

    
    if(checker == false) {
        cout << "You cant place a " << number << " in this spot." << endl;
        return matrix;
    }

    if((possibilitiesV == 1 && possibilitiesV2 == 1) || (possibilitiesH == 1 && possibilitiesH2 == 1)) {
        matrix[yCord][xCord] = number;
        cout << "\nSuccessful!" << endl;    
        return matrix;
    }

    
    int startRow = (yCord / 3) * 3; 
    int startCol = (xCord / 3) * 3; 
    int possibilities = 0;
    bool pCheck = true;
    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if(matrix[i][j] == 0) {
                for(int n = 0; n < 9; n++) {
                    if(matrix[n][j] == number) { pCheck = false; break; }
                    if(matrix[i][n] == number) { pCheck = false; break; }
                }
                if (pCheck) {
                    possibilities++;
                }
            }
            if(matrix[startRow][startCol] == number) {
                checker = false;
                break;
            } 
            pCheck = true;
        }
        if(checker == false) {
            break;
        }
    }

    if(checker && possibilities == 1) {
        matrix[yCord][xCord] = number;
        cout << "\nSuccessful!" << endl;  
        return matrix;
    } 
    else {
        cout << "You cant place a " << number << " in this spot." << endl;
        return matrix;
    }
}

int main() {
    cout << "\nWelcome!" << endl;
    cout << "Which difficulty would you like to choose for Sudoku, \n H for Hard \n M for Medium \n E for Easy" << endl;
    string difficulty; cin >> difficulty;

    vector<vector<int>> matrix = difficultyChooser(difficulty);

    while(isBoardFilled(matrix)) {
        displayBoard(matrix);
        cout << "Input the cordinate and the number for ex:  x,y 3 <- Meaning at column x, row y, input 3" << endl;
        char comma;
        int x, y, num; cin >> x >> comma >> y >> num;
        addNumToBoard(matrix, x, y, num);
    }
    return 0;
}