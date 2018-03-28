# Conectar Arduino Uno a un broker MQTT usando un modulo ESP8266 

## Pre-requisitos de software:
- Docker > 17.12.0
- Arduino IDE 

## Pre-requisitos de hardware:
- Arduino Uno
- Módulo ESP8266
- DPCOT
- Cables
- Protoboard

## Levantar Broker MQTT y cliente

1. Descargar la imagen de broker en el servidor, en este caso se usará mosquitto:

    `docker pull eclipse-mosquitto`

2. Una vez descargada la imagen, levantar un contenedor con la imagen de mosquitto en el puerto 1883

    `docker run -it -p 1883:1883 -p 9001:9001 eclipse-mosquitto`

3. Instalar un cliente de MQTT que va a estar suscrito a canal donde se publicará los mensajes usando Arduino. 

    `brew install mosquitto`
    
4. Suscribirse al canal donde el Arduino publicará los mensajes

     `mosquitto_sub -d -h localhost -p 1883 -t "users/arduino/send/canal`

5. Para comprobar que el correcto funcionamiento del broker 
     
     `mosquitto_pub -d -h localhost -p 1883 -t "users/arduino/send/canal" -m "Hola mundo"`
     
## Probar modulo ESP8266


## Publicar un mensaje

## Suscribirse a un canal

