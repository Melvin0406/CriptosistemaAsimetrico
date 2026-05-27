## Etapa 1: Planteamiento del problema

- **Problema encontrado:** Subestimamos la complejidad de la actividad.
- **Desición tomada:** Leer bien y platicarlo con otros equipos, al igual que utilizar inteligencia artificial para generar un plan de trabajo estructurado para darnos una idea de los desafíos a los que nos íbamos a enfrentar en un proyecto que inicialmente parecía algo trivial.
- **Ajuste realizado:** Cambiar nuestro acercamiento confiado que teníamos al principio.
- **Explicación:** A pesar de que la actividad parecía relativamente simple para un proyecto final al comienzo, al consultar opiniones externas al equipo, nos dimos cuenta de que el proyecto contaba con un grado de dificultad no negable. Por esto, decidimos dividirnos el trabajo de manera ordenada y seguir trabajando con buenas prácticas, como lo es el uso de GitHub para control de versiones y la creación de archivos de librerías de clases para mantener la lógica modular.
- **Reflexión:** Esto fue de gran utilidad ya que, si hubiéramos utilizado un acercamiento parecido a la programación procedimental, hubiéramos contado con un archivo main bastante complejo y no hubiéramos podido representar los casos de uso de manera ordenada.

## Etapa 2: Creación de la clase actor

- **Problema encontrado:** No sabíamos cómo trabajar con archivos de tipo JSON de manera simple.
- **Desición tomada:** Investigar formas de implementar de manera sencilla la integración de archivos de tipo JSON a nuestro proyecto, incluyendo la creación, manipulación y lectura de estos archivos.
- **Ajuste realizado:** Se optó por utilizar una librería pública de Niels Lohmann, tomada de GitHub.
- **Explicación:** C++ no cuenta con soporte nativo para archivos JSON; por eso, decidimos usar una librería bastante utilizada, publicada en GitHub por Niels Lohmann. Esta librería se añadió a nuestra carpeta junto con nuestras librerías propias y se incluyó en los archivos necesarios para poder utilizar la lógica que trae consigo.
- **Reflexión:** Esta fue una decisión sabia, ya que la otra opción constaba de modificar archivos manualmente con librerías como fstream y nos habría hecho trabajar en resolver problemas que están fuera del alcance de esta actividad. Como el manejo corecto de las llaves y la identación de las lineas de texto.

## Etapa 3: Integración dentro del main, compilado y pruebas

- **Problema encontrado:** Durante el compilado inicial, batallamos al enlazar los archivos con las librerías necesarias.
- **Desición tomada:** Investigar cómo hacerle para que el compilador busque los includes desde la raíz.
- **Ajuste realizado:** Agregar -I al comando de compilación.
- **Explicación:** El problema era que al compilar no se encontraban los headers porque los #include usaban paths relativos desde la raíz del proyecto, pero el compilador los buscaba desde el archivo donde está el header. Entonces al agregar el -I al comando, le estamos diciendo al compilador que busque los includes desde la raíz. Ya con eso funcionó.
- **Reflexión:** Esto es algo que ya sabíamos de los primeros semestres de programación, pero en el momento no nos fijamos que no habíamos incluido el -I en el comando y no se nos ocurrió al instante checar.

## Etapa 4: Subido a repositorio

- **Problema encontrado:** Al resolver conflictos durante el proceso de subido, el programa dejó de funcionar correctamente.
- **Desición tomada:** Se debuggeó el código con el fin de encontrar el motivo de la falla. Eventualmente, se llegó a utilizar inteligencia artificial para intentar encontrar el causante del error; no obstante, esto no ayudó. Finalmente, al revisar los cambios agregados por el merge generado al resolver conflictos, se encontró la modificación de dos líneas de código que rompían el programa.
- **Ajuste realizado:** El cambio problemático consistía en acortar el tipo de dato de p y q durante la generación de llaves a 32 bits en vez de 64. A pesar de que esto parecía tener sentido, al momento de realizar su multiplicación, la operación provocaba un overflow. El ajuste realizado consistió en mantener el tipo de dato, pero castear las variables a unas de 64 bits al momento de realizar operaciones con ellas, asegurando que el resultado no se saliera del rango permitido.
- **Explicación:** En vez de revertir el cambio del tipo de variable original, se utilizó este acercamiento para mantener claridad en el proceso de generación de llaves y evitar modificar la estructura base de las variables debido a las limitaciones del lenguaje de programación.
- **Reflexión:** Encontrar y resolver el error de esta manera nos ayudó a adquirir mayor conocimiento y experiencia, lo cual puede ser útil al momento de identificar errores en programas desarrollados en el futuro.

## Etapa 5: Implementación de casos de validación

- **Problema encontrado:** Algunos casos requerían modificaciones al flujo de comunicación entre los actores.
- **Desición tomada:** Pasarle a la función de recibir mensaje una llave privada modificada.
- **Ajuste realizado:** A la función readMessage() ahora le pasamos un parámetro opcional modifiedPrivateKey que si viene en 0 usa la llave real, y si viene con otro valor usa esa llave para el descifrado.
- **Explicación:** Para simular el caso 6 de descifrado con llave privada incorrecta tuvimos modificar el código como se explicó antes. Esto para permitir la simulación de que un tercero con una llave incorrecta intenta descifrar el mensaje sin crear un actor completamente nuevo.
- **Reflexión:** Nosotros tomamos el camino de agregar un parámetro a una función que ya teníamos, aunque también pudimos crear otro Receiver. Al final las 2 formas funcionaban.

## Etapa 6: Tamaño de mensajes y padding

- **Problema encontrado:** Los mensajes de más de 8 caracteres se cortaban. Al arreglar eso, ahora se podía inferir la longitud del mensaje (la mitad del texto cifrado).
- **Desición tomada:** Cambiar un poco la forma de encriptar: en vez de encriptar los números, encriptamos el mensaje en hexadecimal. Después, agregamos padding en bloques de 16.
- **Ajuste realizado:** Para la encriptación hicimos un XOR byte por byte del mensaje con la llave de sesión y lo guardamos el mensaje cifrado en hexadecimal. Esto hacía que el mensaje cifrado fuera el doble de longitud del original (2 caracteres en hexa son un char). Para solucionar esto agregamos un padding para rellenar bloques de 16 caracteres, de forma que el mensaje a encriptar siempre era múltiplo de 16.
- **Explicación:** Originalmente el mensaje se truncaba porque solo hacíamos XOR de uint_8 (8 bytes), entonces máximo se descifraban 8 bytes o caracteres. Al hacer el ajuste, introducimos un ciclo donde el XOR por byte con la llave de sesión se iba ciclando. Aplicamos ese ciclo tanto en el cifrado como en el descifrado, y de esa forma permitiamos que el mensaje fuera de la longitud que queramos, pues simplemente se convería en un string de un número en hexadecimal. El problema es que esto hacía que el mensaje cifrado fuera el doble de longitud del original (2 caracteres en hexa son un char). Y fue ahí donde pusimos el padding para rellenar antes del cifrado, de forma que el mensaje siempre tenía un número de bytes múltiplo de 16. En el descifrado simplemente quitamos ese padding siguiendo PKCS7.
- **Reflexión:** Aquí el arreglar o mejorar cierta parte de la implementación nos introdujo otro problema. Por eso hay que ser cuidadosos y revisar bien que todo esté bien antes de tomar algo por hecho.

## Etapa 7: Adaptación código para prueba de archivos JSON pregenerados

- **Problema encontrado:** No entendíamos qué era lo que los requisitos solicitaban exactamente.
- **Desición tomada:** Se envió un correo a la profesora para entender qué era lo que necesitaba que realizáramos.
- **Ajuste realizado:** Una vez recibimos una respuesta, nos comentó que se requería mostrar evidencias de los archivos JSON tanto en la bitácora como en la documentación. De igual manera, durante la explicación en video se mostraría el uso de dichos archivos, y estos se subirían junto con el código en la entrega.
- **Explicación:** Se decidió comunicar directamente a la docente, ya que era la única persona que podía aclarar esta duda con total certeza, en vez de arriesgarnos a obtener una interpretación incorrecta por parte de otro equipo o de un agente de inteligencia artificial y perder puntos en el proceso.
- **Reflexión:** A pesar de ser una solución bastante sencilla y directa, muchos equipos optan por utilizar otros métodos en lugar de comunicarse con el profesor, ya sea por falta de tiempo o para evitar tiempos de respuesta largos. Como equipo, consideramos que esta era la mejor opción y resultó útil, ya que obtuvimos la claridad necesaria para terminar la asignación.
