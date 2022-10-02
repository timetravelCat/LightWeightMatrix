set(sources
    src/tmp.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/LightWeightMatrix/internal/type_helper.hpp
    include/LightWeightMatrix/internal/type_traits.hpp
    include/LightWeightMatrix/Matrix.hpp
)

set(test_sources
  src/test_type_helper.cpp
  src/Matrix.cpp
  src/Common.cpp
)
