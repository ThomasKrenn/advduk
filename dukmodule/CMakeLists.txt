############################
###  simple duk module   ###
###                      ###
############################

##
## DUKMODAPP
##
set(DUKMODAPP "dukmodapp")


add_executable(${DUKMODAPP} "")

target_include_directories( ${DUKMODAPP}
 PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
   ${CMAKE_SOURCE_DIR}/duklib
)

target_sources(${DUKMODAPP}
PRIVATE

   dukmodapp.h
   dukmodapp.cpp

   mydukmod.cpp   
   mydukmod.h
)

##
## compile definitions
##
target_compile_definitions(${DUKMODAPP}
 PRIVATE 
 DUKMODAPP
  "$<$<PLATFORM_ID:Windows>:_SBCS>"
  "$<$<PLATFORM_ID:Windows>:WIN32>"
  "$<$<PLATFORM_ID:Windows>:WIN64>"
)

##
## Position independent code in Linux
##
target_compile_options( ${DUKMODAPP}
  PRIVATE 
  "$<$<PLATFORM_ID:Linux>:-fPIC>"
  "$<$<PLATFORM_ID:Linux>:-std=c++11>"
  "$<$<PLATFORM_ID:Windows>:/W3>"
)

target_link_libraries(${DUKMODAPP}
 PRIVATE
 duklib
)