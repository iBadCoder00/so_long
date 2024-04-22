#!/bin/bash

# COLORS
GREEN="\e[0;32m"
RED="\e[0;31m"
BLACK="\e[0;30m"
YELLOW="\e[1;33m"
BLUE="\e[0;34m"
PURPLE="\e[1;95m"
BG_PURPLE="\e[45m"
END="\e[0m"

MFILE=Makefile
SRC_DIR=src
PROJ_NAME="$1"

if [ $# -eq 0 ]
then
	echo "Usage: ./build.sh <project_name>. Use -h flag for help."
	exit 1
fi

if [ "$1" == "-h" ]
then
	echo -e 'About:\n  \tThe build scipt creates two folders "include" and "src" where all .h and .c files are moved respectively.
	After all items have been moved, a generic Makefile is created that will compile all .c files and asign to NAME
	the name given as first parameter.
	If a libft folder is found, the script will create default paths and compilations rules to include the library.
	\n\tScript created by Axel Dávila: davilapantanoaxel@gmail.com'
	exit 0
	
fi



# CREATE PROJECT FOLDERS
if [[ ! -d include ]] || [[ ! -d src ]]
then
	mkdir include 2>/dev/null
	mkdir src 2>/dev/null
fi

c_files=$(ls ./*.c  2>/dev/null| wc -l)
if [ $c_files != 0 ]
then
	echo -e "${YELLOW}All .c files have been moved to src/$END"
	mv *.c src 
fi

h_files=$(ls ./*.h  2>/dev/null| wc -l)
if [ $h_files != 0 ]
then
	echo -e "${YELLOW}All .h files have been moved to include/$END"
	mv *.h include 
fi

if [ -f Makefile ]
then
	rm $MFILE
fi

# COLORS TABLE

echo "GREEN		= \033[0;32m" >> $MFILE
echo "RED		= \033[0;31m" >> $MFILE
echo "BLACK		= \033[0;30m" >> $MFILE
echo "YELLOW		= \033[1;33m" >> $MFILE
echo "BLUE		= \033[0;34m" >> $MFILE
echo "PURPLE		= \033[1;95m" >> $MFILE
echo "BG_PURPLE		= \033[45m" >> $MFILE
echo "END		= \033[0m" >> $MFILE
echo -e "\n\n" >> $MFILE


# CREATE COMPILATION / BUILD FLAGS
echo "CC		=	gcc" >> $MFILE
echo "CFLAGS		=	-Wall -Wextra -Werror" >> $MFILE
echo "RM 		= 	rm -rf" >> $MFILE

libft_path=$(find -name libft -type d)
if [ -n "$libft_path" ]
then
	echo "LIBS	=	-L $libft_path -l:libft.a" >> $MFILE
	echo "LIBFT	=	libft/libft.a" >> $MFILE
fi
printf "\n\n" >> $MFILE

echo "NAME		=	$PROJ_NAME" >> $MFILE

# GET ALL THE C FILES
SRC=$(ls $SRC_DIR/*.c 2>/dev/null | sort -V)
echo -e "SRC		=	\\" >> $MFILE
for file_name in $SRC; do
	echo -e "\t\t\t$(basename "$file_name")\\" >> $MFILE
done
echo >> $MFILE

# CREATE RULES
echo 'OBJ		= 	$(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))' >> $MFILE
printf "\n\n" >> $MFILE
echo 'SRC_DIR		= 	src' >> $MFILE
echo 'INC_DIR		= 	include' >> $MFILE
echo 'OBJ_DIR		= 	obj' >> $MFILE
printf "\n\n" >> $MFILE
echo -e 'all: $(NAME)\n' >> $MFILE

# NAME RULE
echo -ne '$(NAME):' >> $MFILE
if [ -n "$libft_path" ]
then
	echo ' $(LIBFT) $(OBJ)' >> $MFILE
	echo -e '\t@$(CC) $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)' >> $MFILE
	echo -e '\t@printf "                                   \\r"' >> $MFILE
	echo -e '\t@printf "$(GREEN)> BUILDING '${1^^}'               [✓]$(END)\\n"\n' >> $MFILE
	echo '$(LIBFT):' >> $MFILE
	echo -e "\t@make -s -C $libft_path\n" >> $MFILE
else
		echo ' $(OBJ)' >> $MFILE
		echo -e '\t@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)' >> $MFILE
		echo -e '\t@printf "                                   \\r"' >> $MFILE
		echo -e '\t@printf "$(GREEN)> BUILDING '${1^^}'               [✓]$(END)\\n"\n' >> $MFILE
fi

# OBJ CREATION RULE & OBJ DIR
echo -e '$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)' >> $MFILE
echo -ne "\t" >> $MFILE
echo '@printf "$(YELLOW)> BUILDING $<               \r$(END)"' >> $MFILE
echo -e '\t@$(CC) $(CFLAGS) -I $(INC_DIR) -c -o $@ $<\n' >> $MFILE

echo '$(OBJ_DIR):' >> $MFILE
echo -e '\t@mkdir obj\n' >> $MFILE

# CLEANERS
echo "clean:" >> $MFILE
if [ -n "$libft_path" ]
then
	echo -e "\t@make clean -s -C $libft_path" >> $MFILE
fi
echo -e '\t@$(RM) $(OBJ_DIR)\n' >>$MFILE

echo "fclean: clean" >> $MFILE
if [ -n "$libft_path" ]
then
	echo -e "\t@make fclean -s -C $libft_path" >> $MFILE
fi
echo -e '\t@$(RM) $(NAME)\n' >>$MFILE

echo -e "re: fclean all\n" >> $MFILE

#.PHONY
echo -ne ".PHONY: all clean fclean re" >> $MFILE
