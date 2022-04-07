CC = gcc

all: Project1_2 Project1_2_ParentPID Project1_2_getpid Project1_2_pid Project1_2_MaxTree Project1_2_MaxTree_NoPrint Project1_2_MaxTree_NoTree

Project1_2: Project1_2.c
	$(CC) Project1_2.c -o Project1_2

Project1_2_ParentPID: Project1_2_ParentPID.c
	$(CC) Project1_2_ParentPID.c -o Project1_2_ParentPID

Project1_2_getpid: Project1_2_getpid.c
	$(CC) Project1_2_getpid.c -o Project1_2_getpid

Project1_2_pid: Project1_2_pid.c
	$(CC) Project1_2_pid.c -o Project1_2_pid

Project1_2_MaxTree: Project1_2_MaxTree.c
	$(CC) Project1_2_MaxTree.c -o Project1_2_MaxTree

Project1_2_MaxTree_NoPrint: Project1_2_MaxTree_NoPrint.c
	$(CC) Project1_2_MaxTree_NoPrint.c -o Project1_2_MaxTree_NoPrint

Project1_2_MaxTree_NoTree: Project1_2_MaxTree_NoTree.c
	$(CC) Project1_2_MaxTree_NoTree.c -o Project1_2_MaxTree_NoTree

clean:
	rm -f Project1_2 Project1_2_ParentPID Project1_2_getpid Project1_2_pid Project1_2_MaxTree Project1_2_MaxTree_NoPrint Project1_2_MaxTree_NoTree
