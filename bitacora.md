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
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**

# Etapa 6: Validaciones

- **Problema encontrado:**
- **Desición tomada:**
- **Ajuste realizado:**
- **Explicación:**
- **Reflexión:**
