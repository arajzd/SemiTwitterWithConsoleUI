CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) server.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/server_main.o: server/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/main.cpp -o $(BUILD_DIR)/server_main.o

$(BUILD_DIR)/SocialNetwork.o: SocialNetwork.cpp SocialNetwork.h DataBase.h User.h Tweet.h Retweet.h
	$(CC) $(CF) -c SocialNetwork.cpp -o $(BUILD_DIR)/SocialNetwork.o
	
$(BUILD_DIR)/DataBase.o: DataBase.cpp DataBase.h
	$(CC) $(CF) -c DataBase.cpp -o $(BUILD_DIR)/DataBase.o
	
$(BUILD_DIR)/Interface.o: Interface.cpp Interface.h
	$(CC) $(CF) -c Interface.cpp -o $(BUILD_DIR)/Interface.o
    	
$(BUILD_DIR)/User.o: User.cpp User.h
	$(CC) $(CF) -c User.cpp -o $(BUILD_DIR)/User.o
	
$(BUILD_DIR)/Tweet.o: Tweet.cpp Tweet.h
	$(CC) $(CF) -c Tweet.cpp -o $(BUILD_DIR)/Tweet.o
	
$(BUILD_DIR)/Retweet.o: Retweet.cpp Retweet.h
	$(CC) $(CF) -c Retweet.cpp -o $(BUILD_DIR)/Retweet.o

$(BUILD_DIR)/Tag.o: Tag.cpp Tag.h
	$(CC) $(CF) -c Tag.cpp -o $(BUILD_DIR)/Tag.o

server.out: $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/SocialNetwork.o $(BUILD_DIR)/DataBase.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Tweet.o $(BUILD_DIR)/Retweet.o $(BUILD_DIR)/Tag.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/server_main.o
	$(CC) -g $(CF) $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/server_main.o  $(BUILD_DIR)/SocialNetwork.o $(BUILD_DIR)/DataBase.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/Tweet.o $(BUILD_DIR)/Retweet.o $(BUILD_DIR)/Tag.o $(BUILD_DIR)/Interface.o -o server.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
