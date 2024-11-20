#include "neural_network.h"
#include <cstdlib> 
#include <ctime> 
using namespace std;

class Board
{
    public:
        vector<vector<int>> table;
        int score=0;

        Board() : table(4,vector<int>(4)) 
        {
            srand(time(0));
        };

        void init()
        {
            vector<pair<int, int>> emp;
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < 4; j++) {
                    if (table[i][j] == 0) {
                        emp.push_back({i, j});
                    }
                }
            }
            if (!emp.empty()) {
                int idx = rand() % emp.size();
                int x = emp[idx].first;
                int y = emp[idx].second;
                table[x][y] = (rand() % 2 + 1) * 2; // 随机生成 2 或 4
            }
        }
        void up()
        {
            vector<vector<int>> copy = table;
            for (int i=0;i<4;i++)
            {
                vector<int> temp;
                bool flag = true;
                for (int j=0;j<4;j++)
                {
                    if (table[j][i]==0) continue;
                    else if (!temp.empty()&&table[j][i]==temp.back()&&flag) 
                    {
                        temp.back()*=2;
                        flag = false;
                        score+=temp.back();
                    }
                    else
                    {
                        temp.push_back(table[j][i]);
                        flag = true;
                    }
                }
                while(temp.size()<4) temp.push_back(0);
                for (int j=0;j<4;j++)
                {
                    table[j][i] = temp[j];
                }
            }
            if(table!=copy) init();
        }
        void down()
        {
            vector<vector<int>> copy = table;
            for (int i=0;i<4;i++)
            {
                vector<int> temp;
                bool flag = true;
                for (int j=0;j<4;j++)
                {
                    if (table[3-j][i]==0) continue;
                    else if (!temp.empty()&&table[3-j][i]==temp.back()&&flag) 
                    {
                        temp.back()*=2;
                        flag = false;
                        score+=temp.back();
                    }
                    else
                    {
                        temp.push_back(table[3-j][i]);
                        flag = true;
                    }
                }
                while(temp.size()<4) temp.push_back(0);
                for (int j=0;j<4;j++)
                {
                    table[3-j][i] = temp[j];
                }
            }
            if(table!=copy) init();
        }
        void left()
        {
            vector<vector<int>> copy = table;
            for (int i=0;i<4;i++)
            {
                vector<int> temp;
                bool flag = true;
                for (int j=0;j<4;j++)
                {
                    if (table[i][j]==0) continue;
                    else if (!temp.empty()&&table[i][j]==temp.back()&&flag) 
                    {
                        temp.back()*=2;
                        flag = false;
                        score+=temp.back();
                    }
                    else
                    {
                        temp.push_back(table[i][j]);
                        flag = true;
                    }
                }
                while(temp.size()<4) temp.push_back(0);
                for (int j=0;j<4;j++)
                {
                    table[i][j] = temp[j];
                }
            }
            if(table!=copy) init();
        }
        void right()
        {
            vector<vector<int>> copy = table;
            for (int i=0;i<4;i++)
            {
                vector<int> temp;
                bool flag = true;
                for (int j=0;j<4;j++)
                {
                    if (table[i][3-j]==0) continue;
                    else if (!temp.empty()&&table[i][3-j]==temp.back()&&flag) 
                    {
                        temp.back()*=2;
                        flag = false;
                        score+=temp.back();
                    }
                    else
                    {
                        temp.push_back(table[i][3-j]);
                        flag = true;
                    }
                }
                while(temp.size()<4) temp.push_back(0);
                for (int j=0;j<4;j++)
                {
                    table[i][3-j] = temp[j];
                }
            }
            if(table!=copy) init();
        }
        void print()
        {
            for (int i=0;i<4;i++)
            {
                for (int j=0;j<4;j++)
                {
                    cout << table[i][j] << ' ';
                }
                cout << endl;
            }
            cout << "total score: " << score << endl;
        }
        
        bool is_over() 
        {
            for (int i = 0; i < 4; i++) 
            {
                for (int j = 0; j < 4; j++) 
                {
                    if (table[i][j] == 0) return false;
                }
            }
            for (int i = 0; i < 4; i++) 
            {
                for (int j = 0; j < 4; j++) 
                {
                    if (j < 3 && table[i][j] == table[i][j + 1]) return false;
                    if (i < 3 && table[i][j] == table[i + 1][j]) return false;
                }
            }
            return true;
        }
};

int main()
{
    Board game;
    game.init();
    game.init();
    game.print();
    
    
}