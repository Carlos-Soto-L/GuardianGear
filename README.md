# GuardianGear
## Objetivo del proyecto
- Desarrollo de un casco inteligente para mejorar la seguridad y la experiencia del usuario al realizar actividades al aire libre.

## Integrantes
- 1220100361 - Carlos Daniel Soto Ledezma. 
- 1219100777 - Carlos Eduardo Rangel Lozano.       
- 1220100006 - Jairo Barron Loza.                  
- 1219100566 - Ricardo Alexis Rioyos Ramirez.
- 1220100074 - Ana Isabel Jasso Velazquez.         

## Beneficiario
- Ricardo Alexis: Al contar con este casco inteligente tendré mucha más confianza de viajar en carretera y de recorrer largos caminos por la noche, en conclusión, me sentiré más seguro. Ya que cada semana salgo de viaje.

## Hardware
| Num. | Componente | Descripción | Imagen | Costo | Cantidad |
|----|-------|----|---|--|---|
|1|SIM800L|El módulo SIM800L es un dispositivo de comunicación compacto y altamente integrado diseñado para permitir la comunicación de datos y voz en redes de telecomunicaciones móviles. | ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/5772f001-a07f-4db7-b917-088df8981e13)|$150.00| 1 |
|2|NodeMCU| El módulo NodeMCU se utiliza ampliamente en proyectos de Internet de las cosas (IoT) debido a su conectividad Wi-Fi integrada y su capacidad para interactuar con otros dispositivos a través de internet| ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/69bcc73b-a2dc-4b7c-b699-55e9e6be8d8a) |$200.00| 1 |
|3| Microfono | Modulo que nos permite enviar audio para hacer posible la realización de llamadas. | ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/4e970429-06e0-476c-a05b-22f15a433fe5)|$60.00|1|
|4| Altavoz | Dispositivo que nos permite la salida de audio, con el objetivo de realizar llamadas.| ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/5cb044ab-694e-45f1-9519-ed259cd53ff4)| $15.00|1|
|5| Hc-sr04 | Es un sensor de distancias por ultrasonidos capaz de detectar objetos y calcular la distancia| ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/ccb820ab-b155-4f88-affd-97be68277525) | $63.00 | 1 |
|6| Servomotor |Es un dispositivo actuador que permite ejercer el movimiento para que el sensor ultrasonico pueda detectar los objetos en un radar giratorio |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/93737169/78859094-af56-4bd9-a4e2-25bb32e856d9)|$56.00|1|
|7| Placa Arduino UNO | Es un dispositivo microcontrolador que permite hacer la conexión entre los dispositivos permitiendo el envío de señales a los actuadores y sensores |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/93737169/681e9f29-bc5e-4c41-b7fe-7dc8af2748b7)|$|1|
|8| Saltar cables | Son los cables que serviran para hacer las conexiones entre todos los dispositivos del casco inteligente |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/93737169/fd0f6fab-c76d-4399-a47d-14cff5cc8c25)|$79.00|1|
|9| LEDRGB | Este componente tiene como objetivo mandar las alertas por medio de cambios de color en el led dentro del casco inteligente en la detección de objetos|![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/93737169/2b0a0d29-cf68-4476-a386-98c117cb6b3f)|$65.50|1|

## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
| 1 | Python | 3.9 | Software Libre |
| 2 | Visual Studio Code | 1.72.2 | Software Libre |
| 3 | IDE de Arduino | 1.6.0 | Software Libre |

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|  HU001 | Yo Ricardo Alexis quiero que el dispositivo envie un mensaje de texto (SMS) a un familiar o medico de confianza. |Debe| 5 |  El casco recibe un fuerte golpe (Simulando un accidente) y su familiar o medico recibe el SMS de ayuda. | Carlos Daniel | 
|  HU002 | Yo Ricardo Alexis quiero que el dispositivo me permita recibir llamadas.  |  Podria   |  6  |  Un contacto de Ricardo Alexis le realiza una llamada y esta se efectúa correctamente. |  Carlos Daniel  |
|  HU003  |  Yo Ricardo Alexis quiero detectar obstáculos que estén cerca de mi, para así poder evitar accidentes, ya que resultara útil en entornos donde no haiga mucha visibilidad     |   Debe    | 1  | El sensor al detectar un obstáculo muy cerca a mi, este enviará una advertencia o activara una alarma | Jairo Barrón  |
|  HU004  | Yo Ricardo Alexis quiero rastrear la ubicación del casco, por lo tanto, la ubicación siempre será en tiempo real | Podría | 1 | En el monitor remoto debe aparecerá la ubucacion del casco, siempre y cuadno este cuente con acceso a internet. |  Jairo Barrón  |
| HU005 | Yo Ricardo Alexis quiero que el casco inteligente sea capaz de conectar a mi telefono movil para reproducir musica | Podría | 6 | El casco mantiene activado el bluetooth para conectar al telefono y reproducir la musica por medio del altavoz integrado | Ana Jasso |
| HU006 | Yo Ricardo Alexis quiero que el casco inteligente detecte objetos a distancia por medio de un radar que me permita tener esa visibilidad extra | Estaría bien | 4 | El casco inteligente mantiene el sensor ultrasonico integrado en funcionamiento mientras detecta los objetos a largas distancias evitando accidentes por choques inesperados en cruces| Ana Jasso |
| HU007 | Yo Ricardo Alexis al encontrarme en la posibilidad de tener un accidente en moto el sensor Sw-420 debe de activarse al tener un impacto para dar paso a los demás sensores y a sus funciones| Debe | 1 | El sensor al detectar una vibración por algún golpe manda un pulso alto “1” a su salida y al no detectar vibración la salida se mantiene en estado bajo “0”. | Ricardo Alexis |
| HU008 | Yo Ricardo Alexis al encontrarme en un viaje largo tendre integrado en mi casco un sensor Dht11 para que mida la temperatura y humedad de esta manera poder evitar un golpe de calor. | Podría | 1 | El sensor detectará la temperatura y humedad y lo reflejará en la pantalla de este modo el usuario podrá verlo. | Ricardo Alexis  |

## Prototipo en dibujo
![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/4e987846-8272-4976-a0ed-eee1e175dd6f)

## Placa PCB

## Prototipo en 3D

