#pragma once

#include <TDocStd_Document.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_ColorTool.hxx>
#include <XCAFApp_Application.hxx>

#include "shape.hpp"
#include "wrapper.hpp"

namespace OCCTS {

	public ref class Assembly {

	public:
		Assembly();

		Assembly^ Add(Shape^ shape, System::String^ name, System::Drawing::Color^ color);

		System::String^ MakeStep();
	private:
		bool doInit();
	private:
		Wrapper<Handle(TDocStd_Document)> mDoc;
		Wrapper<Handle(XCAFApp_Application)> mApp;
		bool mInit;
		Wrapper<Handle(XCAFDoc_ShapeTool)> mAssembly;
		Wrapper<Handle(XCAFDoc_ColorTool)> mColors;

	};

}