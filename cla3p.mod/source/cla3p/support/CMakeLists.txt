#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	support/imalloc.cpp
	support/utils.cpp
	PARENT_SCOPE)

set(CLA3P_SUPPORT_HPP 
	imalloc.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_SUPPORT_HPP_INSTALL include/cla3p/support)

install(FILES ${CLA3P_SUPPORT_HPP} DESTINATION ${CLA3P_SUPPORT_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
