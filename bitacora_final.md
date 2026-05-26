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
- **Desición tomada:** Investigar cómo hacerle para que el compilador busque los includes desde la raíz.
- **Ajuste realizado:** Agregar -I al comando de compilación.
- **Explicación:** El problema era que al compilar no se encontraban los headers porque los #include usaban paths relativos desde la raíz del proyecto, pero el compilador los buscaba desde el archivo donde está el header. Entonces al agregar el -I al comando, le estamos diciendo al compilador que busque los includes desde la raíz. Ya con eso funcionó.
- **Reflexión:** Esto es algo que ya sabíamos de los primeros semestres de programación, pero en el momento no nos fijamos que no habíamos incluido el -I en el comando y no se nos ocurrió al instante checar.

# Etapa 4: Subido a repositorio

- **Problema encontrado:** Al resolver conflictos durante el proceso de subido, el programa dejó de funcionar correctamente.
- **Desición tomada:** Se debuggeó el código con el fin de encontrar el motivo de la falla. Eventualmente, se llegó a utilizar inteligencia artificial para intentar encontrar el causante del error; no obstante, esto no ayudó. Finalmente, al revisar los cambios agregados por el merge generado al resolver conflictos, se encontró la modificación de dos líneas de código que rompían el programa.
- **Ajuste realizado:** El cambio problemático consistía en acortar el tipo de dato de p y q durante la generación de llaves a 32 bits en vez de 64. A pesar de que esto parecía tener sentido, al momento de realizar su multiplicación, la operación provocaba un overflow. El ajuste realizado consistió en mantener el tipo de dato, pero castear las variables a unas de 64 bits al momento de realizar operaciones con ellas, asegurando que el resultado no se saliera del rango permitido.
- **Explicación:** En vez de revertir el cambio del tipo de variable original, se utilizó este acercamiento para mantener claridad en el proceso de generación de llaves y evitar modificar la estructura base de las variables debido a las limitaciones del lenguaje de programación.
- **Reflexión:** Encontrar y resolver el error de esta manera nos ayudó a adquirir mayor conocimiento y experiencia, lo cual puede ser útil al momento de identificar errores en programas desarrollados en el futuro.

# Etapa 5: Implementación de casos de validación

- **Problema encontrado:** Algunos casos requerían modificaciones al flujo de comunicación entre los actores.
- **Desición tomada:** Pasarle a la función de recibir mensaje una llave privada modificada.
- **Ajuste realizado:** A la función readMessage() ahora le pasamos un parámetro opcional modifiedPrivateKey que si viene en 0 usa la llave real, y si viene con otro valor usa esa llave para el descifrado.
- **Explicación:** Para simular el caso 6 de descifrado con llave privada incorrecta tuvimos modificar el código como se explicó antes. Esto para permitir la simulación de que un tercero con una llave incorrecta intenta descifrar el mensaje sin crear un actor completamente nuevo.
- **Reflexión:** Nosotros tomamos el camino de agregar un parámetro a una función que ya teníamos, aunque también pudimos crear otro Receiver. Al final las 2 formas funcionaban.

# Etapa 6: Adaptación código para prueba de archivos JSON pregenerados

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**
