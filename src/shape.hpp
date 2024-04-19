#pragma once

#include <TopoDS_Shape.hxx>

#include "wrapper.hpp"

#include "face.hpp"
#include "vector.hpp"
#include "explorer.hpp"
#include "edge.hpp"

namespace OCCTS {

	public ref class Shape {
	private:
		template<typename T>
		Shape(T&& shape);
	public:
		static Shape^ Box(double dx, double dy, double dz);
		static Shape^ Prism(Face^ face, Vector^ dir);

		property System::Collections::Generic::IEnumerable<Edge^>^ Edges {
			System::Collections::Generic::IEnumerable<Edge^>^ get() {
				return gcnew Explorer<TopAbs_EDGE, TopoDS_Edge, Edge>(mShape.get());
			}
		};

		const TopoDS_Shape& get() {
			return mShape.get();
		}

		Shape^ Fillet(System::Collections::Generic::IEnumerable<Edge^>^ edges, double radius);

		Shape^ Move(Vector^ vector);
		Shape^ Rotate(Point^ orig, Vector^ dir, double ang);

		Shape^ Cut(Shape^ tool);

	private:
		Wrapper<TopoDS_Shape> mShape;
	};

}
