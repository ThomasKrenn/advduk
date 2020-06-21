############################
###    jx pretty from    ###
###     duk examples     ###
############################

##
## JXPRETTY
##
set(JXPRETTY "jxpretty")


add_executable(${JXPRETTY} "")

target_include_directories( ${JXPRETTY}
 PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_SOURCE_DIR}/duklib
)

target_sources(${JXPRETTY}
PRIVATE

   jxpretty.cpp
   
)

##
## compile definitions
##
target_compile_definitions(${JXPRETTY}
 PRIVATE 
 JXPRETTY
  "$<$<PLATFORM_ID:Windows>:_SBCS>"
  "$<$<PLATFORM_ID:Windows>:WIN32>"
  "$<$<PLATFORM_ID:Windows>:WIN64>"
)

##
## Position independent code in Linux
##
target_compile_options( ${JXPRETTY}
  PRIVATE 
  "$<$<PLATFORM_ID:Linux>:-fPIC>"
  "$<$<PLATFORM_ID:Linux>:-std=c++11>"
  "$<$<PLATFORM_ID:Windows>:/W3>"
)

target_link_libraries(${JXPRETTY}
 PRIVATE
 duklib
)