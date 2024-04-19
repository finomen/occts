#pragma once

namespace OCCTS {

	template<typename T>
	public ref class Wrapper {
	public:
		template<typename... Args>
		explicit Wrapper(Args &&... args) : mPtr(new T(std::forward<Args>(args)...)) {}

		~Wrapper() {
			(*this).!Wrapper();
		}

		!Wrapper() {
			delete mPtr;
			mPtr = nullptr;
		}

		T* operator->() {
			return mPtr;
		}

		T& get() {
			return *mPtr;
		}

	private:
		T* mPtr;
	};

}