add_library(tree
        ITreeNode.hpp
        ITree.hpp
        ITemplateTree.hpp
        ITraversal.hpp
        TreeNode.hpp
        BinarySearchTree.hpp
        PreOrder.cpp
        PreOrder.hpp
        InOrder.cpp
        InOrder.hpp
        PostOrder.cpp
        PostOrder.hpp
        TreeConcepts.hpp
)

target_include_directories(tree PUBLIC ${PROJECT_SOURCE_DIR})
