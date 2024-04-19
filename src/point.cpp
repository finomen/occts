#include "point.hpp"

#include <BRep_Tool.hxx>

namespace OCCTS {


	Point::Point(double x, double y, double z) : mPoint(x, y, z) {

	}

	Point::Point(const TopoDS_Vertex& vertex) : mPoint(BRep_Tool::Pnt(vertex)) {

	}

	const gp_Pnt& Point::get() {
		return mPoint.get();
	}


}
