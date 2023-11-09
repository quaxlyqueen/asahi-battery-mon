import tkinter as tk
from tkinter import ttk
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import csv

# Create a window
root = tk.Tk()
root.title("Battery Data Visualization")

# Create a Matplotlib figure
fig = Figure(figsize=(6, 4), dpi=100)
ax = fig.add_subplot(111)

# Read your data from a CSV file
data = []
with open('/usr/local/etc/data.txt', 'r') as csvfile:
    reader = csv.reader(csvfile)
    for row in reader:
        data.append(row)

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
canvas = FigureCanvasTkAgg(fig, master=root)
canvas.get_tk_widget().pack()

# Start the Tkinter event loop
root.mainloop()
