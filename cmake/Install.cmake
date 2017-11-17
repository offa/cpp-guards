
install(TARGETS guards EXPORT guards-config DESTINATION include)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/include/" DESTINATION include)
install(EXPORT guards-config DESTINATION share/guards/cmake)

