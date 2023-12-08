
El programa que usted dispone consta de un código compuesto por 3 archivos en el lenguaje C (.c), un header .h y un Makefile.

Este programa estudia los algoritmos de ordenamiento para distintos arreglos de "tweets" (mensajes de distintos usuarios de la red social Twitter), los cuales son recibidos a partir de un archivo "tweets.csv" ordenados en orden cronológico en base a 3 de dichos algoritmos, los cuales poseen distintos niveles de complejidad a la hora de realizar dicha labor.

Una vez realizada esta tarea, el programa posee la opción de introducir un segundo archivo de texto plano "keys.txt", el cual contiene distintos valores númericos que representarán las posiciones necesarias de los tweets ordenados para formar un mensaje secreto (generado en la creación de otro archivo de texto). Este dato de ser omitido, hará que el programa no busque crear ningún mensaje escondido dentro de los recopilados.

Con esto, el programa es bastante útil para comprender el tamaño de las diferencias que se pueden ir formando al ordenar datos con distintos algoritmos de ordenamiento, y como dicha diferencia se puede ir viendo cada vez mas notoria a la hora de trabajar con una cantidad de datos mucho mayor. Esto no sólo alude al tópico de los algoritmos de ordenamiento como tal, sino que también hace alusión sobre lo valioso que puede llegar a ser manejar una versión mucho mas óptima de un código, en la cual se puedan utilizar menos instrucciones, hacer menos uso de memoria reservada y demás apartados cruciales en el ámbito de una buena programación de código.

Como ciertas restricciones previas para los archivos de texto a introducir junto a la ejecución del programa, es importante recalcar que ninguna linea debe sobrepasar los 2000 caracteres (o de quererse igualmente, se puede modificar el valor de "linea_max" experesado al inicio del código "funciones.c"). A la vez, dichas lineas de texto deben seguir el siguiente formato específico para el correcto funcionamiento del programa:

tweets.csv:

"fecha;hora;usuario;mensaje" <=> "año-mes-día;hora:min:seg;usuario;mensaje"

ej: "2009-06-02;04:44:35;(nombre_usuario);(mensaje_tweet)"

keys.txt: (números en una sola línea separados por espacios)
ej: "1600120 1600106 1600095 2200234 1600077 52 1600205 1600167 1600174 1600127 24 2200249 1600072 1600197 2200259 1600104 1600087 1600203 1600152 2200241 1600137 5 2200250 1600204"

Fuera de esto, se generará un archivo "reportes.txt" el cual contendrá un análisis de la relación empírica existente entre los distintos tipos de algoritmos de ordenamiento utilizados.

Para poder compilar este programa en sistemas operativos Linux, nada más hará falta correr

    make ARGS="tweets.csv keys.txt"

en la terminal desde la carpeta que contenga todos los archivos extraidos del archivo comprimido .tar.gz (opción disponible dentro del paquete "build-essential" para las compilaciones y demases, paquete instalable desde la terminal con

    sudo apt-get install build-essential
    
).

De ser otro su sistema operativo, deberá consultar otras alternativas para poder compilar y obtener el ejecutable de los distintos códigos que constan el programa completo (.exe para Windows, por ejemplo).
Como aclaración, los archivos "tweets.csv" y "keys.txt" pueden reemplazarse por otros archivos de texto plano que respeten las normas y el formato aclarados en un inicio.


Agradeciendo por descargar y estar interesado en mi programa, me despido.

Pedro Cisternas Arce

estudiante de 3° año en Ingeniería Civil Telemática de la Universidad Técnica Federico Santa María

campus San Joaquín, Santiago de Chile.//
