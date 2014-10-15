// vectorSerilizer.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "vectorSerializer.h"
#include "deserializer.hh"
using namespace std;


void draw(int x, std::ostream& out, size_t position){
	out << x;
}

typedef  float myTestType;
int main(int argc,char** argv)
{

	generic_container d,d1;
	std::vector<uint64_t> i = { 65, 66};
	std::vector<char> j = { 70, 71, 72};
	std::vector<float> jj = { 74, 73,123};
	std::vector<bool> bb= {1, 1, 0, 0, 1, 0, 1};
	bool b[] = { 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
	myTestType x = 1.2;
	//cout << x << endl;
	//auto z = helper_reinterpreter_cast_to_uint_1<myTestType, sizeof(myTestType)>(x);
	//cout << *z << endl;
//	cout << sizeof(x) << endl;
// 	cout << *(reinterpret_cast<uint32_t*>(&x)) << endl;
	auto intt = (reinterpret_cast<uint32_t*>(&x));
//	auto ads = helper_reinterpreter_cast_to_uint(x);
//	cout << ads <<"size of ads" << sizeof(ads) << endl;

//	auto ddd = *(reinterpret_cast<myTestType*>(&ads));

//	cout << ddd << endl;
	std::pair<uint64_t*, const size_t> pointer_pair(&i[0],2) ;
	auto pointer_pair3 = make_pair(&b[0], (size_t)20);
	auto  pointer_pair1=make_pair(&jj[0], jj.size());
//	cout << sizeof(i[1]) << endl;
//	cout << i.size() *sizeof uint32_t *CHAR_BIT << endl;
	d.push_back(i);
	d.push_back(1);
	d.push_back(pointer_pair3);
	d.push_back(pointer_pair);
	d.push_back(pointer_pair1);
	d.push_back(bb);
	d.push_back("hallo");
	d.push_back(i);
	d.push_back(j);
	d.push_back(j);
	d1.push_back(d);
	d1.push_back(jj);
	d1.push_back(std::move(d));
	SerilizeVector vec;
	serilize(d1,vec);
	
	const char * ptr_begin = reinterpret_cast<const char *>(&vec[0]);
	const char * ptr_end = ptr_begin + vec.size() * UNIT_BYTES / sizeof(char);

// 	auto s = std::string(ptr_begin, ptr_end);
// 	cout << s << endl;
// 
// 	for (auto&e : vec){
// 
// 		cout << e << " ";
// 	}
// 	cout << endl;
	auto t = factory(vec);
//	cout<<*t->getElement(0)->getElement(1)->data_begin()<<endl;
	t->draw();
	return 0;
}

