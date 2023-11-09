<h1 align="center">Battery Monitor</h1>

This project is written on and for Apple Silicon MacBooks running Asahi Linux. 

The purpose is two-fold: give the user more data about their battery performance, and give the user options to optimize their battery. 
From the first purpose, eventually the daemon and it's corresponding commands will allow for the user to get estimates of their time 
remaining, implement power-saving modes, optimization suggestions, and other features that are built-in to MacOS.

**Note**: An interesting trend does emerge from initial testing, the battery usage and charging appears to be a stepped linear function.

### TODO
    [ ] Gather all relavent information for the daemon: display backlight, keyboard backlight, running applications, etc.
    [ ] Implement the GUI graph with GTK.
        [ ] Estimated time remaining section.
        [ ] Power-saving recommendations
    [ ] Battery-mon daemon on startup.
    [ ] Calculate estimated time remaining based upon historical data.

### INSTALLATION
    git clone https://github.com/quaxlqueen/battery-mon
    cd ./battery-mon
    ./make
