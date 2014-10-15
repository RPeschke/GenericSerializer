#ifndef reinterpreter_cast_helpers_h__
#define reinterpreter_cast_helpers_h__

template <typename T>
auto helper_reinterpreter_cast_to_uint(T t) ->decltype(helper_reinterpreter_cast_to_uint_struct<T, sizeof(T)>(t).value) {
	return helper_reinterpreter_cast_to_uint_struct<T, sizeof(T)>(t).value;
}


template <typename T, size_t n>
struct helper_reinterpreter_cast_to_uint_struct
{
	uint64_t value;
	helper_reinterpreter_cast_to_uint_struct(T t){
		std::cout << "never use the default one" << std::endl;

		value = reinterpret_cast<uint64_t>(&t);
	}
};



template <typename T>
struct helper_reinterpreter_cast_to_uint_struct < T, 1 >
{
	typedef uint8_t uint_type;
	uint_type value;
	helper_reinterpreter_cast_to_uint_struct(T t){
		value = *reinterpret_cast<uint_type*>(&t);
	}
};

template <typename T>
struct helper_reinterpreter_cast_to_uint_struct < T, 2 >
{
	typedef uint16_t uint_type;
	uint_type value;
	helper_reinterpreter_cast_to_uint_struct(T t){
		value = *reinterpret_cast<uint_type*>(&t);
	}
};
template <typename T>
struct helper_reinterpreter_cast_to_uint_struct < T, 4 >
{
	typedef uint32_t uint_type;
	uint_type value;
	helper_reinterpreter_cast_to_uint_struct(T t){
		value = *reinterpret_cast<uint_type*>(&t);
	}
};
template <typename T>
struct helper_reinterpreter_cast_to_uint_struct < T, 8 >
{
	typedef uint64_t uint_type;
	uint_type value;
	helper_reinterpreter_cast_to_uint_struct(T t){
		value = *reinterpret_cast<uint_type*>(&t);
	}
};

#endif // reinterpreter_cast_helpers_h__
