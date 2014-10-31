#ifndef definitions_h__
#define definitions_h__
#include <string>
#include <vector>
#include <stdint.h>


#define VECTOR_LENGTH_OFFSET      1
#define DATA_OFFSET               2


#define  DATA_START_TAG   0xFFFFFFFF
#define CONTAINER_START_TAG 0xFFFFFFFE

#ifndef WIN32
  #define  CHAR_BIT 8
#endif

typedef uint64_t serilize_data_t;
typedef std::vector<serilize_data_t> SerilizeVector;
#define  UNIT_BYTES  sizeof(serilize_data_t)
#define UNIT_BITS   (sizeof(serilize_data_t)*CHAR_BIT)
//typedef std::string SerilizeVector;
inline serilize_data_t Division_reminder(serilize_data_t numer, serilize_data_t denom){

	return numer - (numer / denom)* denom;
}

#endif // definitions_h__
