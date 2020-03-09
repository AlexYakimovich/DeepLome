ifeq ($(OS), Windows_NT)
	PLATFORM=windows
	REMOVE_DIRECTORY=rd /s /q
	ADD_DIRECTORY=md
	CLIENT_EXECUTABLE_NAME=client.exe
        SERVER_EXECUTABLE_NAME=server.exe  
else
	PLATFORM=linux
	REMOVE_DIRECTORY=rm -rf
	ADD_DIRECTORY=mkdir
        CLIENT_EXECUTABLE_NAME=client                                     
        SERVER_EXECUTABLE_NAME=server
endif

all: add_build_dir build_client build_server
	

build_server:
	gcc DeepLomeServer/* DeepLomeCore/*.h DeepLomeCore/$(PLATFORM)/* -o  build_$(PLATFORM)/$(SERVER_EXECUTABLE_NAME) -lws2_32 -w

build_client:
	gcc DeepLomeClient/* DeepLomeCore/*.h DeepLomeCore/$(PLATFORM)/* -o  build_$(PLATFORM)/$(CLIENT_EXECUTABLE_NAME) -lws2_32 -w

add_build_dir:
	$(ADD_DIRECTORY) build_$(PLATFORM)
	
clean:
	$(REMOVE_DIRECTORY) build_$(PLATFORM)
