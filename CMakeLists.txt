cmake_minimum_required(VERSION 4.0)
project(TEP)

set(CMAKE_CXX_STANDARD 98)

# Lista 1
add_executable(Lista1
        Lista1/main.cpp
        Lista1/ConstValues.h
        Lista1/Table.cpp
        Lista1/Table.h
        Lista4/Tree/EquationTree.cpp
)

# Lista 2
add_executable(Lista2
        Lista2/Main.cpp
)

# Lista 3
add_executable(Lista3
        Lista3/Main.cpp
        Lista3/Nodes/Node.cpp
        Lista3/Nodes/Node.h
        Lista3/EquationTree.cpp
        Lista3/EquationTree.h
        Lista3/Nodes/VarNode.h
        Lista3/Nodes/VarNode.cpp
        Lista3/Nodes/ConstNode.cpp
        Lista3/Nodes/ConstNode.h
        Lista3/Nodes/OperatorNodes/AddOpNode.cpp
        Lista3/Nodes/OperatorNodes/AddOpNode.h
        Lista3/Nodes/OperatorNodes/MinOpNode.cpp
        Lista3/Nodes/OperatorNodes/MinOpNode.h
        Lista3/Nodes/OperatorNodes/MultOpNode.cpp
        Lista3/Nodes/OperatorNodes/MultOpNode.h
        Lista3/Nodes/OperatorNodes/DivOpNode.cpp
        Lista3/Nodes/OperatorNodes/DivOpNode.h
        Lista3/Nodes/BinominalOperatorNode.cpp
        Lista3/Nodes/BinominalOperatorNode.h
        Lista3/Nodes/MonominalOperatorNode.cpp
        Lista3/Nodes/MonominalOperatorNode.h
        Lista3/Parser.cpp
        Lista3/Parser.h
        Lista3/Nodes/OperatorNodes/SinOpNode.cpp
        Lista3/Nodes/OperatorNodes/SinOpNode.h
        Lista3/Nodes/OperatorNodes/CosOpNode.cpp
        Lista3/Nodes/OperatorNodes/CosOpNode.h
)

# Lista4
add_executable(Lista4
        Lista4/main.cpp
        Lista4/Result.tpp
        Lista4/Error.cpp
        Lista4/Error.h
        Lista4/Tree/Nodes/Node.cpp
        Lista4/Tree/Nodes/Node.h
        Lista4/Tree/EquationTree.cpp
        Lista4/Tree/EquationTree.h
        Lista4/Tree/Nodes/VarNode.h
        Lista4/Tree/Nodes/VarNode.cpp
        Lista4/Tree/Nodes/ConstNode.cpp
        Lista4/Tree/Nodes/ConstNode.h
        Lista4/Tree/Nodes/OperatorNodes/AddOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/AddOpNode.h
        Lista4/Tree/Nodes/OperatorNodes/MinOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/MinOpNode.h
        Lista4/Tree/Nodes/OperatorNodes/MultOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/MultOpNode.h
        Lista4/Tree/Nodes/OperatorNodes/DivOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/DivOpNode.h
        Lista4/Tree/Nodes/BinominalOperatorNode.cpp
        Lista4/Tree/Nodes/BinominalOperatorNode.h
        Lista4/Tree/Nodes/MonominalOperatorNode.cpp
        Lista4/Tree/Nodes/MonominalOperatorNode.h
        Lista4/Tree/Parser.cpp
        Lista4/Tree/Parser.h
        Lista4/Tree/Nodes/OperatorNodes/SinOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/SinOpNode.h
        Lista4/Tree/Nodes/OperatorNodes/CosOpNode.cpp
        Lista4/Tree/Nodes/OperatorNodes/CosOpNode.h
)