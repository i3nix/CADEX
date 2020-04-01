#define _USE_MATH_DEFINES
#include <cmath>
#include "Curves.h"
#include <chrono>
#include <random>

namespace curves 
{
	//Curve

	Curve::Curve() {}
	
	Curve::~Curve() {}

	//Circle

	Circle::Circle(const double radius) : r(radius)
	{
		if (radius <= 0)
			throw "radii must be positive";
	}

	Circle::~Circle() {}

	Point Circle::GetPoint(const double t) const
	{
		Point p;
		p.x = r * cos(t);
		p.y = r * sin(t);
		p.z = 0;
		return p;
	}

	Point Circle::GetDerivative(const double t) const
	{
		Point p;
		p.x = -r * sin(t);
		p.y = r * cos(t);
		p.z = 0;
		return p;
	}

	double Circle::GetRadius() const
	{
		return r;
	}

	//Ellipse

	Ellipse::Ellipse(const double radiiX, const double radiiY) : rX(radiiX), rY(radiiY)
	{
		if (radiiX <= 0 || radiiY <= 0)
			throw "radii must be positive";
	}
	Ellipse::~Ellipse() {}

	Point Ellipse::GetPoint(const double t) const
	{
		Point p;
		p.x = rX * cos(t);
		p.y = rY * sin(t);
		p.z = 0;
		return p;
	}

	Point Ellipse::GetDerivative(const double t) const
	{
		Point p;
		p.x = -rX * sin(t);
		p.y = rY * cos(t);
		p.z = 0;
		return p;
	}

	//Helix

	Helix::Helix(const double radius, const double step) : r(radius), step(step)
	{
		if (radius <= 0)
			throw "radii must be positive";
	}

	Helix::~Helix() {}

	Point Helix::GetPoint(const double t) const
	{
		Point p;
		p.x = r * cos(t);
		p.y = r * sin(t);
		p.z = step / (2 * M_PI) * t;
		return p;
	}

	Point Helix::GetDerivative(const double t) const
	{
		Point p;
		p.x = -r * sin(t);
		p.y = r * cos(t);
		p.z = step / (2 * M_PI);
		return p;
	}
		
	double CurveRandomizer::GetRadius()
	{
		static std::mt19937 gen((unsigned int)time(0));
		static std::uniform_real_distribution<double> RadiusGen(0.1, 10.0);
		return RadiusGen(gen);
	}

	double CurveRandomizer::GetStep()
	{
		static std::mt19937 gen((unsigned int)time(0));
		static std::uniform_real_distribution<double> StepGen(-10.0, 10.0);
		return StepGen(gen);
	}

	std::shared_ptr<Curve> CircleCreator::Create() const
	{
		return std::make_shared<Circle>(Circle(CurveRandomizer::GetRadius()));
	}

	std::shared_ptr<Curve> EllipseCreator::Create() const
	{
		double a = CurveRandomizer::GetRadius();
		double b;
		do {
			b = CurveRandomizer::GetRadius();
		} while (a == b);
		if (a < b)
			std::swap(a, b);
		return std::make_shared<Ellipse>(Ellipse(a,b));
	}

	std::shared_ptr<Curve> HelixCreator::Create() const
	{
		double s;
		do
		{
			s = CurveRandomizer::GetStep();
		} while (s == 0);
		return std::make_shared<Helix>(Helix(CurveRandomizer::GetRadius(), s));
	}
}
