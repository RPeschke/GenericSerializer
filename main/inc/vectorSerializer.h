#ifndef vectorSeriliser_h__
#define vectorSeriliser_h__










#include <cassert>
#include <iostream>
#include <memory>


#include <ostream>

#include "definitions.hh"
#include "serializer_helpers.hh"



/******************************************************************************/
// Library


class object_t {
public:
	template <typename T>
	object_t(T x) : self_(new model<T>(std::move(x)))
	{ }

	object_t(const object_t& x) : self_(x.self_->copy_())
	{ }
	object_t(object_t&& x) :self_(std::move(x.self_)){
#ifdef DEBUG
		std::cout << "calling good move constructor for:";
		self_->draw_(std::cout, 0);
			std::cout<< std::endl;
#endif
	}
	

	object_t& operator=(const object_t& x)
	{
		object_t tmp(x); *this = std::move(tmp); return *this;
	}
	object_t& operator=(object_t&& x) {
		self_ = std::unique_ptr<const concept_t>(std::move(x.self_));
		return *this;
	}

	friend void serilize(const object_t& x, SerilizeVector& outputVector)
	{
		auto last_size = outputVector.size();
		outputVector.push_back(x.self_->START_TAG());
		outputVector.push_back(0);
		
		x.self_->serilize_(outputVector);
		outputVector[last_size + VECTOR_LENGTH_OFFSET] = outputVector.size() - last_size;
	
		
	}
private:
	struct concept_t {
		virtual ~concept_t() = default;
		virtual concept_t* copy_() const = 0;
		virtual serilize_data_t START_TAG() const = 0;
		virtual void serilize_(SerilizeVector& outputVector) const = 0;
		
	};
	template <typename T>
	struct model : concept_t {
		model(T x) : data_(std::move(x)) { }
		concept_t* copy_() const { 
			std::cout << "evil Constructor of model" << std::endl; 
			return new model(*this); 
		}


		void serilize_(SerilizeVector& outputVector) const{
			
			 helper_serilize(data_,outputVector);
		}
		serilize_data_t START_TAG() const{
			return helper_START_TAG<T>();
		}
		T data_;
	};

	std::unique_ptr<const concept_t> self_;
};

using generic_container = std::vector < object_t > ;



void serilize(const generic_container& x, SerilizeVector& out)
{
	

	for (auto& e : x) {
		serilize(e, out);
		
	}
		
}


void helper_serilize(const generic_container& x, SerilizeVector& outputVector){

	serilize(x, outputVector);

}

template <>
serilize_data_t helper_START_TAG<const generic_container>(){
	return CONTAINER_START_TAG;
}
template <>
serilize_data_t helper_START_TAG<generic_container>(){
	return CONTAINER_START_TAG;
}


#endif // vectorSeriliser_h__