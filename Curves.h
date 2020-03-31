#pragma once
#include <utility>
#include <memory>

namespace curves{

	typedef struct
	{
		double x;
		double y;
		double z;
	} Point;

	enum class CurveType {CIRCLE, ELLIPSE, HELIX};

	class Curve
	{
	public:
		Curve(CurveType t);
		virtual ~Curve();

		virtual Point GetPoint(const double t) const = 0;
		virtual Point GetDerivative(const double t) const = 0;

		CurveType GetType() const;
	private:
		CurveType type;
	};
	
	class Circle : public Curve
	{
	public:
		Circle(const double radius);
		~Circle();

		Point GetPoint(const double t) const;
		Point GetDerivative(const double t) const;

		double GetRadius() const;
	private:
		double r;
	};

	class Ellipse : public Curve
	{
	public:
		Ellipse(const double radiiX, const double radiiY);
		~Ellipse();

		Point GetPoint(const double t) const;
		Point GetDerivative(const double t) const;
	private:
		double rX;
		double rY;
	};

	class Helix : public Curve
	{
	public:
		Helix(const double radius, const double step);
		~Helix();

		Point GetPoint(const double t) const;
		Point GetDerivative(const double t) const;
	private:
		double r;
		double step;
	};

	class CurveCreator
	{
	public:
		virtual std::shared_ptr<Curve> Create() const = 0;
	};

	class CircleCreator : public CurveCreator
	{
	public:
		std::shared_ptr<Curve> Create() const;
	};

	class EllipseCreator : public CurveCreator
	{
	public:
		std::shared_ptr<Curve> Create() const;
	};

	class HelixCreator : public CurveCreator
	{
	public:
		std::shared_ptr<Curve> Create() const;
	private:
	};

	class CurveRandomizer
	{
	public:
		static double GetRadius();
		static double GetStep();
	};
}

