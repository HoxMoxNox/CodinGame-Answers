#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

# define PI 3.14159265358979323846  /* pi */

using namespace std;


pair<int,int> rotateMat(pair<int,int>ship, pair<int,int> checkpoint int angle);
int turnsToNextCheckpoint(pair<int,int> checkpoint, pair<int,int>ship, int dx, int dy);
/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
 
 
 
int main()
{
    
    bool boosted = false;
    bool lapped = false;
    vector< pair<int,int> > storedCheckpoints;
    pair<int,int>MID_MAP(8000,4500);
    
    //perhaps track acceleration?
    //int ddy,ddx,pprevX,pprevY;
    
    int dx = 0;
    int dy = 0; // velocity trackers
    int prevX,prevY;
    int turn = 0;
            
    // game loop
    while (1) {
        int x;
        int y;
        int nextCheckpointX; // x position of the next check point
        int nextCheckpointY; // y position of the next check point
        int nextCheckpointDist; // distance to the next checkpoint
        int nextCheckpointAngle; // angle between your pod orientation and the direction of the next checkpoint
        cin >> x >> y >> nextCheckpointX >> nextCheckpointY >> nextCheckpointDist >> nextCheckpointAngle; cin.ignore();
        int opponentX;
        int opponentY;
        cin >> opponentX >> opponentY; cin.ignore();
        
        if(turn > 0)
        {
            dx = x - prevX;
            dy = y  - prevY;
        }
        
        int thrust;
        int epsilon = 2;
        int delta = 10;
        
        
        pair<int,int>currentCheckpoint(nextCheckpointX,nextCheckpointY);
        pair<int,int> dest(nextCheckpointX, nextCheckpointY);
        pair<int,int>ship(x,y);
        
        int turnsToCP = turnsToNextCheckpoint(currentCheckpoint,ship,dx,dy);
        
        double angleToEnemy = atan2(opponentY - y, opponentX - x);
        double distToEnemy = sqrt( (opponentX - x) * (opponentX - x) + (opponentY - y) * (opponentY - y) );
        double enemyDistToCheck = sqrt( (nextCheckpointX-opponentX) * (nextCheckpointX-opponentX) + (nextCheckpointY-opponentY) * (nextCheckpointY-opponentY) );
        
        
        
        
        turn++;
        prevX = x;
        prevY = y;
    }
}

//This uses an AFFINE transformation, not a LINEAR transformation
pair<int,int> rotateMat(pair<int,int> ship, pair<int,int> checkpoint, int angle)
{
    vector<int> rotatedCoords;
    vector<int> rotatedCheckpoint;
    vector<int> rotatedShip;

    double rotateMatrix[2][2];
    rotateMatrix[0][0] = cos( (angle*PI) / 180 );
    rotateMatrix[0][1] = -sin( (angle*PI) / 180 );
    rotateMatrix[1][0] = sin( (angle*PI) / 180 );
    rotateMatrix[1][1] = cos( (angle*PI) / 180 );
    
    int x = ship.first;
    int y = ship.second;
    
    cerr << "Ship coords: " << x << " " << y << endl;
    
    int cx = checkpoint.first;
    int cy = checkpoint.second;
    
    cerr << "CP coords: " << cx << " " << cy << endl;
    
    cerr << "Angle to rotate about: " << angle << endl;
    
    cerr << "Rotation Matrix: " << rotateMatrix[0][0] << " " << rotateMatrix[0][1] << endl;
    cerr << "                 " << rotateMatrix[1][0] << " " << rotateMatrix[1][1] << endl;
    
    cerr << "Affine transformation R(X) + Xs - R(Xs)" << endl;

    rotatedCheckpoint.push_back((int)(rotateMatrix[0][0] * cx + rotateMatrix[0][1] * cy));
    rotatedCheckpoint.push_back((int)(rotateMatrix[1][0] * cx + rotateMatrix[1][1] * cy));
    
    cerr << "R(X): " << rotatedCheckpoint[0] << endl;
    cerr << "      " << rotatedCheckpoint[1] << endl;
    
    rotatedShip.push_back((int)(rotateMatrix[0][0] * x + rotateMatrix[0][1] * y));
    rotatedShip.push_back((int)(rotateMatrix[1][0] * x + rotateMatrix[1][1] * y));
    
    cerr << "R(Xs): " << rotatedShip[0] << endl;
    cerr << "       " << rotatedShip[1] << endl;
    
    
    cerr << "Xs:   " << x << endl;
    cerr << "      " << y << endl;


    rotatedCoords.first = rotatedCheckpoint[0] - rotatedShip[0] + x;
    rotatedCoords.second = rotatedCheckpoint[1] - rotatedShip[1] + y;
    
    cerr << "R(X) + Xs - R(Xs): " << rotatedCoords.first << endl;
    cerr << "                   " << rotatedCoords.second << endl;
    
    return rotatedCoords;
    
}



int turnsToNextCheckpoint(pair<int,int> checkpoint, pair<int,int>ship, int dx, int dy)
{
    int MAX_TURNS = 30;
    int CP_RADIUS = 600;
    int cx = checkpoint.first;
    int cy = checkpoint.second;
    int x = ship.first;
    int y = ship.second;
    
    for(int i = 0; i < MAX_TURNS; i++)
    {
        if( (x < cx + CP_RADIUS && x > cx - CP_RADIUS) 
           && (y < cy + CP_RADIUS && y > cy - CP_RADIUS) )
           {
               return i;
           }
           else
           {
               x += dx;
               y += dy;
           }
    }
    
    return MAX_TURNS;
    
}
















