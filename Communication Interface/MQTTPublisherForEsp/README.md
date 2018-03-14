# Conectar Arduino Uno a un broker MQTT usando un modulo ESP8266 

## Pre-requisitos de software:
- Docker > 17.12.0
- Arduino IDE 

## Pre-requisitos de hardware:
- Arduino Uno
- Módulo ESP8266
- DPCOT
- Cables
- Proto

## Levantar Broker MQTT y cliente

1. Descargar la imagen de mosquitto

    `docker pull eclipse-mosquitto`

2. Levantar un contenedor con la imagen de mosquitto

    `docker run -it -p 1883:1883 -p 9001:9001 eclipse-mosquitto`

3. Instalar un cliente de mqtt 

    `brew install mosquitto`
    
4. Suscribirse al canal donde el arduino publicará el mensaje

     `mosquitto_sub -d -h localhost -p 1883 -t "users/arduino/send/temperature"`
     
## Probar modulo ESP8266


## Publicar un mensaje

## Suscribirse a un canal

