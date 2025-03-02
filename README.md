# KPKT

KPKT to kalkulator punktów do szkoły średniej zaprogramowany w języku c++.

## Zastosowanie

***Aby zacząć korzystać z programu wystarczy pobrać *ostatnią wersję programu* z githuba.***

Jeśli chcesz zablokować aplikację lub uruchomić tryb debugowania, musisz ***zkompilować ją od nowa***.

Kompilowanie i uruchamianie programu na Linuxie:

```shell
# Kompilowanie za pomocą g++
g++ punkty.cpp -o kpkt

# Kompilowanie za pomocą Clang (alternatywa g++)
clang++ punkty.cpp -o kpkt

# Uruchamianie programu
./kpkt
```
Kompilowanie i uruchamianie programu na Windowsie:

```bash
# Kompilowanie za pomocą MinGW (wersja g++ dla windowsa)
g++ punkty.cpp -o kpkt.exe

# Uruchamianie programu
./kpkt.exe
```

## Dodatkowe informacje

W repozytorium znajduje się również plik `pdf_gen.cpp`, jest on **programem testowym**, który generuje plik PDF z danymi podanymi podczas korzystania z programu.

**Po co istnieje `pdf_gen.cpp`?** Program może zostanie zaimplementowany w **KPKT** po to aby generować raport z punktacji.

## Licencja

[CC BY-NC](https://creativecommons.org/licenses/by-nc/4.0/deed.pl)
