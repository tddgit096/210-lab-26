//Toma Dimov | Lab-26 | COMP210

#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <list>
#include <set>
#include <chrono>
#include <algorithm>
#include <iomanip>
using namespace std;
using namespace std::chrono;

const int SETWIDTH = 15,OPERATIONS = 4, DATATYPES = 3,ITERATIONS = 15;

int main() {
    int data[OPERATIONS][DATATYPES][ITERATIONS];   //make 3d arr
    //our dataholders
    set <string> set1;
    vector <string> vector1;
    list <string> list1;

    //Run Tests and Gather Data =========================================
    for (int i=0;i<ITERATIONS;i++){
        //reading ====================
        fstream fin("codes.txt");
        string input;
        //vector
        auto start = high_resolution_clock::now();
        while (getline(fin,input)){
            vector1.push_back(input);
        }
        auto end = high_resolution_clock::now();
        data[0][0][i]= duration_cast<microseconds>(end - start).count();
        fin.clear();
        fin.seekp(0, std::ios::beg); 
        //list
        start = high_resolution_clock::now();
        while (getline(fin,input)){
            list1.push_back(input);
        }
        end = high_resolution_clock::now();
        data[0][1][i]= duration_cast<microseconds>(end - start).count();
        fin.clear();
        fin.seekp(0, std::ios::beg); 
        //set
        start = high_resolution_clock::now();
        while (getline(fin,input)){
            set1.insert(input);
        }
        end = high_resolution_clock::now();
        data[0][2][i]= duration_cast<microseconds>(end - start).count();
        fin.clear();
        fin.seekp(0, std::ios::beg); 
        

        //sorting ====================
        //vector
        start = high_resolution_clock::now();
        sort(vector1.begin(), vector1.end());
        end = high_resolution_clock::now();
        data[1][0][i]= duration_cast<microseconds>(end - start).count();
        //list
        start = high_resolution_clock::now();
        list1.sort();
        end = high_resolution_clock::now();
        data[1][1][i]= duration_cast<microseconds>(end - start).count();
        //set, can't sort a set.
        data[1][2][i]= duration_cast<microseconds>(end - start).count();


        //insert ====================
        //vector
        start = chrono::high_resolution_clock::now();
        vector1.insert(vector1.begin(), vector1.size()/2, "insertedVal");
        end = high_resolution_clock::now();
        data[2][0][i]= duration_cast<microseconds>(end - start).count();
        //list
        start = chrono::high_resolution_clock::now();
        list1.insert(list1.begin(), list1.size()/2, "insertedVal");
        end = high_resolution_clock::now();
        data[2][1][i]= duration_cast<microseconds>(end - start).count();
        //set
        start = chrono::high_resolution_clock::now();
        set1.insert("insertedVal");
        end = high_resolution_clock::now();
        data[2][2][i]= duration_cast<microseconds>(end - start).count();

        //delete ====================
        //vector
        auto itv = vector1.begin();
        advance(itv,vector1.size()/2);
        start = chrono::high_resolution_clock::now();
        vector1.erase(itv);
        end = high_resolution_clock::now();
        data[3][0][i]= duration_cast<microseconds>(end - start).count();
        //list
        auto itl = list1.begin();
        advance(itl, list1.size()/2);
        start = chrono::high_resolution_clock::now();
        list1.remove(*itl);
        end = high_resolution_clock::now();
        data[3][1][i]= duration_cast<microseconds>(end - start).count();
        //set
        auto its = set1.begin();
        advance(its,set1.size()/2);
        start = chrono::high_resolution_clock::now();
        set1.erase(its);
        end = high_resolution_clock::now();
    }

    //Averaging Data ===========================================
    int averageData[OPERATIONS][DATATYPES];
    int averageTemp=0;

    for (int h=0;h<OPERATIONS;h++)
        for(int j=0;j<DATATYPES;j++){
            averageTemp=0;
            for(int i=0;i<ITERATIONS;i++){
                averageTemp+=data[h][j][i];
            }
            averageData[h][j] = averageTemp/ITERATIONS;
        }
    
    //Outputting Data ===========================================
    cout<<"Number of simulations: "<<ITERATIONS<<endl;
    cout<<setw(SETWIDTH*2)<<"Vector"<<setw(SETWIDTH)<<"List"<<setw(SETWIDTH)<<"Set";
    cout<<endl<<left<<setw(SETWIDTH);
    for(int j=0;j<OPERATIONS;j++){
        switch (j){
        case 0:
            cout<<"Read:"<<right;
            break;
        case 1:
            cout<<"Sort:"<<right;
            break;
        case 2:
            cout<<"Insert:"<<right;
            break;
        case 3:
            cout<<"Delete:"<<right;
            break;
        }
        for(int i=0;i<DATATYPES;i++){
            cout<<setw(SETWIDTH)<<averageData[j][i];
        }
    cout<<endl<<left<<setw(SETWIDTH);
    }

    return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<microseconds>(end - start)
duration.count() references elapsed microseconds
*/  