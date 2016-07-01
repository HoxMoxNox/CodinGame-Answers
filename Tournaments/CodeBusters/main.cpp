#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Send your busters out into the fog to trap ghosts and bring them home!
 **/
int main()
{
    int bustersPerPlayer; // the amount of busters you control
    cin >> bustersPerPlayer; cin.ignore();
    int ghostCount; // the amount of ghosts on the map
    cin >> ghostCount; cin.ignore();
    int myTeamId; // if this is 0, your base is on the top left of the map, if it is 1, on the bottom right
    cin >> myTeamId; cin.ignore();
    
    const int MIN_BUST_RANGE = 900;
    const int MAX_BUST_RANGE = 1760;
    const int RELEASE_RANGE = 1600;
    const int MAX_STUN_RANGE = 1760;
    
    //Patrol modes for the busters
    int patrolModes[] = {0,0,0,0,0};
    
    //a stun timer for each potential buster
    int usedStun[] = {0,0,0,0,0};
    
    //memory for seen ghosts
    vector< vector<int> >potentialGhostLocations;
    
    //turn counter
    int turn = 0;
    
    //this counter saves how many turns a certain buster has been chasing an enemy buster
    int chaseTime[] = {0,0,0,0,0};
    
    //score keeping
    int personalScore = 0;
    int potentialEnemyScore = 0;

    // game loop
    while (1) {
        
        turn++;
        
        int entities; // the number of busters and ghosts visible to you
        cin >> entities; cin.ignore();
        vector< vector<int> > ghostInfo;
        vector< vector<int> > busterInfo;
        vector< vector<int> > enemyInfo;
        
        
        for (int i = 0; i < entities; i++) {
            int entityId; // buster id or ghost id
            int x;
            int y; // position of this buster / ghost
            int entityType; // the team id if it is a buster, -1 if it is a ghost.
            int state; // For busters: 0=idle, 1=carrying a ghost.
            int value; // For busters: Ghost id being carried. For ghosts: number of busters attempting to trap this ghost.
            cin >> entityId >> x >> y >> entityType >> state >> value; cin.ignore();
            
            int currentInfoArray[] = {entityId,x,y,state,value};
            
            vector<int> currentInfo(currentInfoArray,
                        currentInfoArray+sizeof(currentInfoArray)/sizeof(int));
            
            if(entityType == myTeamId)
            {
                busterInfo.push_back(currentInfo);
                
            }
            else if(entityType == -1)
            {
                ghostInfo.push_back(currentInfo);             
            }
            else
            {
                enemyInfo.push_back(currentInfo);
            }

        }
        
        
        for (int i = 0; i < bustersPerPlayer; i++) {
            
            //let stun timers reset over time
            if(usedStun[i] > 0)
            {
                usedStun[i]--;
            }
            //cerr << "Position of buster " << busterInfo[0][0] << "is" << busterInfo[0][1] << " " << busterInfo[0][2] << endl;
            int busterX = busterInfo[i][1];
            int busterY = busterInfo[i][2];
            
            bool givenCommand = false;

            //first checking if the buster has a ghost, if he does, send him to the base to release it
            if(busterInfo[i][3] == 1)
            {
                //cerr << "current buster value: " << busterInfo[i][4] << endl;
                if(myTeamId == 0)
                {
                    if(sqrt( (0 - busterX) * (0 - busterX) + (0 - busterY) * (0 - busterY) ) < RELEASE_RANGE)
                    {
                        cout << "RELEASE Releasing" << endl;
                        personalScore++;
                        givenCommand = true;
                        continue;
                    }
                    else
                    {
                        cout << "MOVE 0 0 Moving to base" << endl;  
                        givenCommand = true;
                        continue;
                    }
                }
                else
                {
                    if(sqrt((16000-busterX)*(16000-busterX) + (9000-busterY)*(9000-busterY)) < RELEASE_RANGE)
                    {
                        cout << "RELEASE Releasing" << endl;
                        personalScore++;
                        givenCommand = true;
                        continue;
                    }
                    else
                    {
                        cout << "MOVE 16000 9000 Moving to base" << endl;
                        givenCommand = true;
                        continue;
                    }
                }
            }
            
            if(givenCommand)
            {
                continue;
            }
            
            //next check if I can stun an opposing player
            for(int k = 0; k < enemyInfo.size();k++)
            {
                int enemyId = enemyInfo[k][0];
                int enemyState = enemyInfo[k][3];
                int enemyX = enemyInfo[k][1];
                int enemyY = enemyInfo[k][2];
                
                
                float dist = sqrt((enemyX-busterX)*(enemyX-busterX) + (enemyY-busterY)*(enemyY-busterY));
                
                if(!usedStun[i] && enemyState == 1 && dist < MAX_STUN_RANGE)
                {
                    usedStun[i] = 20;
                    cout << "STUN " << enemyId << " Stunning enemy " << enemyId << endl;
                    givenCommand = true;
                    chaseTime[i] = 0;
                    break;
                }
                else if(usedStun[i] < 5 && enemyState == 1)
                {
                    cout << "MOVE " << enemyX << " " << enemyY << " Chasing enemy to stun" << endl;
                    cerr << "Chsed for " << chaseTime[i] << " turns" << endl;
                    chaseTime[i]++;
                    givenCommand = true;
                    break;
                }
                
            }
            
            if(givenCommand)
            {
                continue;
            }
            
            //next go for ghosts first based on stamina strength
         //   for(int j = 0; j < ghostInfo.size();j++)
         //   {
          //      cerr << "pre sorted ghosts" << endl;
           //     cerr << ghostInfo[j][0] << " " << ghostInfo[j][1] << " " << ghostInfo[j][2] << " " << ghostInfo[j][3] << " "<< ghostInfo[j][4] << endl;
           // }
            
            sort(ghostInfo.begin(), ghostInfo.end(), [](const std::vector< int >& a, const std::vector< int >& b){ return a[3] < b[3]; } );
            
         //   for(int j = 0; j < ghostInfo.size();j++)
         //   {
         //       cerr << "post sorted ghosts" << endl;
           //     cerr << ghostInfo[j][0] << " " << ghostInfo[j][1] << " " << ghostInfo[j][2] << " " << ghostInfo[j][3] << " "<< ghostInfo[j][4] << endl;
            //}
            
            for(int j = 0; j < ghostInfo.size();j++)
            {
                int ghostId = ghostInfo[j][0];
                int ghostX = ghostInfo[j][1];
                int ghostY = ghostInfo[j][2];
                bool isBustedGhost = false;
                float dist = sqrt((ghostX-busterX)*(ghostX-busterX) + (ghostY-busterY)*(ghostY-busterY));
                
                //check that no other buster already has this ghost
                for (int i = 0; i < bustersPerPlayer; i++)
                {
                    if(busterInfo[i][4] == ghostId)
                    {
                        isBustedGhost = true;
                        break;
                    }
                }
                //then check if the ghost is within range and BUST
                if(dist > MIN_BUST_RANGE && dist < MAX_BUST_RANGE)
                {
                    cout << "BUST " << ghostId << " Busting ghost " << ghostId << endl;
                    givenCommand = true;
                    break;
                }
                //if the ghost is not within range, chase it, MOVE to it
                else if (dist > MAX_BUST_RANGE)
                {
                    //Have one constant camper that only moves for nearby ghosts
                    if(i != 0 || (i == 0 && dist < 4500))
                    {
                    cout << "MOVE " << ghostX << " " << ghostY << " Go to ghost " << ghostId << endl;
                    givenCommand = true;
                    break;
                    }
                }
                
            }
            
            if(givenCommand)
            {
                continue;
            }
            
            //if no command is given yet, camp the enemy grounds and set patrol points
            if(!givenCommand)
            {
                if(myTeamId == 0)
                {
                    //perma-camper
                    if(i == 0)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 12000 7800 Camp" << endl;
                            if(busterX == 12000 && busterY == 7800)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 13500 6500 Camp" << endl;
                            if(busterX == 13500 && busterY == 6500)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else if(patrolModes[i] == 2)
                        {
                            cout << "MOVE 15000 6000 Camp" << endl;
                            if(busterX == 15000 && busterY == 6000)
                            {
                                patrolModes[i] = 0;
                            }
                        }
                        
                    }
                    //patroller
                    else if(i == 1)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 13500 5500 Patrol" << endl;
                            if(busterX == 13500 && busterY == 5500)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 14000 2000 Patrol" << endl;
                            if(busterX == 14000 && busterY == 2000)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else
                        {
                            cout << "MOVE 2000 7000 Patrol" << endl;
                            if(busterX == 2000 && busterY == 7000)
                            {
                                patrolModes[i] = 0;
                            }
                        }
                    }
                    //camper
                    else if(i == 2)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 15000 6000 Camp" << endl;
                            if(busterX == 15000 && busterY == 6000)
                            {
                                patrolModes[i] = 1;
                            }
                        }                        
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 12000 7800 Camp" << endl;
                            if(busterX == 12000 && busterY == 7800)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else if(patrolModes[i] == 2)
                        {
                            cout << "MOVE 13500 6500 Camp" << endl;
                            if(busterX == 13500 && busterY == 6500)
                            {
                                patrolModes[i] = 0;
                            }
                        }

                    }
                    //patroller
                    else if(i == 3)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 10000 7000 Patrol" << endl;
                            if(busterX == 10000 && busterY == 7000)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 2000 6000 Patrol" << endl;
                            if(busterX == 2000 && busterY == 6000)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else
                        {
                            cout << "MOVE 11000 2000 Patrol" << endl;
                            if(busterX == 11000 && busterY == 2000)
                            {
                                patrolModes[i] = 0;
                            }
                        }   
                        
                    }
                    //camper
                    else if(i == 4)
                    {
                        cout << "MOVE 14000 4000 Camp" << endl;
                    }
                }
                else
                {
                    //perma-camper
                    if(i == 0)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 2800 1200 Camp" << endl;
                            if(busterX == 2800 && busterY == 1200)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 2500 2500 Camp" << endl;
                            if(busterX == 2500 && busterY == 2500)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else if(patrolModes[i] == 2)
                        {
                            cout << "MOVE 1200 2600 Camp" << endl;
                            if(busterX == 1200 && busterY == 2600)
                            {
                                patrolModes[i] == 0;
                            }
                        }                        
                    }
                    //patroller
                    else if(i == 1)
                    {
                        if(patrolModes[i] == 0)
                        { 
                            cout << "MOVE 4000 1500 Patrol" << endl;
                            if(busterX == 4000 && busterY == 1500)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 14000 2000 Patrol" << endl;
                            if(busterX == 14000 && busterY == 2000)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else
                        {
                            cout << "MOVE 2000 7000 Patrol" << endl;
                            if(busterX == 2000 && busterY == 7000)
                            {
                                patrolModes[i] = 0;
                            }
                        }                          
                    }
                    //camper
                    else if(i == 2)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 1200 2600 Camp" << endl;
                            if(busterX == 1200 && busterY == 2600)
                            {
                                patrolModes[i] == 1;
                            }
                        }                           
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 2800 1200 Camp" << endl;
                            if(busterX == 2800 && busterY == 1200)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else if(patrolModes[i] == 2)
                        {
                            cout << "MOVE 2500 2500 Camp" << endl;
                            if(busterX == 2500 && busterY == 2500)
                            {
                                patrolModes[i] = 0;
                            }
                        }

                    }
                    //patroller
                    else if(i == 3)
                    {
                        if(patrolModes[i] == 0)
                        {
                            cout << "MOVE 1700 3200 Patrol" << endl;
                            if(busterX == 1700 && busterY == 3200)
                            {
                                patrolModes[i] = 1;
                            }
                        }
                        else if(patrolModes[i] == 1)
                        {
                            cout << "MOVE 5500 7000 Patrol" << endl;
                            if(busterX == 5500 && busterY == 7000)
                            {
                                patrolModes[i] = 2;
                            }
                        }
                        else
                        {
                            cout << "MOVE 12500 1500 Patrol" << endl;
                            if(busterX == 12500 && busterY == 1500)
                            {
                                patrolModes[i] = 0;
                            }
                        }                          
                        
                    }
                    //camper
                    else if(i == 4)
                    {
                        cout << "MOVE 6000 1000 Camp" << endl;
                    }
                }
            }
            
        }
    }
}










