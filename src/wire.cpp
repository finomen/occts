#include "wire.hpp"

#include <BRepBuilderAPI_MakePolygon.hxx>

namespace OCCTS {

	template<typename T>
	Wire::Wire(T&& wire) : mWire(wire) {}

	Wire^ Wire::Polygon(System::Collections::Generic::IEnumerable<Point^>^ points) {
		auto polygon = BRepBuilderAPI_MakePolygon();
		auto enumerator = points->GetEnumerator();
		while (enumerator->MoveNext()) {
			polygon.Add(enumerator->Current->get());
		}

		polygon.Close();

		return gcnew Wire(polygon.Wire());
	}

	const TopoDS_Wire& Wire::get() {
		return mWire.get();
	}


}
