NAME    = pipex                                                                                                                                               
CC      = cc                                                                                                                                                  
CFLAGS  = -Wall -Wextra -Werror                                                                                                                               
                                                                                                                                                              
# Couleurs                                                                                                                                                    
GREEN   = \033[0;32m                                                                                                                                          
BLUE    = \033[0;34m                                                                                                                                          
YELLOW  = \033[0;33m                                                                                                                                          
RED     = \033[0;31m                                                                                                                                          
NC      = \033[0m                                                                                                                                             
                                                                                                                                                              
SRCS    = main.c utils.c                                                                                                                                      
OBJS    = $(SRCS:.c=.o)                                                                                                                                       
                                                                                                                                                              
# ══════════════════════════════════════════════                                                                                                              
                                                                                                                                                              
all: $(NAME)                                                                                                                                                  
                                                                                                                                                              
$(NAME): $(OBJS)                                                                                                                                              
	@printf "$(BLUE)\n"                                                                                                                                     
	@printf "  ╔═══════════════════════════╗\n"                                                                                                             
	@printf "  ║        P I P E X          ║\n"                                                                                                             
	@printf "  ║        by rpinheir        ║\n"                                                                                                             
	@printf "  ╚═══════════════════════════╝\n"                                                                                                             
	@printf "$(NC)\n"                                                                                                                                       
	@printf "  $(YELLOW)⚡ Linking...$(NC)\n"                                                                                                               
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)                                                                                                                     
	@printf "  $(GREEN)✅ $(NAME) ready!$(NC)\n\n"                                                                                                          
                                                                                                                                                              
%.o: %.c                                                                                                                                                      
	@printf "  $(BLUE)🔨 Compiling $<...$(NC)\n"                                                                                                            
	@$(CC) $(CFLAGS) -c $< -o $@                                                                                                                            
                                                                                                                                                              
clean:                                                                                                                                                        
	@printf "  $(RED)🗑️  Cleaning objects...$(NC)\n"                                                                                                        
	@rm -f $(OBJS)                                                                                                                                          
                                                                                                                                                              
fclean: clean                                                                                                                                                 
	@printf "  $(RED)💀 Removing $(NAME)...$(NC)\n"                                                                                                         
	@rm -f $(NAME)                                                                                                                                          
                                                                                                                                                              
re: fclean all                                                                                                                                                
                                                                                                                                                              
.PHONY: all clean fclean re  
