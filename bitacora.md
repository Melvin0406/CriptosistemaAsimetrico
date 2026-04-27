## Etapa 1: Planteamiento del problema

- **Problema encontrado:** No entendíamos al 100% la actividad. Nos confundimos y pensamos que teníamos que hacer un sistema asimétrico de cifrado y descifrado.
- **Desición tomada:** Leer bien, aclarar dudas.
- **Ajuste realizado:** Establecer plan/esquema general de implementación. En esta etapa tenemos esta idea: Generación de llaves -> Implementación de clase hash -> Implementación de clase signer -> Validaciones
- **Explicación:** Una vez que platicamos como equipo definimos este flujo que por ahora pensamos que es el correcto. Decidimos implementar nuestro propio hash, solo porque sí. Entonces la idea es entra el mensaje, se le aplica el hash, usamos las llaves generadas para hacer la firma y a esa firma le hacemos las validaciones.

# Etapa 2: Inicio del programa

- **Problema encontrado:** Tamaño de bits de los tipos de datos. Para tener 512 bits para las llaves y 1024 para el módulo necesitabamos librerías extra.
- **Decisión tomada:** Usar datos de juguete con menos bits, para fines académicos.
- **Ajuste realizado:** Uso de uint32_t para los primos p y q. uint64_t para n (el módulo). uint32_t para el hash.
- **Explicación:** El máximo número de bits que soporta nativamente C++ es 128, entonces necesitamos que en ningún momento alguna operación pase de 128 bits. Por eso el máximo es n con 64 bits, pues al reducir el módulo, el máximo podría ser n\*n. Ahora, la razón que decidimos usar menos bits, es porque al final de cuentas es un trabajo académico y no una implementación que vamos a lanzar.
- **Reflexión:** Aquí comprendimos las limitaciones de C++ nativo y consideramos usar una librería extra. Al ser una implementación académica, iremos con menos bits, pero estámos conscientes de que en un sistema real tendríamos que usar más.

# Etapa 3: Hash

- **Problema encontrado:** La función SHA-256 debía ser modificada internamente para poder acomodarse a nuestra versión simplificada del sistema de firma electrónica.
- **Desición tomada:** Se modifica la salida original de 256 bits para mostrar la salida correcta de 64 bits.
- **Ajuste realizado:** Se toman las últimas 2 partes de 32 bits cada uno y se concatenan para formar la nueva salida.
- **Explicación:** Se decidió tomar esta solución ya que modificar internamente la generación del valor hash podría comprometer la seguridad y entropía de este mismo. La razón que hace a SHA-256 muy efectivo es precisamente la gran cantidad de modificaciones que se le hacen a sus datos por rondas; al reducir la complejidad del cálculo principal se comprometería la eficiencia de la función.
- **Reflexión:** Esto nos enseñó a tomar decisiones que pongan como prioridad la robustez y la seguridad del sistema, haber tomado el otro acercamiento habría comprometido seriamente un sistema de la vida real.

# Etapa 4: Generación de llaves

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**

# Etapa 5: Generación de firma

- **Problema encontrado:**
  1. La firma producida no es igual usando el mismo texto.
  2. Se nos olvidó aplicar mod N al hash para que todo sea menor que N.
  3. d puede ser más de 32 bits, pero lo declaramos como uint32_t en la función.

- **Desición tomada:**
  1. Ver si es problema del hash o de la clase signer generando 2 hashes seguidos y viendo si son iguales.
  2. Simplemente aplicar mod N antes de empezar a elevar el hash en la firma.
  3. Cambiar d a que tenga 64 bits.

- **Ajuste realizado:**
  1. Al inicio de GenerateHash() reseteamos los hash_values a sus valores iniciales antes que nada.
  2. Agregar a la función de sign hash = hash % n; justo después de obtener el hash.
  3. Cambiar d a uint64_t.

- **Explicación:**
  1. Al imprimir el hash del mensaje, sale diferente usando el mismo mensaje indicando que hay un error en el hash. En su momento hicimos pruebas y sí habían salido iguales los hashes de 2 textos iguales, entonces sospechamos que fue por hacer 2 hashes seguidos con el mismo objeto de Chemash. Después de analizar, vimos que los hash_values no se resetean antes de cada hash.
  2. Aplicamos el proceso de encriptación y desencriptación RSA con llaves de juguete para asegurarnos que las matemáticas estuvieran correctas. Se supone que al hacerlo, el hash del mensaje elevado a la e (la llave pública) y luego a la d (llave privada) mod n, debía ser igual al hash del mensaje inicial (porque e y d son inversos multiplicativos). Ahí nos dimos cuenta que el hash era mucho más grande que n, entonces obviamente no eran iguales. Y pues de ahí recordamos que el hash también se tiene que reducir mod n.
  3. Estabamos hablando del tamaño de las llaves, y al checar la presentación, nos dimos cuenta que d estaba en el rando de phi de n, que son los 2 primos de n menos 1 multiplicados, entonces 32 bits es muy poquito.

- **Reflexión:**
  1. Teníamos la opción de crear un nuevo objeto Chemash en cada firma, pero decidimos no complicarnos y arreglar el bug del hash. Aprendimos que siempre es bueno revisar la integración, pues este es uno de esos bugs que se encuentran hasta que se integran los componentes.
  2. Este fue un error de descuido simplemente. Al pensar que el hash y n son de 64 bits y que 64 bits era lo máximo que íbamos a tener, no pensamos en que el hash generado podía ser mayor al n calculado. Al probar con n's pequeñas, el bug quedó expuesto bastante rápido.
  3. Siempre es bueno contrastar la lógica del programa con la de un ejemplo, para encontrar este tipo de incongruencias.

# Etapa 6: Validaciones

- **Problema encontrado:**

1. Al verificar el flujo normal y ver si se podía encriptar con la llave privada y desencriptar con la pública, nos dimos cuenta que la firma y la verificación no coincidían aunque el mensaje y las llaves si eran correctas.

- **Desición tomada:**

1. Agregamos prints de debug para comparar el hash que usa el Signer y el hash que usa el Verifier, con la idea de encontrar en qué punto ocurre el problema.

- **Ajuste realizado:**

1. Cambiar los parámetros de la función ModInverse de int64_t a uint64_t, usando \_\_int128 internamente para los valores intermedios del algoritmo extendido de Euclides.

- **Explicación:**

1. La firma no era válida y no era porque el hash fuera diferente. Imprimimos los demás valores y no se miraban mal. Después de preguntarle a una IA, entendimos el error. uint64_t e int64_t son diferentes en que int64_t guarda un bit para el signo, entonces su valor máximo positivo es de 2^63. Declaramos phi como uint64_t porque los primos de n son de hasta 32 bits, por lo que n y phi pueden superar los 2^63. El problema era que en la función ModInverse los parámetros los pusimos como int64_t, entonces cuando pasabamos phi como parámetro, que tenía más de 63 bits, se interpretaba como negativo y pues hacía que las matemáticas fallaran. Al fallar el cálculo de d, la firma no podía verificarse. En los valores del algoritmo de Euclides no les pusimos uint64_t, porque ahí sí pueden ser negativos, entonces usamos \_\_int128.

- **Reflexión:**

1. Este overflow ha sido el bug más difícil de detectar hasta el momento, porque el programa no lanza ningún error, simplemente produce un resultado incorrecto. Aprendimos que al trabajar con operaciones matemáticas que requieren precisión en bits en el tema de overflow, hay que ser cuidadosos con los tipos en cada operación y con posibles overflows entre medio.
