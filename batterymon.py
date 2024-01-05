import tkinter as tk
import customtkinter as ctk

import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import csv
import os
import re

# Default colors
base = '#262940'
accent = '#4D5382'
hover = '#C6CAED'

class Application(ctk.CTk):
    def __init__(self):
        super().__init__(
            )

        self.title("Battery Monitor")
        self.geometry("960x540")
        self.resizable(False, False)

        self.fg_color = accent
        self.bg_color = base
        self.border_color = base
        self.hover_color = base
        self.text_color = hover
        
        data = []

        self.read_file(data)
        self.create_widgets(data)
        self.mainloop()

    def create_widgets(self, data):
        # Create a Matplotlib figure
        fig = Figure(figsize=(6, 4), dpi=100)
        ax = fig.add_subplot(111)

        # Extract the timestamp, battery percentage, and charging status from your data
        timestamps = [row[0] for row in data]
        battery_percentages = [int(row[1]) for row in data]
        charging_status = [row[2] for row in data]

        # Plot your data
        ax.plot(timestamps, battery_percentages, label='Battery Percentage')
        ax.set_xlabel('Timestamp')
        ax.set_ylabel('Battery Percentage')
        ax.set_title('Battery Data Visualization')
        ax.grid()

        # Create a canvas to display the plot in the Tkinter window
        canvas = FigureCanvasTkAgg(fig, master=self)
        canvas.get_tk_widget().pack()

    def read_file(self, data):
        with open('/usr/local/etc/data.txt', 'r') as f:
            reader = csv.reader(f)
            for row in reader:
                data.append(row)

def theme(theme):
    global base
    global accent
    global hover

    # obtain the user's home directory
    home = os.path.expanduser('~')

    # Read in the colors from the config file
    with open(home + '/.config/' + theme, 'r') as f:
        for line in f:
            if line.startswith('base'):
                base = re.search(r'#[0-9A-Fa-f]{6}', line).group(0)
            elif line.startswith('accent'):
                accent = re.search(r'#[0-9A-Fa-f]{6}', line).group(0)
            elif line.startswith('hover'):
                hover = re.search(r'#[0-9A-Fa-f]{6}', line).group(0)

theme('theme/active.theme')
Application()
