# Importing Libraries 
import serial 
import time 
import tkinter as tk


arduinoData = serial.Serial(port='COM6', baudrate=115200, timeout=.1) 

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
chicker_tester_window.geometry("500x300")

Button = tk.Button

kickBtn = Button(chicker_tester_window, text = " Kick ", font = ("helvetica, 16"), command = sendKick)
chipBtn = Button(chicker_tester_window, text = " Chip ", font = ("helvetica, 16"), command = sendChip)
chargeBtn = Button(chicker_tester_window, text = "Charge", font= ("helvetica, 16"),command = sendCharge)

slider = tk.Scale(chicker_tester_window, from_=0, to=200, orient="horizontal")


kickBtn.place(relx=0.30, rely=0.35, anchor="center")
chipBtn.place(relx=0.5, rely=0.35, anchor="center")
chargeBtn.place(relx=0.70, rely=0.35, anchor="center")
slider.place(relx=0.5, rely=0.65, anchor = "center")

chicker_tester_window.mainloop()
