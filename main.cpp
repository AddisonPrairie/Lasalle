
//
//  main.cpp
//  LLTemplate
//
//  Created by James Shockey on 12/6/16.
//  Copyright © 2016 James Shockey. All rights reserved.
//

/*
 *
 *	Linked List lab.
 *	- Build a library for singly linked list.
 *	- Replace the airport array in main with a Linked List.
 *  - sort the array.
 *
 */

#include "slist.h"
#include "slist.cpp"
#include <string>
#include <cmath>
#include <fstream>
#include <iostream>

using namespace std;


void simpleSortTotal(slist* airportArr, int numAirports);
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d);

int main() {
  
	ifstream infile;
	int i = 0;
	char cNum[10];
	int airportCount;

  slist* airportArr = new slist();

  double ABIALong = -97.6663058;
  double ABIALat = 30.1974292;

  Airport * furthest = nullptr;

  double longestDistance = 0.;

  const double kmToM = .621371;
  
	infile.open("airport-codes_US.csv", ifstream::in);
  
	if (infile.is_open()) {
		int c = 0;

    char temp[405];

    infile.getline(temp, 400, '\n');
    
		while (infile.good()) {
			Airport* tempAir = new Airport();
			infile.getline(tempAir->code, 256, ',');
      //cout << tempAir->code << endl;
      //cout << airportArr[c]->code << endl;
      
			infile.getline(temp, 256, ',');
      infile.getline(temp, 256, ',');

      infile.getline(cNum, 256, ',');
      
			tempAir->longitude = atof(cNum);
			infile.getline(cNum, 256, ',');
			tempAir->latitude = atof(cNum);

      //AK97
      
      
      infile.getline(temp, 400, '\n');

      double distance = distanceEarth(tempAir->latitude, tempAir->longitude, ABIALat, ABIALong) * kmToM;
      
      //outside of 100 mile range
      if (distance > 100) {
        if (distance > longestDistance) {
          furthest = tempAir;
          longestDistance = distance;
          continue;
        } else {
          delete tempAir;
          continue;
        }
      }

      airportArr->add(tempAir);


			if (false)
				cout << tempAir->code
					 << " long: " << tempAir->longitude
					 << " lat: " <<tempAir->latitude << endl;


			i++;
			c++;
		}
    
		airportCount = c - 1;
		infile.close();

    cout << "airports in range "<< airportCount << endl;

    simpleSortTotal(airportArr, airportCount);

		for (int c = 0; c < airportCount; c++) {
      cout << ((Airport*)airportArr->get(c)->value)->code << endl;
      continue;
      cout << ((Airport*)airportArr->get(c)->value)->code << endl;
        Airport* tempAir = (Airport*)airportArr->get(c)->value;
      cout << "hello" << endl;
				cout << tempAir->code
					 << " long: " << tempAir->longitude
					 << " lat: " << tempAir->latitude << endl;
				cout << "Distance between " << tempAir->code << " and "
					 << "austin" << " is "
					 << distanceEarth(
              tempAir->latitude,
							tempAir->longitude,
							ABIALat,
							ABIALong) * kmToM
					 << endl;
		}
    cout << "furthest: " << endl;

    cout << furthest->code << endl;

	} else {
		cout << "Error opening file";
	}
}

#define pi 3.14159265358979323846
#define earthRadiusKm 6371.0

// This function converts decimal degrees to radians
double deg2rad(double deg) {
	return (deg * pi / 180);
}

//  This function converts radians to decimal degrees
double rad2deg(double rad) {
	return (rad * 180 / pi);
}

/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
	double lat1r, lon1r, lat2r, lon2r, u, v;
	lat1r = deg2rad(lat1d);
	lon1r = deg2rad(lon1d);
	lat2r = deg2rad(lat2d);
	lon2r = deg2rad(lon2d);
	u = sin((lat2r - lat1r) / 2);
	v = sin((lon2r - lon1r) / 2);
	return 2.0 * earthRadiusKm *
		asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}

/*
double ABIALong = -97.6663058;
  double ABIALat = 30.1974292;

  Airport * furthest = nullptr;

  double longestDistance = 0.;

  const double kmToM = .621371;
*/

double distanceToAustin(double lat, double lon) {
  return distanceEarth(lat, lon, 30.1974292, -97.6663058) * .621371;
} 

double airDist(Airport* air) {
  return distanceToAustin(air->latitude, air->longitude);
}

/*
	Provide sort routine on linked list
*/

void simpleSortTotal(slist* airportArr, int numAirports)
{
  for (int i = 0; i < numAirports; i++) {
    for (int k = i + 1; k < numAirports; k++) {
      if (airDist((Airport*)airportArr->get(i)) > airDist((Airport*)airportArr->get(k))) {
        airportArr->exchg(i, k);
        cout << "flipped " << endl;
      }
    }
  }
}

