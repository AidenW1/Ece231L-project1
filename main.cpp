/*
 *
 *
 *
 *
 *
 *
 */

#include <iostream>
using namespace std;

struct _capacitor
{
	double *time;
	double *voltage;
	double *current;
	double C;
};

typedef struct _capacitor Capacitor;

const double DT = 1e-10;
const double TF = 5e-6;
const int StepT = 50000;
const double R = 1000;
const double CAP = 100e-12;
const double I0 = 1e-2;
const double V0 = 10;


void allocateCapacitor (Capacitor *cap, int n);
void solveConstantCurrent (Capacitor *cap, int n);
void solveConstantVoltage (Capacitor *cap, int n);
void printResults (Capacitor *cap, int n);
void freeCapacitor (Capacitor *cap);

int main()
{
	Capacitor cc;
	Capacitor rc;

	allocateCapacitor(&cc, StepT);
	allocateCapacitor(&rc, StepT);

	solveConstantCurrent(&cc, StepT);
	solveConstantVoltage(&rc, StepT);

	cout << "Constant Current" << endl;
	printResults(&cc, StepT);

	cout << "Constant Voltage" << endl;
	printResults(&rc, StepT);

	freeCapacitor(&cc);
	freeCapacitor(&rc);

	return 0;
}

void allocateCapacitor (Capacitor *cap, int n)
{
	cap->time = new double[n];
	cap->voltage = new double[n];
	cap->current = new double[n];
	cap->C = CAP;
}

void solveConstantCurrent (Capacitor *cap, int n)
{
	cap->time[0] = 0;
	cap->voltage[0] = 0;
	cap->current[0] = I0;

	for (int i = 1; i < n; i++)
	{
		cap->time[i] = i * DT;
		cap->current[i] = I0;
		cap->voltage[i] = cap->voltage[i-1] + cap->current[i-1] * DT / cap->C;
	}
}

void solveConstantVoltage (Capacitor *cap, int n)
{	
	cap->time[0] = 0;
	cap->voltage[0] = 0;
	cap->current[0] = I0;

	for (int i = 1; i < n; i++)
	{
		cap->time[i] = i * DT;
		cap->current[i] = cap->current[i-1] - cap->current[i-1] * DT / ( R * cap->C );
		cap->voltage[i] = V0 - cap->current[i] * R;
	}
}

void printResults (Capacitor *cap, int n)
{
	int i = 0;
	while (i < n)
	{
		cout << cap->time[i] << "  " << cap->voltage[i] << "  " << cap->current[i] << endl;
		i += 200;
	}
}

void freeCapacitor (Capacitor *cap)
{
	delete[] cap->time;
	delete[] cap->voltage;
	delete[] cap->current;
}
