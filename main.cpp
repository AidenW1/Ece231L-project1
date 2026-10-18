/*Header comment:
 * Aiden W. Ece231l 1BW
 * Project1
 * Does the math on a charging capacitor with constant current and constant voltage
 *
 * General information on AI Use:
 * Use Claude to again help with memory allocation espessialy getting free and delete mixed up now
 * also had to use it for the sytaxing of c++ and how it differes from java
 * you can see that in the prototypes at the top becuase i like having main be at the top
 * and my methods be below in at the bottom
 * struct just like a class from java but different of course
 *
 *claud informed me about the using namespace std; so that was nice
 *also using it for the new printf for std::out makes sense how to use well
 *
 *
 */
#include <iostream>
using namespace std;
//from here to main general housekeeping getting laying the groundwork for the program
//creating the struct, global variables, and prototypes
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

//main method does the constructor, then running the methods then printing them out
//pretty self explanitory for this one also weird how c++'s main is an int and not void
int main()
{
	Capacitor cc;
	Capacitor rc;

	allocateCapacitor(&cc, StepT);
	allocateCapacitor(&rc, StepT);

	solveConstantCurrent(&cc, StepT);
	solveConstantVoltage(&rc, StepT);

	cout << "Constant Current\n" << endl;
	printResults(&cc, StepT);

	cout << "Constant Voltage" << endl;
	printResults(&rc, StepT);

	freeCapacitor(&cc);
	freeCapacitor(&rc);

	return 0;
}

//Memory allocator, "AI helped"
//more or less gave me this whole method one slap over the head at a time
void allocateCapacitor (Capacitor *cap, int n)
{
	cap->time = new double[n];
	cap->voltage = new double[n];
	cap->current = new double[n];
	cap->C = CAP;
}

//solver had to get help setting up the pointers correctly becuse were not calling a variable
//but instead pointing to the memorty location to update and read data
//still getting use to this but the for loop and math was basically given for free
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

//same thing here with the pointers
//and looking at the memorty and not a variable with the information
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

//just like all the print methods i have written before this but
//now with a new flavor of printf i have to learn :*)
void printResults (Capacitor *cap, int n)
{
	int i = 0;
	while (i < n)
	{
		cout << cap->time[i] << "  " << cap->voltage[i] << "  " << cap->current[i] << endl;
		i += 200;
	}
}

//again ai pretty much wrote this whole method because this is a forien concept to a javian
void freeCapacitor (Capacitor *cap)
{
	delete[] cap->time;
	delete[] cap->voltage;
	delete[] cap->current;
}
