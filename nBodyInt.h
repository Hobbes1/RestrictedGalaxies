#ifndef NBODYINT_H
#define NBODYINT_H

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <math.h>
#include <stdio.h>
#include <iostream>
#define NPOINTS 596


const float pc_per_km = 1.0/3.0857e13;
const float km_per_pc = 3.0857e13;
//const float G = 4.4937e-15;
//const float G = 1.0; // [pc^3] / [M_sun][1.49176e7 year^2]
const float G = 4.5e-8; // [kpc^3] / [10e8 year^2]

float findR(float x[], float y[], float z[]);
void SaveState(float x[], float y[], float z[], 
			   float ax[], float ay[], float az[],
			   float a0[], float a1[],
			   int n, float tnow, FILE* savefile);
/*			   
void SaveState(float x[], float y[], float z[], 
			   int n, float tnow, FILE* savefile);
*/
void R_Step(float x[], float y[], float z[], 
			float vx[], float vy[], float vz[],  
			int n, float dt);

void V_Step(float vx[], float vy[], float vz[], 
			float ax[], float ay[], float az[],
			int n, float dt);

void LeapStep(float x[], float y[], float z[],
			  float vx[], float vy[], float vz[], 
			  float ax[], float ay[], float az[],
			  float a0[], float a1[],
			  float m[], int n, float dt);

void NBodyAccel(float x[], float y[], float z[],
			    float ax[], float ay[], float az[],
				float a0[], float a1[],
				float m[], int n);
#endif
