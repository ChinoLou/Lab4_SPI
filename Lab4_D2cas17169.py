#Laboratorio 4
#Comunicación SPI Y Serial
#Operacion del Programa: Mandar 2 potenciómetros (ADC)desde un PIC16F# SLAVE a un PIC16F# MASTER POR "SPI" LEER DICHOS ADC EN LA COMPU. Mandar un número decimal a el puertoB del PIC16# MASTER
#Steven Josué Castillo Lou / Carné: 17169
#Electrónica Digital 2 (secc. 10)

from Tkinter import*
import serial
import time
import sys


#---------------------- Configuración Serial ----------------------------
puerto = 'COM3'
ser = serial.Serial(port = puerto, baudrate = 9600,
                    parity = serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial. EIGHTBITS, timeout = 0)
#-----------------------------------------------------------------
color_fondo = '#DCDCDC'
voltaje1 = 0
voltaje2 = 0
voltaje3 = 0

    
#------------------------------------------------------------

def enviar (): #Función para enviar datos
    try: #Prueba que sea un número entero
        entero = int(contador.get())
        error.set(" ")
        
        if entero > 255 or entero < 0: #Verifica que este dentro del rango si no, muestra un error
            error.set("INGRESE UN VALOR ENTRE 0 Y 255")

       # else: #Si todo se cumple, envia el dato
        #    data.write(struct.pack('>B',entero))
        
    except: #Si no es entero, muestra un error
        print ("ingrese un numero")
        error.set("INGRESE UN VALOR NUMÉRICO ENTERO")   



#------------------ventana-------------------
ventana = Tk()
ventana.title("Laboratorio No. 4 SPI")
ventana.geometry("300x200")
ventana.resizable(width=FALSE, height=FALSE)
ventana.config(bg=color_fondo)


#------------------labels-------------------
rut1 = Label(ventana, text="POT No.1:", background = color_fondo, font=('Comics', 16)).place(x=60,y=20)
rut2 = Label(ventana, text="POT No.2:", background = color_fondo, font=('Comics', 16)).place(x=60,y=45)
rut3 = Label(ventana, text="TTL   :", background = color_fondo, font=('Comics', 16)).place(x=60,y=70)
nombre1 = Label(ventana, text="Josué Castillo \n 17169", background = color_fondo, font=('Times', 14)).place(x=90,y=140)

#-----------------Boton---------------------

send = Button(ventana, text = "Enviar", command = enviar ).place(x=250,y=75)

 #Boton enlazado con la funcion enviar


#------------------variables-----------------
voltaje_1 = Label(ventana,text=str(voltaje1) ,fg="red",font=(18))
voltaje_1.place(x=180,y=20)

voltaje_2 = Label(ventana,text=str(voltaje2) ,fg="red",font=(18))
voltaje_2.place(x=180,y=45)

voltaje_1_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_1_1.place(x=225,y=20)

voltaje_2_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_2_1.place(x=225,y=45)

###############################################################33
contador = Entry(ventana, justify= CENTER, width=3)
contador.place(x=200,y=80)

error = StringVar()
error.set(" ")


while True:
    dato = ser.read()
    try:
        if dato == '':
            pass
        else:
            dato1 = ser.read()
            dato2 = ser.read()

            valor1 = ord(dato1)
            valor2 = ord(dato2)

            print(str(valor1) + ',' + str(valor2))
            ser.flushInput()
            time.sleep(.05)
            
    except:
        print('.')
    voltaje1 = (5.00*valor1)/254.00
    voltaje2 = (5.00*valor2)/254.00
    voltaje_1.config(text = str(voltaje1)[0:4])
    voltaje_2.config(text = str(voltaje2)[0:4])
    #voltaje_3.config(text = str(voltaje3))
    ventana.update_idletasks()
    ventana.update() 
    time.sleep(.2)

ventana.mainloop()
