#--------------------------------------------------------
# The CMakeLists.txt for:                       pNodeReportParse2
# Author(s):                              Carter Fendley
#--------------------------------------------------------

SET(SRC
  NodeReportParse2.cpp
  NodeReportParse2_Info.cpp
  main.cpp
)

ADD_EXECUTABLE(pNodeReportParse2 ${SRC})

TARGET_LINK_LIBRARIES(pNodeReportParse2
   ${MOOS_LIBRARIES}
   apputil
   mbutil
   m
   pthread)

