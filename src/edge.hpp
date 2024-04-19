#pragma once

#include <TopoDS_Edge.hxx>

#include "wrapper.hpp"
#include "point.hpp"
#include "explorer.hpp"

namespace OCCTS {

	public ref class Edge {
	public:
		Edge(const TopoDS_Edge& edge);

		const TopoDS_Edge& get();

		property System::Collections::Generic::IEnumerable<Point^>^ Points {
			System::Collections::Generic::IEnumerable<Point^>^ get() {
				return gcnew Explorer<TopAbs_VERTEX, TopoDS_Vertex, Point>(mEdge.get());
			}
		};

	private:
		Wrapper<TopoDS_Edge> mEdge;
	};

}
