#include "nBodyInt.h"

using namespace std;

float findR(float x[], float y[], float z[]){
	float r = 0.0;
	r = pow((pow(x[0]-x[1],2)+pow(y[0]-y[1],2)+pow(z[0]-z[1],2)),0.5);
	return r;
}

void SaveState(float x[], float y[], float z[], 
			   float ax[], float ay[], float az[],
			   float a0[], float a1[],
			   int n, float tnow, FILE* savefile){
		float a_r;
		for(int i = 0; i < n; i++){
			a_r = pow((pow(ax[i],2.0) + pow(ay[i],2.0) + pow(az[i],2.0)), 0.5);
			fprintf(savefile,"%12.6f%s"
					 "%12.6f%s%12.6f%s"
					 "%12.6f%s",
					 x[i],"\t", y[i], "\t", z[i],"\t",
					 a0[i], "\n");
		}
}

		/* Step real space positions a full time-step forward */
void R_Step(float x[], float y[], float z[], 
			float vx[], float vy[], float vz[],  
			int n, float dt){
	for (int i = 0; i < n; i++){
		x[i] = x[i] + dt * vx[i];
		y[i] = y[i] + dt * vy[i];
		z[i] = z[i] + dt * vz[i];
	}
}

		/* Step the velocity half a time-step forward */
void V_Step(float vx[], float vy[], float vz[], 
			float ax[], float ay[], float az[],
			int n, float dt){
	for (int i = 0; i < n; i++){
		vx[i] = vx[i] + 0.5 * dt * ax[i];
		vy[i] = vy[i] + 0.5 * dt * ay[i];
		vz[i] = vz[i] + 0.5 * dt * az[i];
	}
}

		/* Same leapstep method as before, in 3d and with 
 		 * modulated sub-method calls, acceleration arrays
		 * are now also passed rather than generated each time */
void LeapStep(float x[], float y[], float z[],
			  float vx[], float vy[], float vz[], 
			  float ax[], float ay[], float az[],
			  float a0[], float a1[],
			  float m[], int n, float dt){

	NBodyAccel(x, y, z, ax, ay, az, a0, a1, m, n);
	V_Step(vx, vy, vz, ax, ay, az, n, dt);
	R_Step(x, y, z, vx, vy, vz, n, dt);
	NBodyAccel(x, y, z, ax, ay, az, a0, a1, m, n);
	V_Step(vx, vy, vz, ax, ay, az, n, dt);
}

		/* Pure and un-approximated acceleration 
 		 * generation from each of the N point masses all 
 		 * N others, O(N^2), disgustingly expensive */
void NBodyAccel(float x[], float y[], float z[],
			    float ax[], float ay[], float az[],
				float a0[], float a1[],
				float m[], int n){
	float phi, theta, a, aj;
	for (int i = 0; i < n; i++){
		ax[i] = 0.0;
		ay[i] = 0.0;
		az[i] = 0.0;
		a0[i] = 0.0;
		a1[i] = 0.0;
		for (int j = 0; j < 2; j++){
			if(i!=j){
						
				aj = -G * m[j] / (pow(x[i]-x[j], 2)
								+pow(y[i]-y[j], 2)
								+pow(z[i]-z[j], 2));	

				phi = atan2(y[i]-y[j], x[i]-x[j]);
				theta = atan2(sqrt(pow(y[i]-y[j], 2)
						+pow(x[i]-x[j], 2)), z[i]-z[j]);
				
			
				ax[i] += aj * sin(theta) * cos(phi);
				ay[i] += aj * sin(theta) * sin(phi);
				az[i] += aj * cos(theta);

				if (i%2==1&&j==0){
					a0[i]=aj;
				}
				if (i%2==0&&j==1){
					a0[i]=aj;
				}
			}
		}
	}
}
