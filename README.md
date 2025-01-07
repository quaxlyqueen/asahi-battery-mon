<h1 align="center">Battery Monitor</h1>

### INTRODUCTION

This project is written on and for Apple Silicon MacBooks running Asahi Linux. 

The purpose is two-fold: give the user more data about their battery performance, and give the user options to optimize their battery. 
Eventually the daemon and it's corresponding commands will allow for the user to get estimates of their time remaining, implement 
power-saving modes, optimization suggestions, and other features that are built-in to MacOS.

**Note**: An interesting trend does emerge from initial testing, the battery usage and charging appears to be a stepped linear function.

### FEATURES

### TODO
- [ ] Gather all relavent information for the daemon: display backlight, keyboard backlight, 
      running applications, etc.
- [X] Implement the GUI graph with GTK.
    - [ ] Estimated time remaining section.
    - [ ] Power-saving recommendations
- [ ] Calculate estimated time remaining based upon historical data.
- [x] Battery-mon daemon on startup.

### INSTALLATION
    git clone https://github.com/quaxlqueen/battery-mon
    cd battery-mon
    sudo ./install

### Troubleshooting
    You may need to do the following:
    sudo chmod a+rw /tmp/battery.txt
    sudo pacman -S acpi
