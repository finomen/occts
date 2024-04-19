#include "face.hpp"

#include <BRepBuilderAPI_MakeFace.hxx>

namespace OCCTS {

	Face::Face(Wire^ wire) : mFace(BRepBuilderAPI_MakeFace(wire->get())) {

	}

	const TopoDS_Face& Face::get() {
		return mFace.get();
	}

}
