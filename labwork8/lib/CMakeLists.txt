add_library(bst INTERFACE bst.hpp)
add_library(container INTERFACE container.hpp iterator.hpp)

target_link_libraries(container INTERFACE bst)