#ifndef _NLIBVECTOR_
#define _NLIBVECTOR_

#include<cstring>

namespace nlib{
	namespace vector{

		template<class T>
		class Vector{


			public:
				Vector(unsigned int size=0);
				~Vector();
				void backPush(const T &value);
				T backPop();
				T& operator[](const unsigned int index);
				unsigned int count();
			private:
				void resize();
				unsigned int size;
				unsigned int capability;
				static unsigned int init_size;
				static unsigned int step;
				T *ptr;
		};

		template<class T>
		unsigned int Vector<T>::init_size = 15;

		template<class T>
		unsigned int Vector<T>::step = 2;

		template<class T>
		unsigned int Vector<T>::count(){
			return size;
		}

		template<class T>
		Vector<T>::Vector(unsigned int size){
			this->size = size;
			capability = init_size;
			while(capability<size){
				capability = capability*step+1;
			}
			ptr = new T[capability];
		}

		template<class T>
		Vector<T>::~Vector(){
			delete[] ptr;
		}

		template<class T>
		void Vector<T>::backPush(const T &value){
			size++;
			if(size>capability){
				capability = capability*step+1;
				resize();
			}
			ptr[size-1] = value;
		}

		template<class T>
		T Vector<T>::backPop(){
			//if vector is empty,we can't return. it may throw error, but i don't like error 
			//so i just return vevtor[0], hope no code will do this stupid thing to pop a empty vector :(
			if(size==0)
				size++;
			size--;
			return ptr[size];
		}

		template<class T>
		T& Vector<T>::operator[](const unsigned int index){
			if(index<=size-1)
				return ptr[index];
			else
				//if index is out of range,return first element
				return ptr[0];
		}

		template<class T>
		void Vector<T>::resize(){
			T *temp_ptr = new T[capability];
			std::memcpy(temp_ptr,ptr,sizeof(T)*(size-1));
		}

	}
}

#endif