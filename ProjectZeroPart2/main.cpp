//
//  main.cpp
//  ProjectZeroPart2
//
//  Created by Sierra on 8/21/15.
//  Copyright (c) 2015 Sierra Adibi. All rights reserved.
//
//  Updated on GitHub 8/22/15

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

int main(){

    
    srand(time(NULL));
    
    // Define the basics of the machines, and give them each vectors
    
    int numofmachines = 3;

    vector<double> machineMedian (numofmachines);
    vector<double> machineRange (numofmachines);
    vector<double> machineTotal (numofmachines,0);
    vector<double> machineAverage (numofmachines);
    vector<double> machineDeviation (numofmachines);
    vector< vector<double> > machineWinnings (numofmachines);
    
    for (int i=0;i < numofmachines; i++){
        machineMedian.at(i) = rand()%10;
        machineRange.at(i) = rand()%10;
        //  cout << "The median value for machine " << i+1 << " is " << machineMedian.at(i) << endl;
        //  cout << "The range value for machine " << i+1 << " is " << machineRange.at(i)<< endl;
        
    };
    
    
    
    cout << "Welcome to the Multi-Armed-Bandit.  Today we are playing with " << numofmachines << " machines. \n";
    cout << "We will start by playing 10 rounds on each machine.  Good Luck!";
    
    // First Run 10 rounds on each machine to get a baseline for their values.
    
    
    for (int firstround = 0; firstround < 10; firstround++){
        
        for (int r=0; r < numofmachines; r++){
            double r1 = ((double)rand()/RAND_MAX)*machineRange.at(r);
            double r2 = ((double)rand()/RAND_MAX)*machineRange.at(r);
            
            machineWinnings[r].push_back(machineMedian.at(r)+r1-r2);
        };

    };
    

    // calculate the average values for the machines
    
    vector<int> machineCount(numofmachines);
    vector<double> deviationCalc(numofmachines,0);
    
    for (int i=0;i < numofmachines; i++){
        
        machineCount.at(i) = machineWinnings[i].size();
        
        for (int j=0; j<machineCount.at(i);j++){
            machineTotal.at(i) = machineTotal.at(i) + machineWinnings[i][j];
            }
        
        machineAverage.at(i) = machineTotal.at(i)/machineCount.at(i);
        
    }
    
    
    // calculate standard deviations for the machines
    
    for (int i=0;i < numofmachines; i++){
        
        for (int j=0; j<machineCount.at(i);j++){
            deviationCalc.at(i) = deviationCalc.at(i) + pow((machineAverage.at(i)-machineWinnings[i][j]),2.0);
            }
        
        machineDeviation.at(i) = sqrt(deviationCalc.at(i)/machineCount.at(i));
        
    }

    
    // output results of the first ten rounds
    
    
    cout << "\n The results of your first 10 rounds are below: \n";
    
    cout << "Machine Number |  Total Winnings  | Average Pull Value |   Standard Deviation   |  Number of Pulls  \n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    
    for (int j=0;j<numofmachines;j++){
        
        cout << "       " << j+1 << "             " << machineTotal.at(j) << "             " << machineAverage.at(j);
        
        cout << "                 "<< machineDeviation.at(j) << "                    "  <<machineCount.at(j) <<endl << endl;
    };
    
    int reevaluations = 10;
    
    for (int eval = 1;eval < reevaluations; eval++){
    
    // compare average values, keep track of how many times each arm has been pulled, recalculate
    int roundcount = 0;
    
    while(roundcount<10){

    for (int i=0; i<numofmachines; i++){
        
        for (int j=i+1; j<numofmachines;j++){
            
            if(machineAverage.at(i)>machineAverage.at(j)){
                
                
                double r1 = ((double)rand()/RAND_MAX)*machineRange.at(i);
                double r2 = ((double)rand()/RAND_MAX)*machineRange.at(i);
                
                machineWinnings[i].push_back(machineMedian.at(i)+r1-r2);
                
            } else{
                double r1 = ((double)rand()/RAND_MAX)*machineRange.at(j);
                double r2 = ((double)rand()/RAND_MAX)*machineRange.at(j);
                
                machineWinnings[j].push_back(machineMedian.at(j)+r1-r2);
                
                
            };
            
            
        };
        
        
    };
        roundcount++;
    };
    
    
    // calculate the average values for the machines
    
    machineCount.clear();
    
    for (int i=0;i < numofmachines; i++){
        
        machineCount.push_back(machineWinnings[i].size());
        machineTotal.at(i) = 0;
        
        for (int j=0; j<machineCount.at(i);j++){
            machineTotal.at(i) = machineTotal.at(i) + machineWinnings[i][j];
        }
        
        machineAverage.at(i) = machineTotal.at(i)/machineCount.at(i);
        
    }
    
    
    // calculate standard deviations for the machines
    
    for (int i=0;i < numofmachines; i++){
        
        deviationCalc.at(i)=0;
        
        for (int j=0; j<machineCount.at(i);j++){
            deviationCalc.at(i) = deviationCalc.at(i) + pow((machineAverage.at(i)-machineWinnings[i][j]),2.0);
        }
        
        machineDeviation.at(i) = sqrt(deviationCalc.at(i)/machineCount.at(i));
        
    }
    
    
    // output results of the first ten rounds
    
    
    cout << "\n The results of your " << eval+1<<" 10 rounds are below: \n";
    
    cout << "Machine Number |  Total Winnings  | Average Pull Value |   Standard Deviation   |  Number of Pulls  \n";
    cout << "----------------------------------------------------------------------------------------------------\n";
    
    for (int j=0;j<numofmachines;j++){
        
        cout << "       " << j+1 << "             " << machineTotal.at(j) << "             " << machineAverage.at(j);
        
        cout << "                 "<< machineDeviation.at(j) << "                    "  <<machineCount.at(j) <<endl << endl;
    };
    
    

    };
    
    
    return 0;
    
}

