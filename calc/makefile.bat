g++ -c Add.cpp Diff.cpp func.cpp Sub.cpp expression.cpp vector.cpp multiply.cpp expressionOperates.cpp
ar -rc libfile.a Add.o Diff.o func.o Sub.o expression.o vector.o multiply.o expressionOperates.o
g++ -o Main Main.cpp libfile.a 
