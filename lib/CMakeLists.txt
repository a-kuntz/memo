add_library(memo
	INTERFACE
)

target_include_directories(memo INTERFACE ${CMAKE_CURRENT_LIST_DIR}/include)

target_compile_features(memo INTERFACE cxx_std_17)