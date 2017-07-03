#include "nBodyInt.h"

using namespace std;

int main(int argc, char *argv[]){

	int n, mstep, nout, nstep;
	float x[NPOINTS], vx[NPOINTS], ax[NPOINTS];
	float y[NPOINTS], vy[NPOINTS], ay[NPOINTS];
	float z[NPOINTS], vz[NPOINTS], az[NPOINTS];
	float a0[NPOINTS], a1[NPOINTS];
	float m[NPOINTS];
	float tnow, dt;

	char filein[20] = {0};
	char fileout[20] = {0};
	char * temp = argv[1];
	strcat(filein, temp);
	strcat(filein, ".data");
	strcat(fileout, temp);
	strcat(fileout, "Run.data");

	FILE *savefile;
	ifstream datafile(filein, ifstream::in);
    savefile = fopen(fileout, "w");
	if(datafile.is_open())
		cout <<"succesfully opened initial and output files"<< endl;

	/* Load pre-generated initial data into arrays */

	std::string line;
	int i = 0; 
	while(getline(datafile, line)){
		std::stringstream linestream(line);
		if(i==0){
			linestream >> n;
			cout << "N = " << n << endl;
		}
		else{	
			linestream >> m[i-1] >> x[i-1] >> y[i-1] >> z[i-1] 
				       >> vx[i-1] >> vy[i-1] >> vz[i-1];
		}
		ax[i-1] = 0.0;
		ay[i-1] = 0.0;
		az[i-1] = 0.0;
		a0[i-1] = 0.0;
		a1[i-1] = 0.0;
		cout <<" saved line " << i << endl;
		i++;
	}
	cout << " n points read is: " << n << endl;
		
	mstep = 6000;
	nout = 6;
	tnow = 0.0;
	// Timesteps are now 1.49176e7 years... ~15 million
	// 0.002 gives ~30,000 years 
	// 0.00335175 gives 50,000.06 years
	dt = 0.00535175;
	float R_i = findR(x,y,z);
	float R_ii = findR(x,y,z);
	int closest_frame;
	bool found = 0;

	for(nstep = 0; nstep < mstep; nstep++){
		if(nstep % nout == 0){
			SaveState(x, y, z, ax, ay, az, a0, a1, n, tnow, savefile); 
		}
		R_i = findR(x,y,z);
		LeapStep(x, y, z, vx, vy, vz, ax, ay, az, a0, a1, m, n, dt);
		cout << "Steps taken: " << nstep << "/" << mstep << " \r";

		R_ii = findR(x,y,z);
		if(R_i < R_ii && found==0){
			closest_frame = nstep;
			found=1;
		}
		cout << "				R is: " << R_ii << "\r";
		cout.flush();
		tnow += dt;
	}
	if(nstep % nout == 0)
		SaveState(x, y, z, ax, ay, az, a0, a1, n, tnow, savefile);	
	cout << "Done making " << mstep << " steps, saving every " << nout << " steps" << endl;
	cout << "init file: " << filein << " out file: " << fileout << endl;
	cout << "closest frame was: " << closest_frame << endl;

	return 0;
}
