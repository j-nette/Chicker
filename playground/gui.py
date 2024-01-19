import tkinter as tk

def sendKick():
	#do something

	Text.insert('1.0',"Kick with " + str(slider.get()) + "!\n")

def sendChip():
	#do something
	Text.insert('1.0',"Chip with " + str(slider.get()) + "!\n")

def sendCharge():
	#do something
	Text.insert('1.0',"Charge with " + str(slider.get()) + "!\n")

# tkinter window setup

chicker_tester_window = tk.Tk()
chicker_tester_window.geometry("500x300")

Text = tk.Text(chicker_tester_window, width = 40, height = 4, wrap = "word")
Text.insert('1.0',"Hi c:")

Button = tk.Button

kickBtn = Button(chicker_tester_window, text = " Kick ", font = ("helvetica, 16"), command = sendKick)
chipBtn = Button(chicker_tester_window, text = " Chip ", font = ("helvetica, 16"), command = sendChip)
chargeBtn = Button(chicker_tester_window, text = "Charge", font= ("helvetica, 16"),command = sendCharge)

slider = tk.Scale(chicker_tester_window, from_=0, to=200, orient="horizontal")


kickBtn.place(relx=0.30, rely=0.35, anchor="center")
chipBtn.place(relx=0.5, rely=0.35, anchor="center")
chargeBtn.place(relx=0.70, rely=0.35, anchor="center")
slider.place(relx=0.5, rely=0.65, anchor = "center")
Text.place(relx=0.5, rely=0.14, anchor = "center")

chicker_tester_window.mainloop()