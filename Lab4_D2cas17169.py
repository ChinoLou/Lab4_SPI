#Laboratorio 4
#Comunicaci�n SPI Y Serial
#Operacion del Programa: Mandar 2 potenci�metros (ADC)desde un PIC16F# SLAVE a un PIC16F# MASTER POR "SPI" LEER DICHOS ADC EN LA COMPU. Mandar un n�mero decimal a el puertoB del PIC16# MASTER
#Steven Josu� Castillo Lou / Carn�: 17169
#Electr�nica Digital 2 (secc. 10)

from Tkinter import*
import serial
import struct               #Librer�a para convertir los datos a Bytes 
import time
import sys


#---------------------- Configuraci�n Serial ----------------------------
puerto = 'COM3'
ser = serial.Serial(port = puerto, baudrate = 9600,
                    parity = serial.PARITY_NONE,
                    stopbits = serial.STOPBITS_ONE,
                    bytesize = serial. EIGHTBITS, timeout = 0)
#-----------------------------------------------------------------------
color_fondo = '#DCDCDC'
voltaje1 = 0
voltaje2 = 0
voltaje3 = 0

    
#---------------- Funcion del Boton enviar -----------------------------

def enviar():                         #Funcion para enviar los datos al PIC 
    numero_str=contadorNew.get()      #asignamos a la variable numero_str el valor del string ingresado en la ventana del "Entry"
    num_entero=int(numero_str)        #Convertimos dicho Str en un Entero "Int" 

    ser.write(struct.pack('>B',num_entero))          #STRUCT manda los datos ingresados en el "entry" en forma binaria al PIC desde el TTL
    print("Byte env�ado")                            #Esta funcion "struct.pack" solo permine ingresar numeros de 0-255 (1 Byte) por lo que no es necesario hacer progra defensiva!!!
    print (num_entero)                               #num_entero es el dato en Byte que se envia del TTL al PIC  



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
nombre1 = Label(ventana, text="Josu� Castillo \n 17169", background = color_fondo, font=('Times', 14)).place(x=90,y=140)

#-----------------Boton---------------------

envioTTL = Button(ventana, text = "Enviar", command = enviar ).place(x=250,y=75)  #! "comamand = enviar" relaciona el boton de la ventana del Entry con la funcion "envio"

#------------------variables-----------------
voltaje_1 = Label(ventana,text=str(voltaje1) ,fg="red",font=(18))
voltaje_1.place(x=180,y=20)

voltaje_2 = Label(ventana,text=str(voltaje2) ,fg="red",font=(18))
voltaje_2.place(x=180,y=45)

voltaje_1_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_1_1.place(x=225,y=20)

voltaje_2_1 = Label(ventana,text="V" ,fg="red",font=(18))
voltaje_2_1.place(x=225,y=45)

#--------------  Cuadro de Entrada ------------------#
contadorNew = Entry(ventana, justify= CENTER, width=3)  #! Le asignamos el dato que ingresamos en el "Entry" a la variable "contadorNew"
contadorNew.place(x=200,y=80)  #Posici�n del Entry

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
