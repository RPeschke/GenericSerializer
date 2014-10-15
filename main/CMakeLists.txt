





AUX_SOURCE_DIRECTORY( src EXE_sources )


file(GLOB Demo_HEADERS *.h)
source_group("Headers" FILES ${Demo_HEADERS})

SOURCE_GROUP(Headers  ./main/inc/*.h)


# fill list of header files 
set(vectorSerializer_HEADERS 
 ${PROJECT_SOURCE_DIR}/main/inc/vectorSerializer.h
 ${PROJECT_SOURCE_DIR}/main/inc/serializer_helpers.hh
 ${PROJECT_SOURCE_DIR}/main/inc/reinterpreter_cast_helpers.hh
${PROJECT_SOURCE_DIR}/main/inc/deserializer.hh
${PROJECT_SOURCE_DIR}/main/inc/definitions.hh


  )

SET(MY_INCLUDE_DIRECTORIES ./main/inc ./inc ../../main/inc  )
INCLUDE_DIRECTORIES(  ${MY_INCLUDE_DIRECTORIES} )



add_executable( ${PROJECT_NAME}  ${EXE_sources}  )



SOURCE_GROUP(Headers  inc/*.h)

target_link_libraries( ${PROJECT_NAME} ${EUDAQ_THREADS_LIB} ${ROOT_LIBRARIES} ${ADDITIONAL_LIBRARIES})


INSTALL(TARGETS ${PROJECT_NAME}
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)


