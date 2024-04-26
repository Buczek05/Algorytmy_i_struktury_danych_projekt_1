# Projekt 1

[Link to Better view](https://kacperbukowski.notion.site/Projekt-1-5b018d37d24040b1a18754a6aa632714?pvs=4)

Zadanie polega na obliczeniu pola pod funkcją, jest na to methoda analityczna, niestety niektóre całki wymagają sporej ilości liczenia więc spróbujemy użyć do tego komputera.
Jak dobrze wiemy koputery swojego mózgu nie mają (nie licząc AI) i nie potrafią same tworzyć rozwiązań, a gdybyśmy próbowali zaimplementować każdą metodę liczenia całek i funkcje która będzie odpowiednio łączyć metody to napewno nie zmieścimy się w tysiącu jak nie w 10 tyś linijek kodu, a po co to komu? Trzeba by napisać mnóstwo testów i mnóstwo logiki, a zamiast tego może pomyśleć nad rozwiązaniem które poda zbliżony wynik do oczekiwanego. Przykładowymi rozwiązaniami są metoda na prostokąty, trapezy i monte carlo. Zerknij na te diagramy i oceń która z nich będzie najlepsza

# Diagram sposobu na prostokąty

![rectangle.drawio.svg](rectangle.drawio.svg)

# Diagram sposobu na trapezy (bardzo podobny do poprzedniego)

![trapezoid.drawio.svg](trapezoid.drawio.svg)

# Diagram sposobu monte carlo

po lewej stronie jest funkcja znajdująca najwyższy punkt w wykresie (lub najniższy i bierze jego wartość bezwzględną) a po prawej już samo losowanie i liczenie punktów

![monte_carlo.drawio.svg](monte_carlo.drawio.svg)

Niestety muszę wybić cię z błędu, ta najtrudniejsza i najciekawsza, która polega na wylosowaniu miejsca kropki i sprawdzeniu czy ta kropka znajduje się pod wykresem czy nad, nie jest tą najlepszą. Za to zdobywa trofeum za najbardziej obciążającą 🏆 gdyż aby uzyskać jakikolwiek sensowny wynik potrzebujemy wykonać miliony operacji, gdzie poprzednie metody dają podobny wynik już przy kilku tysiącach.

Poniżej zobaczysz rozwiązania analityczne (tak chciało mi się liczyć całki) oraz rozwiązania komputerowe każdej z metod nałożone na wykres tworzony w matplotlib

![Rectangle.drawio.svg](doc_img/Rectangle.drawio.svg)

![Rectangle.drawio.svg](doc_img/Rectangle.drawio%201.svg)

$$
f(x) = x^2
$$

$$
\int_{-100}^{100} x^2 \, dx = \frac{x^3}{3} \bigg|_{-100}^{100} = \frac{100^3}{3} - \frac{(-100)^3}{3} = \frac{2000000}{3} \approx 666666.6666

$$

Dla 10 kwadratów

Wynik: 680000 ~ 102%

![1_10_rectangle.jpg](doc_img/1_10_rectangle.jpg)

Dla 1 tyś kwadratów (najlepsza dokładność)

Wynik: 666667.5625 ~ 100.0001345%

Dla 50 kwadratów

Wynik: 667200 ~ 100.08%

![1_50_rectangle.jpg](doc_img/1_50_rectangle.jpg)

Dla 5 tyś kwadratów

Wynik float: 666689.1875 ~ 100.003378%

Powyższy wynik jest przy zastosowaniu typu float, po zmianie na double zyskałem dodatkową dokładność

Wynik double: 666666.72 ~ 100.000008%

Dla 100 kwadratów

Wynik: 666800 ~ 100.02%

![1_100_rectangle.jpg](doc_img/1_100_rectangle.jpg)

Dla 10 tyś kwadratów

Wynik float: 66648.875 ~ 99.9973%

Wynik double: 666666.68 ~ 100.000002%

Dla 10 trapezów, pokrycie wygląda dużo lepiej niż 10 kwadratów, jednakże z powodu symetryczności funkcji, kwadraty w jednym miejscu wystawały a w drugim ich brakowało, co spowodowało identyczny wynik

Wynik: 680000 ~ 102%

![1_10_trapezoid.jpg](doc_img/1_10_trapezoid.jpg)

Dla 50 trapezów wynik również jest identyczny z 50 kwadratami

![1_50_trapezoid.jpg](doc_img/1_50_trapezoid.jpg)

Dla 100 trapezów wynik również jest identyczny co oznacza, że dla tej funkcji nie ma różnicy czy użyjemy sposobu na prostokąty czy na trapezy

![1_100_trapezoid.jpg](doc_img/1_100_trapezoid.jpg)

Następną możliwością jest metoda Monte Carlo. Polega ona na rozmieszczeniu losowo punktów i policzeniu pola całego prostokąta, następnie zliczenie punktów pod wykresem i przemnożenie ich stosunku do pola. Niestety taka metoda wymaga dużej ilości punktów nie zależnie od funkcji. Ogromną wagą tego sposobu jest fakt, że z każdym uruchomieniem programu dostajemy inny wynik

$$
area_f = area_{rectangle} * \frac{points\_under\_line}{all\_points}
$$

Dla 10 punktów wynik to 1000000 ~ 150%

![1_10_monte-carlo.jpg](doc_img/1_10_monte-carlo.jpg)

Dla 1 tyś punktów wykres jest już bardziej optymistyczny. (szare kropki ponad funkcją, zielone pod). Wynik: 644000 ~ 96.6%. Niestety mimo bardziej złożonego sposobu, dla tej funkcji wynik jest gorszy niż dla 10 kwadratów

![1_1000_monte-carlo.jpg](doc_img/1_1000_monte-carlo.jpg)

Dla 10 tyś punktów wykres jest już ciekawie pokolorowany a wynik jest nieco dokładniejszy: 669200 ~ 100.38%. Niestety przegrywa on z 50 kwadratami i to jest mak

![1_10000_monte-carlo.jpg](doc_img/1_10000_monte-carlo.jpg)

Dla 100 tyś punktów wynik to 670520 ~ 100.578% co oznacza, że jest gorszy niż dla 10k punktów, a winowajcą jest losowość a wykres wygląda w ten sposób

![1_100000_monte-carlo.jpg](doc_img/1_100000_monte-carlo.jpg)

Specjalnie aby zaprezentować co potrafi ta metoda przy większej ilości punktów, zmieniłem typ int na long w programie aby pomieścić liczbę 10 000 000 000 i takie udało się osiągnąć dokładności

| 1 mln | 665234 | 99.785% |
| --- | --- | --- |
| 10 mln | 666860 | 100.029% |
| 100 mln | 666578 | 99.9867% |
| 1 mld | 666666 | 99.9999% |
| 10 mld | 666656 | 99.9984% |

Podsumowując: Funkcja kwadratowa zyskała najlepsze wyniki stosując metody kwadratów (jest ona szybsza od trapezów). Metoda Monte Carlo nie sprawdziła się tak dobrze jak pozostałe.

---

$$
f(x) = e^x
$$

$$
\int_{-2}^{2} e^x \, dx = e^x\bigg|_{-2}^{2} = e^2 - e^{-2} = e^2 - \frac{1}{e^2} \approx 7,3890560989 - \frac{1}{7,3890560989} = \frac{53,5981500327}{7,3890560989} \approx 7,2537208157
$$

Wykres dla 10, 50 i 100 kwadratów

Wyniki odpowiednio:

5.899436

7.109614

7.224745

![2_10_rectangle.jpg](doc_img/2_10_rectangle.jpg)

![2_50_rectangle.jpg](doc_img/2_50_rectangle.jpg)

![2_100_rectangle.jpg](doc_img/2_100_rectangle.jpg)

Wykres dla 10, 50 i 100 trapezów

Wyniki odpowiednio:

7.350180

7.257589

7.254688

![2_10_trapezoid.jpg](doc_img/2_10_trapezoid.jpg)

![2_50_trapezoid.jpg](doc_img/2_50_trapezoid.jpg)

![2_100_trapezoid.jpg](doc_img/2_100_trapezoid.jpg)

Wykres dla 500, 1000 i 5000 kropek

Wyniki odpowiednio:

7.388120

7.711349

7.412654

![2_500_monte-carlo.jpg](doc_img/2_500_monte-carlo.jpg)

![2_1000_monte-carlo.jpg](doc_img/2_1000_monte-carlo.jpg)

![2_5000_monte-carlo.jpg](doc_img/2_5000_monte-carlo.jpg)

$$
f(x) = \cos{2x}
$$

$$
\int_{-10}^{10} \cos{2x} \ dx = \frac{sin(2x)}{2} \bigg|_{-10}^{10} = \frac{\sin{20}}{2} - \frac{\sin{(-20)}}{2} \approx \frac{0,9129452507}{2} - \frac{-0,9129452507}{2} = 0,9129452507
$$

Wykres dla 10, 50 i 100 kwadratów

Wyniki odpowiednio:

-0.835633

0.863727

0.900740

![3_10_rectangle.jpg](doc_img/3_10_rectangle.jpg)

![3_50_rectangle.jpg](doc_img/3_50_rectangle.jpg)

![3_100_rectangle.jpg](doc_img/3_100_rectangle.jpg)

Wykres dla 10, 50 i 100 trapezów

Wyniki odpowiednio:

-0.835633

0.863727

0.900740

![3_10_trapezoid.jpg](doc_img/3_10_trapezoid.jpg)

![3_50_trapezoid.jpg](doc_img/3_50_trapezoid.jpg)

![3_100_trapezoid.jpg](doc_img/3_100_trapezoid.jpg)

Wykres dla 500, 1000 i 5000 kropek

Wyniki odpowiednio:

2.160000

1.600000

0.660000

(Kropki ze względu na mój algorytm pojawiają się tylko ponad 0, jednak jest to uznawane w obliczeniach)

![3_500_monte-carlo.jpg](doc_img/3_500_monte-carlo.jpg)

![3_1000_monte-carlo.jpg](doc_img/3_1000_monte-carlo.jpg)

![3_5000_monte-carlo.jpg](doc_img/3_5000_monte-carlo.jpg)

$$
f(x) = -2x^2 - 15
$$

$$
\int_{-10}^{10} -2x^2-15 \ dx = (\frac{-2x^3}{3} - 15x)\bigg|_{-10}^{10} = \frac{-2000}{3} - 150 - (\frac{2000}{3} + 150) = \frac{-4000}{3} - 300 \approx -1633.333
$$

Wykres dla 10, 50 i 100 kwadratów

Wyniki odpowiednio:

-1660.000000

-1634.400000

-1633.600000

![4_10_rectangle.jpg](doc_img/4_10_rectangle.jpg)

![4_50_rectangle.jpg](doc_img/4_50_rectangle.jpg)

![4_100_rectangle.jpg](doc_img/4_100_rectangle.jpg)

Wykres dla 10, 50 i 100 trapezów

Wyniki odpowiednio:

-1660.000000

-1634.400000

-1633.600000

![4_10_trapezoid.jpg](doc_img/4_10_trapezoid.jpg)

![4_50_trapezoid.jpg](doc_img/4_50_trapezoid.jpg)

![4_100_trapezoid.jpg](doc_img/4_100_trapezoid.jpg)

Wykres dla 500, 1000 i 5000 kropek

Wyniki odpowiednio:

-1573.800000

-1612.500000

-1618.520000

![4_500_monte-carlo.jpg](doc_img/4_500_monte-carlo.jpg)

![4_1000_monte-carlo.jpg](doc_img/4_1000_monte-carlo.jpg)

![4_5000_monte-carlo.jpg](doc_img/4_5000_monte-carlo.jpg)

Tutaj możecie zobaczyć tabelke z wynikami dla odpowiedniej ilości obliczeń

|  | $f(x) = x^2$
math 666666.(6)
rectangle
trapezoid
monte carlo | $f(x) = e^x
$
math 7.2537208157
rectangle
trapezoid
monte carlo | $f(x) = \cos{2x}$
math 0.9129452507
rectangle
trapezoid
monte carlo | $f(x) = -2x^2 - 15$
math -1633.333
rectangle
trapezoid
monte carlo |
| --- | --- | --- | --- | --- |
| 10 | 680000.0 (102.000000%)
680000.0 (102.000000%)
600000.0 (90.000000%) | 5.899436 (81.329791%)
7.350180 (101.329791%)
10.624374 (146.467922%) | -0.835633 (-91.531511%)
-0.835633 (-91.531511%)
-4.000000 (-438.142375%) | -1660.000000 (101.632653%)
-1660.000000 (101.632653%)
-1290.000000 (78.979592%) |
| 100 | 666800.0 (100.020000%)
666800.0 (100.020000%)
580000.0 (87.000000%) | 7.109614 (98.013333%)
7.254688 (100.013333%)
6.820958 (94.033926%) | 0.900740 (98.663098%)
0.900740 (98.663098%)
1.200000 (131.442712%) | -1633.600000 (100.016327%)
-1633.600000 (100.016327%)
-1290.000000 (78.979592%) |
| 1,000 | 666668.0 (100.000200%)
666668.0 (100.000200%)
678000.0 (101.700000%) | 7.239223 (99.800133%)
7.253730 (100.000133%)
7.183576 (99.032980%) | 0.912824 (99.986666%)
0.912824 (99.986666%)
0.300000 (32.860678%) | -1633.336000 (100.000163%)
-1633.336000 (100.000163%)
-1629.700000 (99.777551%) |
| 10,000 | 666666.68 (100.000002%)
666666.68 (100.000002%)
647400.0 (97.110000%) | 7.252270 (99.980001%)
7.253721 (100.000001%)
7.315222 (100.847861%) | 0.912944 (99.999867%)
0.912944 (99.999867%)
0.814000 (89.161973%) | -1633.333360 (100.000002%)
-1633.333360 (100.000002%)
-1646.040000 (100.777959%) |
| 100,000 | 666666.6668 (100.000000%)
666666.6668 (100.000000%)
671860.0 (100.779000%) | 7.253576 (99.998000%)
7.253721 (100.000000%)
7.280889 (100.374541%) | 0.912945 (99.999999%)
0.912945 (99.999999%)
0.878400 (96.216065%) | -1633.333334 (100.000000%)
-1633.333334 (100.000000%)
-1637.096000 (100.230368%) |
| 1,000,000 | 666666.666674 (100.000000%)
666666.666674 (100.000000%)
666924.000000 (100.038600%) | 7.253706 (99.999800%)
7.253721 (100.000000%)
7.258005 (100.059060%) | 0.912945 (100.000000%)
0.912945 (100.000000%)
0.893000 (97.815285%) | -1633.333333 (100.000000%)
-1633.333333 (100.000000%)
-1633.789300 (100.027917%) |
| 10,000,000 | 666666.666704 (100.000000%)
666666.666704 (100.000000%)
666636.000000 (99.995400%) | 7.253719 (99.999980%)
7.253721 (100.000000%)
7.260395 (100.092011%) | 0.912945 (100.000000%)
0.912945 (100.000000%)
0.916698 (100.411060%) | -1633.333333 (100.000000%)
-1633.333333 (100.000000%)
-1633.372630 (100.002406%) |

![Rectangle.drawio.svg](doc_img/Rectangle.drawio%202.svg)

Podsujmowując nie ma potrzeby stosowania 3 najbardziej skomplikowanej metody, wystarczy użyć trapezów a dostaniemy dużo lepszy wynik w dużo krótszym czasie

Poniżej znajdziesz kod z implementacją wszystkich 3 metod oraz link do githuba z tym kodem oraz dodatkowym który pomógł mi wygenerować tą dokumentacje

[https://github.com/Buczek05/Algorytmy_i_struktury_danych_projekt_1](https://github.com/Buczek05/Algorytmy_i_struktury_danych_projekt_1)

```c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct Integral{
    double (*integral_func)(double);
    float start_point;
    float end_point;
    long calculating_accuracy;
};

double get_step(struct Integral *integral){
    return (integral->end_point - integral->start_point) / (double) integral->calculating_accuracy;
}

double calculate_integral_using_rectangle(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        result += integral->integral_func(x) * step;
        x += step;
    }
    return result;
}

double calculate_integral_using_trapezoid(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double result = 0.0;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        result += (integral->integral_func(x) + integral->integral_func(x+step)) * step / 2;
        x += step;
    }
    return result;
}

double get_random_double(double min, double max) {
    return min + ((double) arc4random_uniform((u_int32_t) RAND_MAX) / (double) RAND_MAX) * (max - min);
}

double get_highest_y(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double highest_y = integral->integral_func(x), moment_y;
    for (long i = 1; i < integral->calculating_accuracy; i++) {
        moment_y = integral->integral_func(x);
        highest_y = moment_y > highest_y ? moment_y : highest_y;
        x += step;
    }
    return highest_y;
}

double get_lowest_y(struct Integral *integral){
    double step = get_step(integral);
    double x = integral->start_point;
    double lowest_y = integral->integral_func(x), moment_y;
    for (long i = 1; i < integral->calculating_accuracy; i++) {
        moment_y = integral->integral_func(x);
        lowest_y = moment_y < lowest_y ? moment_y : lowest_y;
        x += step;
    }
    return lowest_y;
}

double calculate_integral_using_monte_carlo(struct Integral *integral){
    int value;
    long point_under_lines = 0;
    double random_x, random_y;
    double highest_y = get_highest_y(integral);
    double lowest_y = get_lowest_y(integral);
    highest_y = fabs(lowest_y) > highest_y ? fabs(lowest_y) : highest_y;
    double y;
    for (long i = 0; i < integral->calculating_accuracy; i++) {
        random_x = get_random_double(integral->start_point, integral->end_point);
        random_y = get_random_double(0., highest_y);
        y = integral->integral_func(random_x);
        if (y < 0) value = random_y <= fabs(y) ? -1 : 0;
        else if (y >= 0) value = random_y <= y ? 1 : 0;
        else value = 0;
        point_under_lines += value;
    }
    double coverage = (double) point_under_lines / (double) integral->calculating_accuracy;
    return (integral->end_point - integral->start_point) * highest_y * coverage;
}
```