#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
int main()
{
    string LON;
    cin >> LON; cin.ignore();
    string LAT;
    cin >> LAT; cin.ignore();
    int N;
    cin >> N; cin.ignore();
    
    const int EARTH_RADIUS = 6371;
    string::size_type sz;
    
    replace(LON.begin(),LON.end(),',','.');
    replace(LAT.begin(),LAT.end(),',','.');
    
    double LatA = stod(LAT,&sz);
    double LonA = stod(LON,&sz);
    
    cerr << LatA << endl;
    cerr << LonA << endl;
    
    double x,y,dist;
    double MinDist = 100000000;
    string ClosestDefib;
    
    for (int i = 0; i < N; i++) {
        
        string LocationNumber;
        string Location;
        string Address;
        string PhoneNumber;
        string Longitude;
        string Latitude;
        
        double LonB;
        double LatB;
        
        string DEFIB;
        getline(cin, DEFIB);
        
        istringstream SEPARATE(DEFIB);
        
        getline(SEPARATE,LocationNumber,';');
        getline(SEPARATE,Location,';');
        getline(SEPARATE,Address,';');
        getline(SEPARATE,PhoneNumber,';');
        getline(SEPARATE,Longitude,';');
        getline(SEPARATE,Latitude,';');
        
        replace(Longitude.begin(),Longitude.end(),',','.');
        replace(Latitude.begin(),Latitude.end(),',','.');
        
        LonB = stod(Longitude,&sz);
        LatB = stod(Latitude,&sz);
    
        x = (LonB - LonA) * cos((LatA+LatB)/2);
        y = LatB-LatA;
        dist = sqrt(x*x + y*y) * EARTH_RADIUS;
        
        if(dist < MinDist)
        {
            MinDist = dist;
            ClosestDefib = Location;
        }
        
    }

    // Write an action using cout. DON'T FORGET THE "<< endl"
    // To debug: cerr << "Debug messages..." << endl;

    cout << ClosestDefib << endl;
}
