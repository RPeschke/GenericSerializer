#ifndef serilize_helpers_h__
#define serilize_helpers_h__
#include "definitions.hh"

#include <iostream>
#include <cstring>


//////////////////////////////////////////////////////////////////////////
// Template declarations											////// 
//////////////////////////////////////////////////////////////////////////



template <typename T>
serilize_data_t  helper_START_TAG();

template <typename T>
void helper_serilize(const std::vector<T>& x, SerilizeVector& outputVector);


template <typename T>
void helper_serilize(const std::pair< const T*, const size_t>& x, SerilizeVector& outputVector);



template <typename T>
void helper_serilize(const std::pair< T*, size_t>& x, SerilizeVector& outputVector);

template <typename T>
void helper_serilize(const std::pair<const T*, size_t>& x, SerilizeVector& outputVector);


template <typename T>
void helper_serilize(const std::pair< T*, const size_t>& x, SerilizeVector& outputVector);

template <typename Iterator_t>
void helper_serilize_bool(Iterator_t begin_it, size_t size, SerilizeVector& outputVector);

template <typename IntType>
void helper_serilize_intTypes(IntType in_data, SerilizeVector& outputVector);


template <>
void helper_serilize(const std::pair< const bool*, const size_t>& x, SerilizeVector& outputVector);

template <>
void helper_serilize(const std::vector<bool>& t, SerilizeVector& outputVector);


void helper_serilize(const char* data_, SerilizeVector& outputVector);

void helper_serilize(int data_, SerilizeVector& outputVector);


//////////////////////////////////////////////////////////////////////////
// Template Definitions												//////
//////////////////////////////////////////////////////////////////////////

template <typename T>
serilize_data_t  helper_START_TAG(){
	return DATA_START_TAG;
}

template <typename T>
void helper_serilize(const std::vector<T>& x, SerilizeVector& outputVector){
	helper_serilize(std::make_pair(&x[0], x.size()), outputVector);
}




template <typename T>
void helper_serilize(const std::pair< const T*, const size_t>& x, SerilizeVector& outputVector){
	const serilize_data_t * ptr_begin = reinterpret_cast<const serilize_data_t *>(x.first);
	const serilize_data_t * ptr_end = ptr_begin + x.second * sizeof(T) / UNIT_BYTES;
	serilize_data_t bitsWritten = x.second * sizeof(T)*CHAR_BIT;



	outputVector.insert(outputVector.end(), ptr_begin, ptr_end);

	serilize_data_t reminder = Division_reminder(bitsWritten, UNIT_BITS);

	if (reminder)
	{

		serilize_data_t overEvent = reminder / (sizeof(T)*CHAR_BIT);
		size_t startindex = x.second - overEvent;
		std::vector<T> dummy;

		for (size_t i = startindex; i < x.second; ++i)
		{
			dummy.push_back(*(x.first + i));
		}
		while (dummy.size()*sizeof(T)*CHAR_BIT < UNIT_BITS)
		{
			dummy.push_back(0);
		}

		helper_serilize(dummy, outputVector);
	}

}



template <typename T>
void helper_serilize(const std::pair< T*, size_t>& x, SerilizeVector& outputVector){

	helper_serilize(std::pair<const T*, const size_t>(x.first, x.second), outputVector);


}
template <typename T>
void helper_serilize(const std::pair<const T*, size_t>& x, SerilizeVector& outputVector){

	helper_serilize(std::pair<const T*, const size_t>(x.first, x.second), outputVector);


}
template <typename T>
void helper_serilize(const std::pair< T*, const size_t>& x, SerilizeVector& outputVector){

	helper_serilize(std::pair<const T*, const size_t>(x.first, x.second), outputVector);


}

template <typename Iterator_t>
void helper_serilize_bool(Iterator_t begin_it, size_t size, SerilizeVector& outputVector){

	size_t j = 0;
	serilize_data_t dummy = 0;

	bool saved = false;
	for (auto i = begin_it; i < begin_it + size; ++i)
	{
		saved = false;
		dummy += *i << (j % UNIT_BITS);
	//	cout << *(i);
		if ((j % UNIT_BITS) == UNIT_BITS - 1)
		{
			outputVector.push_back(dummy);
			dummy = 0;
			saved = true;
		}
		++j;
	}
	if (saved == false)
	{
		outputVector.push_back(dummy);
	}
	//cout << endl;


}

template <typename IntType>
void helper_serilize_intTypes(IntType in_data, SerilizeVector& outputVector){
    helper_serilize(std::make_pair(&in_data, (size_t)1), outputVector);

}

template <>
void helper_serilize(const std::pair< const bool*, const size_t>& x, SerilizeVector& outputVector){

	helper_serilize_bool(x.first, x.second, outputVector);
	
}

template <>
void helper_serilize(const std::vector<bool>& t, SerilizeVector& outputVector){
	
	helper_serilize_bool(t.begin(), t.size(), outputVector);
}


void helper_serilize(const char* data_, SerilizeVector& outputVector){

	helper_serilize(std::make_pair(data_, strlen(data_)), outputVector);

}

void helper_serilize(int data_, SerilizeVector& outputVector){



	helper_serilize_intTypes(data_, outputVector);
}


#endif // serilize_helpers_h__
