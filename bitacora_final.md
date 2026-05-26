## Etapa 1: Planteamiento del problema

- **Problema encontrado:** Subestimamos la complejidad de la actividad.
- **Desición tomada:** Leer bien y platicarlo con otros equipos, al igual que utilizar inteligencia artificial para generar un plan de trabajo estructurado para darnos una idea de los desafíos a los que nos íbamos a enfrentar en un proyecto que inicialmente parecía algo trivial.
- **Ajuste realizado:** Cambiar nuestro acercamiento confiado que teníamos al principio.
- **Explicación:** A pesar de que la actividad parecía relativamente simple para un proyecto final al comienzo, al consultar opiniones externas al equipo, nos dimos cuenta de que el proyecto contaba con un grado de dificultad no negable. Por esto, decidimos dividirnos el trabajo de manera ordenada y seguir trabajando con buenas prácticas, como lo es el uso de GitHub para control de versiones y la creación de archivos de librerías de clases para mantener la lógica modular.
- **Reflexión:** Esto fue de gran utilidad ya que, si hubiéramos utilizado un acercamiento parecido a la programación procedimental, hubiéramos contado con un archivo main bastante complejo y no hubiéramos podido representar los casos de uso de manera ordenada.

# Etapa 2: Creación de la clase actor

- **Problema encontrado:** No sabíamos cómo trabajar con archivos de tipo JSON de manera simple.
- **Desición tomada:** Investigar formas de implementar de manera sencilla la integración de archivos de tipo JSON a nuestro proyecto, incluyendo la creación, manipulación y lectura de estos archivos.
- **Ajuste realizado:** Se optó por utilizar una librería pública de Niels Lohmann, tomada de GitHub.
- **Explicación:** C++ no cuenta con soporte nativo para archivos JSON; por eso, decidimos usar una librería bastante utilizada, publicada en GitHub por Niels Lohmann. Esta librería se añadió a nuestra carpeta junto con nuestras librerías propias y se incluyó en los archivos necesarios para poder utilizar la lógica que trae consigo.
- **Reflexión:** Esta fue una decisión sabia, ya que la otra opción constaba de modificar archivos manualmente con librerías como fstream y nos habría hecho trabajar en resolver problemas que están fuera del alcance de esta actividad. Como el manejo corecto de las llaves y la identación de las lineas de texto.

# Etapa 3: Integración dentro del main, compilado y pruebas

- **Problema encontrado:** Durante el compilado inicial, batallamos al enlazar los archivos con las librerías necesarias.
- **Desición tomada:** 
- **Ajuste realizado:** 
- **Explicación:** 
- **Reflexión:** 

# Etapa 4: Subido a repositorio

- **Problema encontrado:** Al resolver conflictos durante el proceso de subido, el programa dejó de funcionar correctamente.
- **Desición tomada:** Se debuggeó el código con el fin de encontrar el motivo de la falla. Eventualmente, se llegó a utilizar inteligencia artificial para intentar encontrar el causante del error; no obstante, esto no ayudó. Finalmente, al revisar los cambios agregados por el merge generado al resolver conflictos, se encontró la modificación de dos líneas de código que rompían el programa.
- **Ajuste realizado:** El cambio problemático consistía en acortar el tipo de dato de p y q durante la generación de llaves a 32 bits en vez de 64. A pesar de que esto parecía tener sentido, al momento de realizar su multiplicación, la operación provocaba un overflow. El ajuste realizado consistió en mantener el tipo de dato, pero castear las variables a unas de 64 bits al momento de realizar operaciones con ellas, asegurando que el resultado no se saliera del rango permitido.
- **Explicación:** En vez de revertir el cambio del tipo de variable original, se utilizó este acercamiento para mantener claridad en el proceso de generación de llaves y evitar modificar la estructura base de las variables debido a las limitaciones del lenguaje de programación.
- **Reflexión:** Encontrar y resolver el error de esta manera nos ayudó a adquirir mayor conocimiento y experiencia, lo cual puede ser útil al momento de identificar errores en programas desarrollados en el futuro.

# Etapa 5: Implementación de casos de validación

- **Problema encontrado:** Algunos casos requerían modificaciones al flujo de comunicación entre los actores.
- **Desición tomada:** 
- **Ajuste realizado:** 
- **Explicación:** 
- **Reflexión:** 

# Etapa 6: Adaptación código para prueba de archivos JSON pregenerados

- **Problema encontrado:** 
- **Desición tomada:** 
- **Ajuste realizado:** 
- **Explicación:** 
- **Reflexión:** 