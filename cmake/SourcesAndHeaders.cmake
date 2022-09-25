set(sources
    src/tmp.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/LightWeightMatrix/type_helper.hpp
)

set(test_sources
  src/test_type_helper.cpp
  src/Matrix.cpp
)
