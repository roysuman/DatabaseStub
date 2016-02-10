//Mon Feb  8 12:25:29 IST 2016
#ifndef SINGLETON_H
#define SINGLETON_H
template<typename T>
class Singleton{
	public:
		static T* get_instance( void );
	private:
		static T* local_instance;
};
/*defination*/

template<typename T>
 T* Singleton<T>::local_instance = nullptr;

template<class T>
T* Singleton<T>::get_instance( void ){
	std::cout<<"R U"<<std::endl;
	T *ins = local_instance;
	if ( !ins ){
		ins = new T();
		local_instance = ins;
	}
	return ins;
}




#endif
