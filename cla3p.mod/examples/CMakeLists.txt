#-----------------------------------------------
# sub-directory setup
#-----------------------------------------------
add_subdirectory(src)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES cmake_list_install/CMakeLists.txt DESTINATION ${CLA3P_EXAMPLES_INSTALL})

if(LINUX)
	install(PROGRAMS example_builder.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	install(PROGRAMS example_builder_i32.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	install(PROGRAMS example_builder_i64.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	if(SIMULICORE_FULL_INSTALL)
		install(PROGRAMS example_executor.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
		install(PROGRAMS example_executor_i32.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
		install(PROGRAMS example_executor_i64.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	endif()
endif()

#-----------------------------------------------
# end
#-----------------------------------------------
