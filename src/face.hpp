#pragma once

#include <TopoDS_Face.hxx>

#include "wrapper.hpp"
#include "wire.hpp"

namespace OCCTS {

	public ref class Face {
	public:
		Face(Wire^ poly);

		const TopoDS_Face& get();
	private:
		Wrapper<TopoDS_Face> mFace;
	};

}
