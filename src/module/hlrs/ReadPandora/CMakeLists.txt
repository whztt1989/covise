using(HDF5)

set(HEADERS
   ReadPandora.h
)
set(SOURCES
   ReadPandora.cpp
)

covise_add_module(IO ReadPandora ${HEADERS} ${SOURCES})
TARGET_LINK_LIBRARIES(ReadPandora ${EXTRA_LIBS})
