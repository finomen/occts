#include "assembly.hpp"

#include <sstream>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <BinXCAFDrivers.hxx>
#include <XmlXCAFDrivers.hxx>
#include <TDataStd_Name.hxx>
#include <Quantity_Color.hxx>
#include <STEPCAFControl_Writer.hxx>

namespace OCCTS {

	Assembly::Assembly() : mDoc(), mApp(XCAFApp_Application::GetApplication()), mAssembly(XCAFDoc_DocumentTool::ShapeTool(mDoc.get()->Main())), mInit(doInit()), mColors(XCAFDoc_DocumentTool::ColorTool(mDoc.get()->Main())) {


	}

	bool Assembly::doInit() {
		BinXCAFDrivers::DefineFormat(mApp.get());
		XmlXCAFDrivers::DefineFormat(mApp.get());
		mApp.get()->NewDocument("BinXCAF", mDoc.get());
		return true;
	}

	Assembly^ Assembly::Add(Shape^ shape, System::String^ name, System::Drawing::Color^ color) {
		using System::Runtime::InteropServices::Marshal;
		TDF_Label label = mAssembly.get()->AddShape(shape->get(), true);
		TDataStd_Name::Set(label, (const char*)(Marshal::StringToHGlobalAnsi(name)).ToPointer());
		mColors.get()->SetColor(label, Quantity_Color(color->R / 255.0, color->G / 255.0, color->B / 255.0, Quantity_TOC_RGB), XCAFDoc_ColorGen);
		return this;
	}

	System::String^ Assembly::MakeStep() {
		mAssembly.get()->UpdateAssemblies();
		STEPCAFControl_Writer aStepWriter;
		aStepWriter.Transfer(mDoc.get(), STEPControl_AsIs);
		std::ostringstream aStream;
		aStepWriter.WriteStream(aStream);

		return gcnew System::String(aStream.str().c_str());
	}
}