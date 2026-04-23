## Etapa 1: Planteamiento del problema

- **Problema encontrado:** No entendíamos al 100% la actividad. Nos confundimos y pensamos que teníamos que hacer un sistema asimétrico de cifrado y descifrado.
- **Desición tomada:** Leer bien, aclarar dudas.
- **Ajuste realizado:** Establecer plan/esquema general de implementación. En esta etapa tenemos esta idea: Generación de llaves -> Implementación de clase hash -> Implementación de clase signer -> Validaciones
- **Explicación:** Una vez que platicamos como equipo definimos este flujo que por ahora pensamos que es el correcto. Decidimos implementar nuestro propio hash, solo porque sí. Entonces la idea es entra el mensaje, se le aplica el hash, usamos las llaves generadas para hacer la firma y a esa firma le hacemos las validaciones.
- **Reflexión:**

# Etapa 2: Inicio del programa

- **Problema encontrado:** Tamaño de bits de los tipos de datos. Para tener 512 bits para las llaves y 1024 para el módulo necesitabamos librerías extra.
- **Decisión tomada:** Usar datos de juguete con menos bits, para fines académicos.
- **Ajuste realizado:** Uso de uint32_t para los primos p y q. uint64_t para n (el módulo). uint32_t para el hash.
- **Explicación:** El máximo número de bits que soporta nativamente C++ es 128, entonces necesitamos que en ningún momento alguna operación pase de 128 bits. Por eso el máximo es n con 64 bits, pues al reducir el módulo, el máximo podría ser n\*n. Ahora, la razón que decidimos usar menos bits, es porque al final de cuentas es un trabajo académico y no una implementación que vamos a lanzar. Para fines ilustrativos, usar menos bits nos pareció perfecto, pero estámos conscientes de que en un sistema real tendríamos que usar más.
- **Reflexión:**

# Etapa 3: Hash

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**

# Etapa 4: Generación de llaves

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**

# Etapa 5: Generación de firma

- **Problema encontrado:**
  1. La firma producida no es igual usando el mismo texto.

- **Desición tomada:**
  1. Ver si es problema del hash o de la clase signer generando 2 hashes seguidos y viendo si son iguales.

- **Ajuste realizado:**
  1. Al inicio de GenerateHash() reseteamos los hash_values a sus valores iniciales antes que nada.

- **Explicación:**
  1. Al imprimir el hash del mensaje, sale diferente usando el mismo mensaje indicando que hay un error en el hash. En su momento hicimos pruebas y sí habían salido iguales los hashes de 2 textos iguales, entonces sospechamos que fue por hacer 2 hashes seguidos con el mismo objeto de Chemash. Después de analizar, vimos que los hash_values no se resetean antes de cada hash.

- **Reflexión:**
  1. Teníamos la opción de crear un nuevo objeto Chemash en cada firma, pero decidimos no complicarnos y arreglar el bug del hash. Aprendimos que siempre es bueno revisar la integración, pues este es uno de esos bugs que se encuentran hasta que se integran los componentes.

# Etapa 6: Validaciones

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**
