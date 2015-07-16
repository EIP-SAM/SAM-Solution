##
## Makefile for SAM-Solution
##
## Made by Nicolas Chauvin
## Email <chauvin.nico@gmail.com>
##
## Started on  Wed Jul 15 01:56:59 2015 Nicolas Chauvin
## Last update Thu Jul 16 21:16:52 2015 Nicolas Chauvin
##
##
## NOTE :
## This makefile is temporary, it will be soon replaced by sam-deployer
##

RM		=	rm -rfv

SERVER		=	server
ADMIN_CLIENT	=	admin_client
USER_CLIENT	=	user_client

BUILD_DIR_SUFFIX	=	build

SERVER_BUILD_DIR	=	$(SERVER)_$(BUILD_DIR_SUFFIX)
ADMIN_CLIENT_BUILD_DIR	=	$(ADMIN_CLIENT)_$(BUILD_DIR_SUFFIX)
USER_CLIENT_BUILD_DIR	=	$(USER_CLIENT)_$(BUILD_DIR_SUFFIX)

SERVER_TMP_BUILD_FILES		=	$(shell ls $(SERVER_BUILD_DIR)/build/ | grep -v $(SERVER)\$)
ADMIN_CLIENT_TMP_BUILD_FILES	=	$(shell ls $(ADMIN_CLIENT_BUILD_DIR)/build/ | grep -v $(ADMIN_CLIENT)\$)
USER_CLIENT_TMP_BUILD_FILES	=	$(shell ls $(USER_CLIENT_BUILD_DIR)/build/ | grep -v $(USER_CLIENT)\$)


all: $(SERVER) $(ADMIN_CLIENT) $(USER_CLIENT)

$(SERVER):
	cd $(SERVER_BUILD_DIR)/build/ && cmake .. && make && cd - && ln -sf $(SERVER_BUILD_DIR)/build/$(SERVER) .

$(ADMIN_CLIENT):
	cd $(ADMIN_CLIENT_BUILD_DIR)/build/ && cmake .. && make && cd - && ln -sf $(ADMIN_CLIENT_BUILD_DIR)/build/$(ADMIN_CLIENT) .

$(USER_CLIENT):
	cd $(USER_CLIENT_BUILD_DIR)/build/ && cmake .. && make && cd - && ln -sf $(USER_CLIENT_BUILD_DIR)/build/$(USER_CLIENT) .

clean:
	cd $(SERVER_BUILD_DIR)/build/ && $(RM) $(SERVER_TMP_BUILD_FILES)
	cd $(ADMIN_CLIENT_BUILD_DIR)/build/ && $(RM) $(ADMIN_CLIENT_TMP_BUILD_FILES)
	cd $(USER_CLIENT_BUILD_DIR)/build/ && $(RM) $(USER_CLIENT_TMP_BUILD_FILES)

fclean: clean
	$(RM) $(SERVER) $(ADMIN_CLIENT) $(USER_CLIENT)
	$(RM) $(SERVER_BUILD_DIR)/build/$(SERVER) $(ADMIN_CLIENT_BUILD_DIR)/build/$(ADMIN_CLIENT) $(USER_CLIENT_BUILD_DIR)/build/$(USER_CLIENT)

re: fclean all

.PHONY: all clean fclean re
