#define _USE_MATH_DEFINES
#include <cmath>
#include "Curves.h"
#include <list>
#include <random>
#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;

bool compare(const shared_ptr<curves::Circle> &c1, const shared_ptr<curves::Circle> &c2)
{
	if (c1->GetRadius() < c2->GetRadius())
		return true;
	return false;
}

void Fill(list<shared_ptr<curves::Curve> >& ListOfCurves)
{
	curves::CircleCreator CircleCreator;
	curves::EllipseCreator EllipseCreator;
	curves::HelixCreator HelixCreator;
	curves::CurveCreator* Creators[3];
	Creators[0] = &CircleCreator;
	Creators[1] = &EllipseCreator;
	Creators[2] = &HelixCreator;

	bool CreatorUsed[3] = { false, false, false };

	mt19937 gen((unsigned int)time(0));
	uniform_int_distribution<int> TypeDist(0, 2);

	for (int t = 0; t < 50; t++)
	{
		int type = TypeDist(gen);
		ListOfCurves.push_back(Creators[type]->Create());
		CreatorUsed[type] = true;
	}
	for (int t = 0; t < 3; t++)
		if (!CreatorUsed[t])
			ListOfCurves.push_back(Creators[t]->Create());
}

void Print(list<shared_ptr<curves::Curve> >& ListOfCurves)
{
	cout << "Points and Derivations (t=PI/4):" << endl;

	for (list<shared_ptr<curves::Curve> >::const_iterator it = ListOfCurves.begin(); it != ListOfCurves.end(); it++)
	{
		curves::Point p = (*it)->GetPoint(M_PI / 4);
		curves::Point d = (*it)->GetDerivative(M_PI / 4);
		cout << fixed << setprecision(6) << "X=" << p.x << "\tY=" << p.y << "\tZ=" << p.z << "\tX*=" << d.x << "\tY*=" << d.y << "\tZ*=" << d.z << endl;
	}
}

void Select(list<shared_ptr<curves::Curve> >& ListOfCurves, list<shared_ptr<curves::Circle> >& ListOfCircles)
{
	for (list<shared_ptr<curves::Curve> >::iterator it = ListOfCurves.begin(); it != ListOfCurves.end(); it++)
	{
		if (typeid(**it) == typeid(curves::Circle))
			ListOfCircles.push_back(dynamic_pointer_cast<curves::Circle>(*it));
	}
}

double Compute(list<shared_ptr<curves::Circle> >& ListOfCircles)
{
	double sum = 0;
	for (list<shared_ptr<curves::Circle> >::iterator it = ListOfCircles.begin(); it != ListOfCircles.end(); it++)
		sum += (*it)->GetRadius();
	return sum;
}

int main() 
{
	try
	{
		list<shared_ptr<curves::Curve> > ListOfCurves;
		Fill(ListOfCurves);

		Print(ListOfCurves);

		list<shared_ptr<curves::Circle> > ListOfCircles;
		Select(ListOfCurves, ListOfCircles);

		ListOfCircles.sort(compare);

		double sum = Compute(ListOfCircles);
	}
	catch (const char* c)
	{
		cout << "Exception: " << c << endl;
	}
	return 0;
}
