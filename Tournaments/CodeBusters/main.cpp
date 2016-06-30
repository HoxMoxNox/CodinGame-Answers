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

    // game loop
    while (1) {
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
                cerr << "hello" << endl;
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

            // Write an action using cout. DON'T FORGET THE "<< endl"
            // To debug: cerr << "Debug messages..." << endl;
            //cerr << "size of buster vector: " << busterInfo.size() << endl;
            //cerr << "Position of buster " << busterInfo[0][0] << "is" << busterInfo[0][1] << " " << busterInfo[0][2] << endl;
            int busterX = busterInfo[i][1];
            int busterY = busterInfo[i][2];
            
            
            //first checking if the buster has a ghost, if he does, send him to the base to release it
            if(busterInfo[i][3] == 1)
            {
                if(myTeamId == 0)
                {
                    if(sqrt( (0 - busterX) * (0 - busterX) + (0 - busterY) * (0 - busterY) ) < RELEASE_RANGE)
                    {
                        cout << "RELEASE" << endl;
                        continue;
                    }
                    else
                    {
                        cout << "MOVE 0 0" << endl;  
                        continue;
                    }
                }
                else
                {
                    if(sqrt((16000-busterX)*(16000-busterX) + (9000-busterY)*(9000-busterY)) < RELEASE_RANGE)
                    {
                        cout << "RELEASE" << endl;
                        continue;
                    }
                    else
                    {
                        cout << "MOVE 16000 9000" << endl;
                        continue;
                    }
                }
            }
            
            for(int j = 0; j < ghostInfo.size();j++)
            {
                int ghostId = ghostInfo[j][0];
                int ghostX = ghostInfo[j][1];
                int ghostY = ghostInfo[j][2];
                bool isBustedGhost = false;
                float dist = sqrt((ghosX-busterX)*(ghostX-busterX) + (ghostY - busterY)*(ghostY-busterY));
                
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
                if(!isBustedGhost && dist > MIN_BUST_RANGE && dist < MAX_BUST_RANGE)
                {
                    cout << "BUST " << ghostId << endl;
                    break;
                }
                //if the ghost is not within range, chase it, MOVE to it
                else if (dist > MAX_BUST_RANGE)
                {
                    cout << "MOVE " << ghostX << " " << ghostY << endl;
                    break;
                }
                
            }
            
            
            /*
            If there is a ghost near the busters, MOVE closest buster to it,
                then once close enough, BUST
                MOVE rest of busters to their closest ghost
                
            Then, with leftover busters, or if no busters have a ghost to go to
                have them scout the location by MOVING them away from the starting location
            
            If a ghost is captured, move the buster toward the base
                if within radius 1600 radius, RELEASE
            */
            

            cout << "MOVE 8000 4500" << endl; // MOVE x y | BUST id | RELEASE
        }
    }
}









