# GuardianGear
## Objetivo del proyecto
- Desarrollo de un casco inteligente para mejorar la seguridad y la experiencia del usuario al realizar actividades al aire libre.

## Integrantes
- 1220100361 - Carlos Daniel Soto Ledezma.     
- 1220100006 - Jairo Barron Loza.                  
- 1219100566 - Ricardo Alexis Rioyos Ramirez.       

## Beneficiario
- [POR DEFINIRSE]

## Hardware
| Num. | Componente | Descripción | Imagen | Costo | Cantidad |
|----|-------|----|---|--|---|
|1|KY-003 HALL MAGNETIC|El KY-003 es un sensor de efecto Hall que detecta campos magnéticos, proporcionando una salida digital en presencia de un imán. Se utiliza en aplicaciones como contadores de revoluciones y sistemas de alarma. |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/98db8d6c-c3f6-4c69-8588-dd85456ac397)|$40.00| 1 |
|2|KY-018 PHOTORESISTOR|El KY-018 es un módulo basado en fotoresistencia que varía su resistencia según la cantidad de luz que recibe. Se utiliza para detectar niveles de luminosidad en proyectos electrónicos.|![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/ec6c4087-0c07-4a06-add7-29037dbf2c06)|$40.00| 1 |
|3| KY-015 TEMP AND HUMIDITY | El KY-015 es un módulo sensor que mide temperatura y humedad, ofreciendo salidas digitales para ambos parámetros. Se utiliza en proyectos que requieren monitoreo del ambiente. | ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/bb4aaa0d-285a-4e9f-b159-e0f3475f0ba0)|$60.00|1|
|4| KY-006 PASSIVE BUZZER |El KY-006 es un módulo de zumbador pasivo que produce sonidos al recibir una señal oscilante. Se utiliza en proyectos para generar tonos y alertas sonoras.|![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/f5cd179e-8367-41df-9771-f3fae5ff93cb)| $35.00|1|
|5| KY-031 TAP MODULE | El KY-031 es un módulo sensor de golpeteo o "tap" que detecta vibraciones o impactos físicos. Se emplea en proyectos que requieren detección de movimientos o golpes. |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/766643f1-b390-461f-90c7-b67f89a8ee57)| $35.00 | 1 |
|6| NEO-6M GPS | El NEO-6M es un módulo GPS de alta performance que proporciona datos de coordenadas geográficas, altitud y tiempo. Se utiliza en proyectos de rastreo, navegación y sincronización de tiempo basados en ubicación. |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/44bf770c-b479-4ca4-9a1b-64350d442f32)|$206.00|1|
|7| ESP32 |El ESP32 es un microcontrolador de doble núcleo con conectividad WiFi y Bluetooth integrada, ampliamente utilizado en proyectos de IoT (Internet de las Cosas). Ofrece una combinación de bajo consumo de energía y alto rendimiento para aplicaciones embebidas y domóticas.|![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/023a705f-88a8-4f46-b7ba-2a97cbbf2151)|$180.00|1|
|8| Cable Dupont Breadboard Jumper Wires | Son los cables que serviran para hacer las conexiones entre todos los dispositivos del casco inteligente |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/93737169/fd0f6fab-c76d-4399-a47d-14cff5cc8c25)|$79.00|1|
|9| Matriz de LEDs | Es una matriz de 64 LEDs RGB (8x8) en la que cada LED puede ser controlado individualmente en cuanto a color e intensidad. Utiliza el chip WS2812, lo que significa que se puede controlar con un solo pin de datos desde microcontroladores como Arduino. Es popular en proyectos que requieren visualizaciones coloridas o efectos luminosos personalizados. |![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/85852f9c-9326-43bc-8b1b-7546332d695a)|$85.50|1|

## Tabla de Software utilizado
| Id | Software | Version | Tipo |
|----|----------|---------|------|
| 1 | Python | 3.9 | Software Libre |
| 2 | Visual Studio Code | 1.72.2 | Software Libre |
| 3 | IDE de Arduino | 1.6.0 | Software Libre |
| 4 | Open Computer Vision | 4.70 | Biblioteca de Visión Artificial. |
| 6 | NumPy | 1.19.2 | Biblioteca para Python. |

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
|  HU001 | Como beneficiario, deseo que la persona encargada de mí pueda conocer mi ubicación en tiempo real. |Debe| 5 | El beneficiario inicia su viaje y el encargado puede ver en el sitio web dónde se encuentra en tiempo real.| Carlos Daniel | 
|  HU002 | Como beneficiario, necesito que mi encargado pueda recibir un mensaje con mi ubicación en caso de que tenga un accidente. |  Debe |  6  | Si el casco recibe un fuerte golpe, el encargado recibe un mensaje en Telegram con los datos de la ubicación actual o la última registrada en la base de datos. |  Carlos Daniel  |
|  HU003  | Como beneficiario, necesito que los conductores que están detrás de mí al momento de que nuestro entorno no cuenta con suficiente luz, se encienda una luz llamativa para promover precaución. |   Debe    | 1  | El sensor KY-018 al detectar poca luz, debe encender la matriz de LEDs | Jairo Barrón  |
|  HU004  |Como beneficiario, quiero que mi encargado se entere cuando me abrocho el casco, demostrando así mi responsabilidad.| Debe | 1 | El sensor KY-003 debe colocarse en el broche del casco, y un imán debe situarse estratégicamente en una parte del casco, de modo que cuando el beneficiario se lo abroche, se pueda activar el sensor. |  Ricardo Alexis  |
| HU005 | Como beneficiario, quisiera conocer la temperatura y humedad de mi entorno para estar al tanto de los máximos y mínimos de estos y así tomar mis precauciones. | Debe | 3 | Se debe registrar en la base de datos el máximo y mínimo de temperatura y humedad por recorrido, para que posteriormente se puedan consultar en el sitio web. | Ricardo Alexis |
| HU006 | Como beneficiario, deseo que una alarma me alerte cuando mi encargado ha intentado contactarme por algún asunto y no ha podido hacerlo. | Debe | 4 | En el sitio web habrá un botón que, al presionarlo, activará una alarma integrada en el casco. | Jairo Barron |
| HU007 | Como beneficiario, necesito que mi ubicación, al ser almacenada en la base de datos, esté encriptada para protegerme de posibles peligros.| Debe | 1 | Al consultar en la base de datos los registros de la ubicación del casco, estos deben estar encriptados. | Carlos Daniel |
| HU008 | Como beneficiario, necesito que el sitio web donde se muestra información de mi ubicación y entorno esté protegido por un módulo de login, asegurando así que solo las personas autorizadas puedan ingresar. | Debe | 1 | Al acceder al sitio web, este debe solicitar credenciales para permitir el acceso. | Carlos Daniel |

## Prototipo en dibujo
![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/4e987846-8272-4976-a0ed-eee1e175dd6f)

## Prototipo en Fitzing
![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/3ee351e7-4963-47b1-8631-f0ddf93159ed)


## Placa PCB
![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/df405c02-3de7-447b-93f9-96d790d16ab5)


## Prototipo en 3D
- ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/7796be0d-2c14-44fd-8657-03a0c4d34e0a)
- ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/cc179d24-71a5-4609-a978-d3dd9e97a599)
- ![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/84ee540f-e531-4049-badb-ccb19fcad49f)

## Carta
![image](https://github.com/Carlos-Soto-L/GuardianGear/assets/67080087/145bdc55-b6d9-4781-9863-27ec6c66aa24)




