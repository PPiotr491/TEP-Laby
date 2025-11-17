cmake_minimum_required(VERSION 4.0)
project(TEP)

set(CMAKE_CXX_STANDARD 98)

add_executable(TEP
        Lista1/main.cpp
        Lista1/ConstValues.h
        Lista1/Table.cpp
        Lista1/Table.h
        Lista2/Main.cpp
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
)
