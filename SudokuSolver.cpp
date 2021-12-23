
//Cameron Mah
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>


//using namespace std;

std::vector<int> getPossibilities(std::vector<std::vector<int>> sudoku, int y, int x);
void solve(std::vector<std::vector<int>>& sudoku, int y, int x, bool& solved);
int main()
{
    std::vector<std::vector<int>> sudoku = {
        //Easy


        {1, 0, 6, 0, 0, 2, 3, 0, 0},
        {0, 5, 0, 0, 0, 6, 0, 9, 1},
        {0, 0, 9, 5, 0, 1, 4, 6, 2},
        {0, 3, 7, 9, 0, 5, 0, 0, 0},
        {5, 8, 1, 0, 2, 7, 9, 0, 0},
        {0, 0, 0, 4, 0, 8, 1, 5, 7},
        {0, 0, 0, 2, 6, 0, 5, 4, 0},
        {0, 0, 4, 1, 5, 0, 6, 0, 9},
        {9, 0, 0, 8, 7, 4, 2, 1, 0}

        //Hard
        /*
         {0, 0, 0, 0, 0, 0, 0, 0, 2},
         {0, 0, 0, 0, 0, 0, 9, 4, 0},
         {0, 0, 3, 0, 0, 0, 0, 0, 5},
         {0, 9, 2, 3, 0, 5, 0, 7, 4},
         {8, 4, 0, 0, 0, 0, 0, 0, 0},
         {0, 6, 7, 0, 9, 8, 0, 0, 0},
         {0, 0, 0, 7, 0, 6, 0, 0, 0},
         {0, 0, 0, 9, 0, 0, 0, 2, 0},
         {4, 0, 8, 5, 0, 0, 3, 6, 0}*/
         /*
          {8, 0, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 6, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 2, 0, 0},
          {0, 5, 0, 0, 0, 0, 0, 0, 0},
          {0, 0, 0, 0, 4, 0, 0, 0, 0},
          {0, 0, 0, 0, 0, 0, 0, 3, 0},
          {0, 0, 0, 0, 0, 0, 0, 0, 8},
          {0, 0, 0, 5, 0, 0, 0, 0, 0},
          {0, 9, 0, 0, 0, 0, 0, 0, 0}*/
    };


    //Thoughts:
    //Lets assume that it is a valid sudoku(Maybe i should validate the given sudoku first)
    //I will make a function to determine possible values any given cell can be 
    //For every possible value that cell can be, try every valid possibility

    //Potential Issues:
    //If I am filling the sudoku in place while backtracking there might be issues

    //getPossibilities(sudoku, 3, 4);
    bool solved = false;
    solve(sudoku, 0, 0, solved);

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << sudoku[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void solve(std::vector<std::vector<int>>& sudoku, int y, int x, bool& solved) {
    //std::cout << y << " " << x << std::endl;
    std::vector<int> possibleVect;
    //I NEED TO CHECK IF IT IS LAST INDEX
    if (x == 8 && y == 8 && sudoku[y][x] == 0) {
        possibleVect = getPossibilities(sudoku, y, x);
        sudoku[y][x] = possibleVect[0];
        solved = true;
        return;
    }
    if (y == 8 && x == 8) {
        solved = true;
        return;
    }
    if (sudoku[y][x] != 0) { //If it was a given cell
        if (x < 8) {
            solve(sudoku, y, x + 1, solved);
        }
        else if (x == 8) {
            solve(sudoku, y + 1, 0, solved);
        }
    }
    else {
        possibleVect = getPossibilities(sudoku, y, x);
        if (possibleVect.size() == 0) {//No possibilities, backtrack 
            return;
        }
        for (int i = 0; i < possibleVect.size(); i++) {
            if (solved == true) {
                return;
            }
            sudoku[y][x] = possibleVect[i];
            if (x < 8) {
                solve(sudoku, y, x + 1, solved);
            }
            else if (x == 8) {
                solve(sudoku, y + 1, 0, solved);
            }
        }
        if (solved == false) {//If reached end of function without solving then it is going back to try more so reset back to 0
            sudoku[y][x] = 0;
        }
    }

}


//Get possible values for a given index
//Change back to std::vector
std::vector<int> getPossibilities(std::vector<std::vector<int>> sudoku, int y, int x) {
    std::vector<int> possibleVect = { 1,2,3,4,5,6,7,8,9 };
    std::unordered_set<int> possibleSet; //Using set to get all taken numbers
    std::unordered_set<int>::iterator it;
    //Get 3by3
    //Top row
    if (y <= 2 && x <= 2) {
        //std::cout << 1 << std::endl;
        for (int i = 0; i <= 2; i++) {
            for (int j = 0; j <= 2; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 2 && x <= 5) {
        //std::cout << 2 << std::endl;
        for (int i = 0; i <= 2; i++) {
            for (int j = 3; j <= 5; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 2 && x <= 8) {
        //std::cout << 3 << std::endl;
        for (int i = 0; i <= 2; i++) {
            for (int j = 6; j <= 8; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }


    //Middle row
    else if (y <= 5 && x <= 2) {
        //std::cout << 4 << std::endl;
        for (int i = 3; i <= 5; i++) {
            for (int j = 0; j <= 2; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 5 && x <= 5) {
        //std::cout << 5 << std::endl;
        for (int i = 3; i <= 5; i++) {
            for (int j = 3; j <= 5; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 5 && x <= 8) {
        //std::cout << 6 << std::endl;
        for (int i = 3; i <= 5; i++) {
            for (int j = 6; j <= 8; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    //Bottom row
    else if (y <= 8 && x <= 2) {
        //std::cout << 7 << std::endl;
        for (int i = 6; i <= 8; i++) {
            for (int j = 0; j <= 2; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 8 && x <= 5) {
        //std::cout << 8 << std::endl;
        for (int i = 6; i <= 8; i++) {
            for (int j = 3; j <= 5; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    else if (y <= 8 && x <= 8) {
        //std::cout << 9 << std::endl;
        for (int i = 6; i <= 8; i++) {
            for (int j = 6; j <= 8; j++) {
                if (sudoku[i][j] != 0) {
                    possibleSet.insert(sudoku[i][j]);
                }
            }
        }
    }

    //Get column
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][x] != 0) {
            possibleSet.insert(sudoku[i][x]);
        }
    }

    //Get row
    for (int i = 0; i < 9; i++) {
        if (sudoku[y][i] != 0) {
            possibleSet.insert(sudoku[y][i]);
        }
    }

    it = possibleSet.begin();
    while (it != possibleSet.end()) {
        std::vector<int>::iterator position = std::find(possibleVect.begin(), possibleVect.end(), *it);
        if (position != possibleVect.end()) {
            possibleVect.erase(position);
        }
        it++;
    }
    /*
    for (int i = 0; i < possibleVect.size(); i++) {
        std::cout << possibleVect[i];
    }
    std::cout << std::endl;*/


    return possibleVect;
}