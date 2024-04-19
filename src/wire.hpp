#pragma once

#include <TopoDS_Wire.hxx>

#include "wrapper.hpp"
#include "point.hpp"

namespace OCCTS {

	public ref class Wire {
	private:
		template<typename T>
		Wire(T&& wire);
	public:
		static Wire^ Polygon(System::Collections::Generic::IEnumerable<Point^>^ points);

		const TopoDS_Wire& get();
	private:
		Wrapper<TopoDS_Wire> mWire;
	};

}
