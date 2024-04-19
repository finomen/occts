#pragma once

#include <TopExp_Explorer.hxx>

#include "wrapper.hpp"

namespace OCCTS {


	template<TopAbs_ShapeEnum query, typename T, typename W>
	public ref class Explorer : public System::Collections::Generic::IEnumerable<W^> {
	public:
		ref class Enumerator : public System::Collections::Generic::IEnumerator<W^> {

		public:
			Enumerator(const TopoDS_Shape& shape) : mExplorer(shape, query) {}

			~Enumerator() {
				this->!Enumerator();
			}

			!Enumerator() {
				mExplorer.~Wrapper();
			}

			virtual bool MoveNext()
			{
				if (!mExplorer->More()) {
					return false;
				}

				if (!mStarted) {
					mStarted = true;
				}
				else {
					mExplorer->Next();
				}
				return true;
			}
			virtual void Reset()
			{
				throw gcnew System::NotImplementedException();
			}

			virtual property W^ Current {
				virtual W^ get() {
					return gcnew W(*static_cast<const T*>(&mExplorer->Current()));
				}
			}

			virtual property Object^ Current2
			{
				virtual Object^ get() = System::Collections::IEnumerator::Current::get
				{
						return gcnew W(*static_cast<const T*>(&mExplorer->Current()));
				}
			};

		private:
			Wrapper<TopExp_Explorer> mExplorer;
			bool mStarted = false;
		};


	public:
		Explorer(const TopoDS_Shape& shape) : mShape(shape) {}

		virtual System::Collections::Generic::IEnumerator<W^>^ GetEnumerator()
		{
			return gcnew Enumerator(mShape.get());
		}

		virtual System::Collections::IEnumerator^ GetEnumerator2() new sealed = System::Collections::IEnumerable::GetEnumerator
		{
			return gcnew Enumerator(mShape.get());
		}

	private:
		Wrapper<TopoDS_Shape> mShape;
	};

}