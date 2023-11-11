import tkinter as tk
import serial
import time

arduinoData = serial.Serial(port='COM6', baudrate=9600, timeout=.1) 

def write_read(x: str): 
	arduinoData.write(bytes(x, 'utf-8')) 
	time.sleep(0.05) 
	#data = arduinoData.readline() 
	#return data 

def sendKick():
	write_read("1," + str(slider.get()))

def sendChip():
	write_read("2," + str(slider.get()))

def sendCharge():
	write_read("3," + str(slider.get()))


# tkinter window setup
chicker_tester_window = tk.Tk()

Button = tk.Button

kickBtn = Button(chicker_tester_window, text = "Kick", command = sendKick)
chipBtn = Button(chicker_tester_window, text = "Chip", command = sendChip)
chargeBtn = Button(chicker_tester_window, text = "Charge", command = sendCharge)

slider = tk.Scale(chicker_tester_window, from_=0, to=200, orient="horizontal")

kickBtn.grid(row = 0, column = 1)
chipBtn.grid(row = 0, column = 2)
chargeBtn.grid(row = 0, column = 3)
slider.grid(row = 1)

chicker_tester_window.mainloop()
