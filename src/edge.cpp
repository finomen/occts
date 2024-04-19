#include "edge.hpp"

namespace OCCTS {

	Edge::Edge(const TopoDS_Edge& edge) : mEdge(edge) {

	}

	const TopoDS_Edge& Edge::get() {
		return mEdge.get();
	}

}
