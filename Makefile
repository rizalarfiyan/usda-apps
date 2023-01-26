MAIN = usda-apps
COMPILER = g++
TEMP_DIR = ./temp/

all: clear build access run

clear:
	clear

build:
	mkdir -p $(TEMP_DIR)
	$(COMPILER) $(MAIN).cpp -o $(TEMP_DIR)$(MAIN) 

access:
	chmod +x $(TEMP_DIR)$(MAIN)

run:
	$(TEMP_DIR)$(MAIN)

clean:
	rm -rf $(TEMP_DIR)