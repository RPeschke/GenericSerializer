#include "deserializer.hh"
#include <iostream>

using namespace std;

SerilizeVector::iterator findstartTag_container(SerilizeVector::iterator first, SerilizeVector::iterator last)
{
	return std::find(first, last, CONTAINER_START_TAG);
}

SerilizeVector::iterator findstartTag_data(SerilizeVector::iterator first, SerilizeVector::iterator last)
{
	return std::find(first, last, DATA_START_TAG);
}

vectorOfVector* factory(SerilizeVector::iterator first, SerilizeVector::iterator last)
{
	VectorOfContainer* ret = new VectorOfContainer();

	while (first != last)
	{
	//	std::cout <<"last - first " << last-first << std::endl;
		auto first_container = findstartTag_container(first, last);
		auto first_data = findstartTag_data(first, last);

		if (first_data<first_container&&first_data!=last)
		{
			first = first_data;
			serilize_data_t lengthOfdata = *(first + VECTOR_LENGTH_OFFSET);
			auto new_last = first + lengthOfdata;
			ret->m_container.emplace_back(factory_data(first, new_last));
			first = new_last;
		}
		else if (first_data > first_container&&first_container!=last){
			first = first_container;
			serilize_data_t lengthOfdata = *(first + VECTOR_LENGTH_OFFSET);
			auto new_last = first + lengthOfdata;
			ret->m_container.emplace_back(factory(++first, new_last));
			first = new_last;
		}


	}
//	std::cout << *first << std::endl;
//	auto start1 = findstartTag(first, last);
//	std::cout << *(++start1) << std::endl;
	return ret;
}

vectorOfVector* factory(SerilizeVector& in)
{
	return factory(in.begin(), in.end());
}

vectorOfVector* factory_data(SerilizeVector::iterator first, SerilizeVector::iterator last)
{
//	cout << "vector of data" << std::endl;
	VectorOfData* out = new VectorOfData();
	
	out->m_data_begin = first+DATA_OFFSET;
	out->m_data_end = last;
	return out;
}

