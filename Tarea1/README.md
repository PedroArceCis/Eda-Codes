
El programa que usted dispone consta de un código compuesto por 3 archivos en el lenguaje C (.c), un header .h, un Makefile y un .txt de ejemplo por si desea probarlo con este al momento de ejecutar el programa.

============================================================

Este programa simula venta de entradas para un concierto, a través de la lectura de un archivo de texto .txt (estadio) el cual consta en su primera linea de la cantidad de sectores del recinto en dónde se realizará dicho espectáculo, seguido del precio base para las distintas entradas a ofrecer, en el formato que se dicta en el archivo de ejemplo, todo separado con espacios.
A partir de la segunda linea, el formato será el siguiente:
"número_de_sector   cantidad_de_entradas   factor_multiplicador_para_precio_base"

============================================================

A partir de dicha información, el código generará un lista de clientes los cuales irán accediendo a comprar las entradas a partir de un presupuesto monetario aleatorio.
Por pantalla, se irán mostrando actualizaciones dentro de un aproximado de cada 5000 entradas vendidads hasta que estas se terminen agotando.
Dentro de estas actualizaciones, se podrá visualizar cuantas entradas disponibles quedan en total, las localidades en las cuales ya no quedan boletos disponibles, y en una suerte de azar puede o no salir una publicidad de la venta de entradas del concierto como de la bebida auspiciadora oficial de dicho evento.

============================================================

Para poder compilar este programa en sistemas operativos Linux, nada más hará falta correr

        make ARGS="estadio1.txt"

en la terminal desde la carpeta que contenga todos los archivos extraidos del archivo comprimido .tar.gz (opción disponible dentro del paquete "build-essential" para las compilaciones y demases, paquete instalable desde la terminal con <sudo apt-get install build-essential>).
De ser otro su sistema operativo, deberá consultar otras alternativas para poder compilar y obtener el ejecutable de los distintos códigos que constan el programa completo (.exe para Windows, por ejemplo).
Como aclaración, el comando se utiliza sin los simbolos "<>" y el archivo "estadio1.txt" puede reemplazarse por otro archivo de estadio mientras se respeten las normas y el formato aclarados en un inicio.

============================================================

Agradeciendo por descargar y estar interesado en mi programa, me despido.

Pedro Cisternas Arce

estudiante de 3° año en Ingeniería Civil Telemática de la Universidad Técnica Federico Santa María

campus San Joaquín, Santiago de Chile.//
