#pragma once

#include <gp_Vec.hxx>

#include "wrapper.hpp"

namespace OCCTS {

	public ref class Vector {
	public:
		Vector(double x, double y, double z);

		const gp_Vec& get();
	private:
		Wrapper<gp_Vec> mVector;
	};

}
