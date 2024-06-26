#include "shape.hpp"

#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>
#include <BRepPrimAPI_MakeCylinder.hxx>
#include <BRepPrimAPI_MakePrism.hxx>
#include <BRepFilletAPI_MakeFillet.hxx>
#include <BRepBuilderAPI_Transform.hxx>
#include <BRepAlgoAPI_Cut.hxx>
#include <BRepAlgoAPI_Fuse.hxx>
#include <STEPControl_Reader.hxx>
#include <gp_Trsf.hxx>

namespace OCCTS {

	template<typename T>
	Shape::Shape(T&& shape) : mShape(std::forward<T>(shape)) {

	}

	Shape^ Shape::Box(double dx, double dy, double dz) {
		return gcnew Shape(BRepPrimAPI_MakeBox(dx, dy, dz).Shape());
	}

	Shape^ Shape::Sphere(double r) {
		return gcnew Shape(BRepPrimAPI_MakeSphere(r).Shape());
	}

	Shape^ Shape::Cylinder(double r, double h) {
		return gcnew Shape(BRepPrimAPI_MakeCylinder(r, h).Shape());
	}

	Shape^ Shape::Prism(Face^ face, Vector^ dir) {
		return gcnew Shape(BRepPrimAPI_MakePrism(face->get(), dir->get()).Shape());
	}

	Shape^ Shape::Fillet(System::Collections::Generic::IEnumerable<Edge^>^ edges, double radius) {
		BRepFilletAPI_MakeFillet fillet(mShape.get());
		auto it = edges->GetEnumerator();
		while (it->MoveNext()) {
			fillet.Add(radius, it->Current->get());
		}
		return gcnew Shape(fillet.Shape());
	}

	Shape^ Shape::Move(Vector^ vector) {
		gp_Trsf trsf;
		trsf.SetTranslation(vector->get());
		BRepBuilderAPI_Transform xform(mShape.get(), trsf);
		return gcnew Shape(xform.Shape());
	}

	Shape^ Shape::Rotate(Point^ orig, Vector^ dir, double ang) {
		gp_Trsf trsf;
		trsf.SetRotation(gp_Ax1(orig->get(), dir->get()), ang);
		BRepBuilderAPI_Transform xform(mShape.get(), trsf);
		return gcnew Shape(xform.Shape());
	}

	Shape^ Shape::Mirror(Point^ orig, Vector^ dir) {
		gp_Trsf trsf;
		trsf.SetMirror(gp_Ax2(orig->get(), dir->get()));
		BRepBuilderAPI_Transform xform(mShape.get(), trsf);
		return gcnew Shape(xform.Shape());
	}

	

	Shape^ Shape::Cut(Shape^ tool) {
		return gcnew Shape(BRepAlgoAPI_Cut(mShape.get(), tool->get()).Shape());
	}

	Shape^ Shape::Merge(Shape^ tool) {
		return gcnew Shape(BRepAlgoAPI_Fuse(mShape.get(), tool->get()).Shape());
	}

	Shape^ Shape::LoadStep(System::String^ stepData) {
		using System::Runtime::InteropServices::Marshal;
		std::istringstream iss((const char*)(Marshal::StringToHGlobalAnsi(stepData)).ToPointer());
		STEPControl_Reader Reader;
		Reader.ReadStream("step", iss);
		Reader.TransferRoots();
		return gcnew Shape(Reader.OneShape());
	}
}