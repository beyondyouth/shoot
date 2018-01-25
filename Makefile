DIR_SRC = ./src
DIR_OBJ = ./obj

SOURCE = $(wildcard ${DIR_SRC}/*.cpp)  
OBJECT = $(patsubst %.cpp,${DIR_OBJ}/%.o,$(notdir ${SOURCE}))
	
	
TARGET = main  
BIN_TARGET = ${DIR_OBJ}/${TARGET}  
    
CFLAGS = -g -Wall -I${DIR_SRC} 

${BIN_TARGET}:${OBJECT}  
	g++ -o $@ ${OBJECT} -lpthread -lncurses
   
#生成各个中间文件  
${DIR_OBJ}/%.o:${DIR_SRC}/%.cpp
	g++ $(CFLAGS) -o $@ -c $<
   
.PHONY:clean  
clean:  
	rm -rf $(DIR_OBJ)/*.o
