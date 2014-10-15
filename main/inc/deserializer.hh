#ifndef deserializer_h__
#define deserializer_h__
#include "definitions.hh"
#include <memory>
#include <iostream>
#include <string>
#include <algorithm>

class vectorOfVector{
public:
	virtual SerilizeVector::iterator data_begin() = 0;
	virtual SerilizeVector::iterator data_end() = 0;
	virtual bool isData() const = 0;
	virtual std::shared_ptr<vectorOfVector> getElement(size_t element) = 0;
	virtual size_t size() const = 0;

	virtual void draw(size_t offset=0) const = 0;
};

class VectorOfContainer :public vectorOfVector{
public:
	VectorOfContainer(){}
	bool isData() const{
		return false;
	}
	SerilizeVector::iterator data_begin(){
		return m_dummy.begin();

	}
	SerilizeVector::iterator data_end(){
		return m_dummy.end();
	}
	std::shared_ptr<vectorOfVector> getElement(size_t element){
		return m_container.at(element);
	}
	size_t size() const{
		return m_container.size();
	}

	void draw(size_t offset = 0) const{
		std::cout  <<std::string(offset, ' ') << "<container>" << std::endl;
		for (auto& e:m_container)
		{
			e->draw(offset+2);
		}
		std::cout << std::string(offset, ' ') << "</container>" << std::endl;
	}
	std::vector<std::shared_ptr<vectorOfVector>> m_container;
private:
	SerilizeVector m_dummy;
};

class VectorOfData : public vectorOfVector{
public:
	VectorOfData(){}
	bool isData() const{
		return true;
	}
	SerilizeVector::iterator data_begin(){
		return m_data_begin;
	}
	SerilizeVector::iterator data_end(){
		return m_data_end;
	}
	std::shared_ptr<vectorOfVector> getElement(size_t element){
		return nullptr;
	}
	size_t size() const{
		return m_data_end - m_data_begin;
	}

	void draw(size_t offset = 0) const{
		std::cout << std::string(offset, ' ') << "<data>" << std::endl;
		std::cout << std::string(offset + 2, ' ');
// 			SerilizeVector v(m_data_begin, m_data_end);
// 		//	auto d = reinterpret_cast<float*>(&v[0]);
// 			//std::cout << *(d+3) << std::endl;
// 			const char* it = reinterpret_cast<const char*>(&v[0]);
// 			const char* endIt = it + v.size()*UNIT_BYTES;
// 			std::string str(it, endIt);
// 				//str.erase(std::remove(str.begin(), str.end(), 0), str.end());
// 		std::cout << str;

		for (auto i = m_data_begin; i != m_data_end;++i)
		{
			std::cout << *i << "; ";
		}
		std::cout	<< std::endl;
		std::cout << std::string(offset, ' ') <<"</data>" << std::endl;

	}
	SerilizeVector::iterator m_data_begin, m_data_end;


};



SerilizeVector::iterator findstartTag_container(SerilizeVector::const_iterator first, SerilizeVector::const_iterator last);
SerilizeVector::iterator findstartTag_data(SerilizeVector::const_iterator first, SerilizeVector::const_iterator last);
vectorOfVector* factory(SerilizeVector::iterator first, SerilizeVector::iterator last);
vectorOfVector* factory_data(SerilizeVector::iterator first, SerilizeVector::iterator last);


vectorOfVector* factory(SerilizeVector& in);




#endif // deserializer_h__
