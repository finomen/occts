#include "vector.hpp"

namespace OCCTS {


	Vector::Vector(double x, double y, double z) : mVector(x, y, z) {

	}

	const gp_Vec& Vector::get() {
		return mVector.get();
	}


}
