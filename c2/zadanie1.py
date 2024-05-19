import Adafruit_BMP.BMP085 as BMP085  # Import biblioteki BMP

sensor = BMP085.BMP085()  # zmienna sensor i obiekt BMP085

# Temperatura w st. C
print("Temperatura = {0:0.2f} *C".format(sensor.read_temperature()))

# Cisnienie w Pa
print("Cisnienie = {0:0.2f} Pa".format(sensor.read_pressure()))
