
ADD_LIBRARY(pmvs2 SHARED pmvs2.cc )

TARGET_LINK_LIBRARIES(pmvs2 pmvs_lib image_lib numeric_lib ${PMVS_LIBRARIES} nlopt tinycthread -llog -ldl)

ADD_LIBRARY(genOption SHARED  genOption.cc)
TARGET_LINK_LIBRARIES(genOption  -llog -ldl)

ADD_LIBRARY(cmvs SHARED cmvs.cc)
TARGET_LINK_LIBRARIES(cmvs cmvs_lib image_lib graclus_lib ${PMVS_LIBRARIES} tinycthread -ldl -llog)
