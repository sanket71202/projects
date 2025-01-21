#include <stdio.h>
#include <bits/stdc++.h>
#include <iostream>
using namespace std;



 unordered_map<int,vector<int>> box;
 unordered_map<int,vector<int>> row;
 unordered_map<int,vector<int>> col;

 void setSudoku2(string input, int myarr[9][9]){
    for(int i = 0; i<input.length(); i++){
        myarr[i/9][i%9] = (int)input[i]-int('0');
    }
 }

 void setSudoku(int myarr[9][9]){
    for(int z = 0; z<9; z++){
        for(int x = 0; x<9; x++){
            myarr[z][x] = 0;
        }
    }
 }


 void mapSudoku(int myarr[9][9]){
    for(int i = 0; i<9; i++){
        for(int j = 0; j<9; j++){
            if(myarr[i][j]!=0){
                row[i].push_back(myarr[i][j]);
                col[j].push_back(myarr[i][j]);
                box[(j/3+i/3*3)].push_back(myarr[i][j]);
            }else{
                continue;
            }
        }
    }
 }

 bool  solveSudoku(int myarr[9][9],int i, int j){

            if(j>=9 && i>=8){
                return true;
            }
            if(j>=9 && i<8){
                j=0;
                i++;
            }

            if(myarr[i][j] == 0){
                for(int a = 1; a<10; a++){
                    int temp = j/3+i/3*3;
                    if(count(box[temp].begin(),box[temp].end(),a)==0 && find(row[i].begin(),row[i].end(),a)==row[i].end() && find(col[j].begin(),col[j].end(),a)==col[j].end()){
                        myarr[i][j] = a;
                        box[temp].push_back(a);
                        row[i].push_back(a);
                        col[j].push_back(a);
                        if(!solveSudoku(myarr,i,j+1)){
                            myarr[i][j] = 0;
                            box[temp].pop_back();
                            row[i].pop_back();
                            col[j].pop_back();    
                            continue;
                        }
                        return true;
                    }
                }
                return false;
            }else{
                return solveSudoku(myarr,i,j+1);
            }
 }


void printSudoku(int myarr[9][9]){
    for(int z = 0; z<9; z++){
        for(int x = 0; x<9; x++){
            cout<<" "<<myarr[z][x];
        }
        cout<<endl;
    }
}


int main(){
    int mySudoku[9][9];
    string input;
    cout<<" input sudoku values in single line, fill empty places with 0."<<endl;
    cin>>input;
    cout<<endl;
    setSudoku2(input,mySudoku);
    mapSudoku(mySudoku);
    if(solveSudoku(mySudoku,0,0)){
        cout<<"Sudoku solved!!";
        cout<<endl;
        printSudoku(mySudoku);
    }else{
        cout<<"could not solve sudoku";
    }
}

// int main(){
//     int mySudoku[9][9];
//     setSudoku(mySudoku);
//     mySudoku[0][1] = 5;
//     mySudoku[0][4] = 1;
//     mySudoku[0][8] = 6;
//     mySudoku[1][0] = 3;
//     mySudoku[1][3] = 5;
//     mySudoku[1][5] = 8;
//     mySudoku[1][7] = 9;
//     mySudoku[2][5] = 7;
//     mySudoku[2][7] = 4;
//     mySudoku[3][7] = 2;
//     mySudoku[4][1] = 9;
//     mySudoku[4][5] = 3;
//     mySudoku[4][6] = 1;
//     mySudoku[5][5] = 1;
//     mySudoku[5][8] = 9;
//     mySudoku[6][1] = 8;
//     mySudoku[6][3] = 3;
//     mySudoku[6][4] = 6;
//     mySudoku[6][6] = 9;
//     mySudoku[6][8] = 5;
//     mySudoku[7][0] = 9;
//     mySudoku[7][1] = 2;
//     mySudoku[8][0] = 6;
//     mySudoku[8][4] = 7;
//     mySudoku[8][7] = 8;

//     mapSudoku(mySudoku);
//     // cout<<"Row map: "<< " "<<endl;
//     // for(auto i = row.begin(); i!=row.end(); i++){
//     //     for(int j = 0; j<i->second.size(); j++){
//     //         cout<<i->first<<" "<<i->second[j]<<" "<<endl;
//     //     }
//     // }

//     // cout<<"Col map: "<< " "<<endl;
//     // for(auto i = col.begin(); i!=col.end(); i++){
//     //     for(int j = 0; j<i->second.size(); j++){
//     //         cout<<i->first<<" "<<i->second[j]<<" "<<endl;
//     //     }
//     // }

//     // cout<<"Box map: "<< " "<<endl;
//     // for(auto i = box.begin(); i!=box.end(); i++){
//     //     for(int j = 0; j<i->second.size(); j++){
//     //         cout<<i->first<<" "<<i->second[j]<<" "<<endl;
//     //     }
//     // }

//     // printSudoku(mySudoku);
    

//     if(solveSudoku(mySudoku,0,0)){
//         cout<<"Sudoku solved!!";
//         cout<<endl;
//         printSudoku(mySudoku);
//     }else{
//         cout<<"could not solve sudoku";
//     }

// }
 

