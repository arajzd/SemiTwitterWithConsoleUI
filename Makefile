CC=g++
STD=-std=c++98 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) main

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/main.o: main.cpp
	$(CC) $(CF) -c main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/SocialNetwork.o: SocialNetwork.cpp SocialNetwork.h DataBase.h User.h Tweet.h Retweet.h Reply.h Comment.h Event.h
	$(CC) $(CF) -c SocialNetwork.cpp -o $(BUILD_DIR)/SocialNetwork.o
	
$(BUILD_DIR)/Reply.o: Reply.cpp Reply.h
	$(CC) $(CF) -c Reply.cpp -o $(BUILD_DIR)/Reply.o

$(BUILD_DIR)/Comment.o: Comment.cpp Comment.h
	$(CC) $(CF) -c Comment.cpp -o $(BUILD_DIR)/Comment.o
	
$(BUILD_DIR)/Event.o: Event.cpp Event.h
	$(CC) $(CF) -c Event.cpp -o $(BUILD_DIR)/Event.o

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

main: $(BUILD_DIR)/SocialNetwork.o $(BUILD_DIR)/DataBase.o $(BUILD_DIR)/User.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Tweet.o $(BUILD_DIR)/Retweet.o $(BUILD_DIR)/Tag.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Event.o $(BUILD_DIR)/main.o
	$(CC) -g $(CF) $(BUILD_DIR)/main.o  $(BUILD_DIR)/SocialNetwork.o $(BUILD_DIR)/DataBase.o  $(BUILD_DIR)/User.o $(BUILD_DIR)/Tweet.o $(BUILD_DIR)/Retweet.o $(BUILD_DIR)/Tag.o $(BUILD_DIR)/Interface.o $(BUILD_DIR)/Reply.o $(BUILD_DIR)/Comment.o $(BUILD_DIR)/Event.o -o main.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
