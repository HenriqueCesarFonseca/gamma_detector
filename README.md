### DETECCÇÃO DE RADIAÇÃO GAMA PARA FINS DIDÁTICOS UTILIZANDO WEBCAM


![logo](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/radiacao_2.png)


[Sobre]() | [Visão Geral do Projeto]() | [Montando o Detector]() | [Download e Instalação]() | [Utilizando o software DetectaRad]() | [Fonte de Radiação]()



### **Sobre o projeto**
O objetivo geral deste projeto é enriquecer o ensino de Física Moderna em sala de aula através da confecção de um experimento de baixo custo e viável de ser realizado em sala de aula para turmas do ensino médio.

O experimento consiste em captar radiação ionizante do tipo gama atravez de uma webcam de baixo custo e analisar as imagens em tempo real através de um software (DetectaRad) desenvolvido para este fim.

Este projeto faz parte da dissertação de mestrado do **Programa Nacional de Mestrado Profissional em Ensino de Física (MNPEF)** desenvolvida no polo da UNESP de Presidente Prudente - SP, orientado pela Profª. Dra. Ana Maria Osório Araya.
 

 ### **Visão Geral do Projeto**

Uma fonte de radiação gama e uma webcam são colocadas dentro de um recipiente fechado para impedir a entrada de luz. O cabo USB da webcam é conectado a um PC onde o software **DetectaRad** irá exibir em tempo real todos os pontos de radiação detectados bem como uma janela com todos os pontos já detectados e a quantidade total de pontos detectados.

![esquema](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/VIS%C3%83O%20GERAL.bmp)

Ao finalizar o programa, todos os frames em que foram detectados algum ponto de radiação são armazenados em um diretório bem como um arquivo com as coordenadas de todos os pontos de radiação detectados. A cada experimento um novo diretório é criado e numerado sequencialmente.
O software DetectaRad foi desenvolvido para ser executado apenas no sistema operacional Windows.

[Clique aqui para ver uma demonstração no YouTube](https://youtu.be/BfPhDDmZTyQ)

![GIF](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/gif_2.gif)

![Montagem final](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%20FINAL%20RESIZED%20640%20X%20480.bmp)

Os pontos na janela **IMAGEM EM TEMPO REAL** aparecem e desaparecem rapidamente. Alguns pontos com intensidade mais fraca não podem ser visto pelo observador. A imagem abaixo (640 x 480) mostra um ponto bem visível detectado nas coordenadas (345;351). Como a imagem gerada segue o padrão da biblioteca OpenCV , a origem (0,0) situa-se no canto esquerdo superior.

![Ponto bem visível](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/UM%20PONTO%20DETECTADO%20BEM%20VIS%C3%8DVEL%201.bmp)


Observe que o arquivo ***cooredenadas_todos_os_pontos_detectador.txt*** - gerado automaticamente ao final do programa - lista este ponto na segunda linha:

```
614:68	        Nivel de cinza:  32

345:351		Nivel de cinza:  51

530:408		Nivel de cinza:  31
```

A primeira linha corresponde ao primeiro frame capturado , a segunda linha ao segundo frame e assim por diante.

Desta forma podemos conferir utilizando o programa PAINT do Windows que realmente na coordenada (345;351) encontramos um ponto de detecção conforme mostrado na Figura abaixo.

![Ponto visto do PAINT](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/PONTO%20VISTO%20PELO%20PAINT.png)


O parâmetro ***Nível de cinza*** corresponde à conversão do padrão RGB com diferentes intensidade para Red,Green e Blue convertidas para o padrão GRAY com um único nível de intensidade (o que facilita o software executar a busca por um ponto detectado).





 ### **Montando o Detector**




 ### **Download e Instalação**


### **Utilizando o software DetectaRad**


1

2

3

4

5



 
 




















[Download](https://github.com/HenriqueCesarFonseca/curso_github#instru%C3%A7%C3%B5es-de-uso)  |  

[Recomendações](https://github.com/HenriqueCesarFonseca/curso_github#recomenda%C3%A7%C3%B5es)






** Pendências**

- [x] Sem bugs.
- [ ] Instalador ok.
- [ ] Ícone

Recurso              |        Disponibilidade
-------------------- |  ---------------------
resolução máxima     |      1280x920
![logo](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/radiacao_2.png)   | ![logo](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/radiacao_2.png) 









* Sobre o projeto.
* Montando o detector.
* Download do softwere DetectaRad.
* Como instalar DetectaRad.
* Instruções de uso do DetectaRad.

1. Sobre o projeto.
2. Montando o detector.
3. Utilizando o software

       i. aaa
       ii. bbb

4. Uso
> Este é  um block code destaca uma área
>
> Segunda ligna
>
> Terceira linha

**Comandos para localizar o diretório**

```C++
int a=10;
b++;
return 0;

dir
list
```

dir

mkdir teste

'''

1

2

3

4

5

6

7

8

9

10

11

12

13


14


15














### INSTRUÇÕES DE USO
Baixe os dois arquivos:

DetectaRad.msi

setup.exe



2

3

4

5

6

7

8

9

10

11

12

13


14


15


















### Recomendações
f

d

f

f


2

3

4

5

6

7

8

9

10

11

12

13


2

3

4

5

6

7

8

9

10

11

12

13


