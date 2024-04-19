#pragma once

#include <gp_Pnt.hxx>
#include <TopoDS_Vertex.hxx>

#include "wrapper.hpp"

namespace OCCTS {

	public ref class Point {
	public:
		Point(double x, double y, double z);
		Point(const TopoDS_Vertex& vertex);

		const gp_Pnt& get();

		property double X {
			double get() { return mPoint->Coord(1); }
		};

		property double Y {
			double get() { return mPoint->Coord(2); }
		};

		property double Z {
			double get() { return mPoint->Coord(3); }
		};
	private:
		Wrapper<gp_Pnt> mPoint;
	};

}
