############################
###        duklib        ###
###                      ###
############################


set(DUK_LIB "duklib")
  
add_library(${DUK_LIB} STATIC "")


target_include_directories( ${DUK_LIB}
 PRIVATE
   ${CMAKE_CURRENT_SOURCE_DIR}
)

target_sources(${DUK_LIB}
PRIVATE
    duktape.c
    duktape.h
    duk_config.h
    duk_module_duktape.c
    duk_module_duktape.h
    duk_print_alert.c
    duk_print_alert.h
)

##
## compile definitions
##
target_compile_definitions(${DUK_LIB}
 PRIVATE 
  DUK_LIB_LIB
  "$<$<PLATFORM_ID:Windows>:_SBCS>"
  "$<$<PLATFORM_ID:Windows>:WIN32>"
  "$<$<PLATFORM_ID:Windows>:WIN64>"
)

##
## Position independent code in Linux
##
target_compile_options( ${DUK_LIB}
  PRIVATE 
  "$<$<PLATFORM_ID:Linux>:-fPIC>"
  "$<$<PLATFORM_ID:Linux>:-std=c++11>"
  "$<$<PLATFORM_ID:Windows>:/W3>"
)
