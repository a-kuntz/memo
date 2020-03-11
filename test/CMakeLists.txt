add_executable(memotest
	src/main.cpp
	src/MemorizerTest.cpp
)

target_link_libraries(memotest PRIVATE memo)
target_link_libraries(memotest PRIVATE GTest::Main)

target_compile_features(memotest PRIVATE cxx_variadic_macros)

add_test(NAME memotest
	COMMAND memotest
)
