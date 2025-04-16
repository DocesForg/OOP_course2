add_library(bst INTERFACE
        BST.hpp
        BstIterator.hpp
        BstConcepts.hpp
)

target_link_libraries(bst INTERFACE tree)

target_include_directories(bst INTERFACE ${PROJECT_SOURCE_DIR})
