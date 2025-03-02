    // Obliczanie punktow do szkoly sredniej
    // Program zgodny z podstawa naukowa 2025
    // Wszystkie prawa zastrzezone Kerso 2025
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include <map>
    #include <vector>
    #include <limits>
    #ifdef _WIN32
    #include <conio.h>
    #else
    #include <termios.h>
    #include <unistd.h>
    #endif

    // Definiowanie kolorow ASCII
    #define RESET "\033[0m"
    #define RED "\033[31m"
    #define GREEN "\033[32m"
    #define YELLOW "\033[33m"
    #define BLUE "\033[34m"
    #define PURPLE "\033[1;35m"

    // Universal pause function
    void waitForKeyPress() {
        std::cout << BLUE << "Naciśnij dowolny klawisz, aby wyjść..." << RESET << std::endl;
        #ifdef _WIN32
            _getch(); // Wykryj przycisniecie klawisza (WIN)
        #else
            struct termios oldt, newt;
            tcgetattr(STDIN_FILENO, &oldt); // Zdobadz aktualne ustawienia terminala
            newt = oldt;
            newt.c_lflag &= ~ICANON; // Disable canonical mode (line buffering)
            newt.c_lflag &= ~ECHO; // Disable echoing input characters
            tcsetattr(STDIN_FILENO, TCSANOW, &newt); // Apply the new settings
            getchar(); // Wait for any key press (Linux/macOS)
            tcsetattr(STDIN_FILENO, TCSADRAIN, &oldt); // Restore the old terminal settings
        #endif
    }

    // Funkcja do zamiany oceny na punkty
    int ocenaNaPunkty(const std::string& ocena) {
        // Mapa przypisująca ocenom odpowiednie wartości punktowe
        static const std::map<std::string, int> punktacja = {
            {"celujący", 18},
            {"celujaca", 18},
            {"celująca", 18},
            {"6", 18},
            {"bardzo dobry", 17},
            {"bardzo dobra", 17},
            {"5", 17},
            {"dobry", 14},
            {"dobra", 14},
            {"4", 14},
            {"dostateczny", 8},
            {"dostateczna", 8},
            {"3", 8},
            {"dopuszczający", 2},
            {"dopuszczajaca", 2},
            {"dopuszczająca", 2},
            {"2", 2}
        };

        // Sprawdzamy, czy podana ocena istnieje w mapie
        auto it = punktacja.find(ocena);
        if (it != punktacja.end()) {
            return it->second;
        } else {
            std::cout << RED << "Nieznana ocena: " << ocena << ". Przyznano 0 punktów." << RESET << std::endl;
            return 0;
        }
    }

    // Glowna funkcja programu
    int main() {
        // USTAWIENIA APLIKACJI
        bool debug = false; // Zmienna decydujaca o trybie debugowania
        std::string wersjaAplikacji = " 2.1.0"; // Zmienna informujaca o wersji programu
        bool blocked = false; // Zmienna decydujaca o tym, czy program jest zablokowany
        
        std::cout << PURPLE << R"(
        _   ________ _   _______ 
        | | / /| ___ \ | / /_   _|
        | |/ / | |_/ / |/ /  | |  
        |    \ |  __/|    \  | |  
        | |\  \| |   | |\  \ | |  
        \_| \_/\_|   \_| \_/ \_/  
            )" << RESET << std::endl;
        
        std::cout << "Kalkulator punktów do szkoły średniej" << std::endl;
        std::cout << "Autor programu: " << PURPLE << "kerso.dev" << RESET << std::endl;
        std::cout << "\n";
        
        // Sprawdz czy tryb debugowania jest uruchomiony
        if (debug == true) {
            std::cout << YELLOW << "[DEBUG] TRYB DEBUGOWANIA URUCHOMIONY" << RESET << std::endl;
            std::cout << YELLOW << "[DEBUG] WERSJA PROGRAMU: " << wersjaAplikacji << RESET << std::endl;
            std::cout << YELLOW << "[DEBUG] STATUS ZABLOKOWANIA: " << blocked << RESET << std::endl;
        }
        
        // Sprawdz czy zmienna blokady rowna sie "true"
        if (blocked == true) {
            std::cout << RED << "[SECURITY]: PROGRAM ZOSTAŁ ZABLOKOWANY, PROSZĘ SKONTAKTOWAĆ SIĘ Z ADMINISTRATOREM." << RESET << std::endl;
            waitForKeyPress(); // Zaczekaj na przycisniecie klawisza
            return 1;
        }
        
        // ----- CZĘŚĆ 1: PUNKTY ZA EGZAMINY -----
        std::cout << PURPLE << "\n===== PUNKTY ZA EGZAMINY =====" << RESET << std::endl;
        
        // Zdobywanie danych o punktacji z egzamiów
        double pktPl, pktMat, pktEn;
        
        // J.POLSKI
        std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Języka Polskiego: " << RESET;
        std::cin >> pktPl;
        
        pktPl *= 0.35;
        if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktPl << RESET << std::endl;
        
        // MATEMATYKA
        std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Matematyki: " << RESET;
        std::cin >> pktMat;
        
        pktMat *= 0.35;
        if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktMat << RESET << std::endl;
        
        // J. OBCY NOWOŻYTNY
        std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Języka obcego nowożytnego: " << RESET;
        std::cin >> pktEn;
        
        pktEn *= 0.30;
        if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktEn << RESET << std::endl;
        
        // Sumowanie punktów za egzamin
        double sumaEgzaminy = pktPl + pktMat + pktEn;
        std::cout << GREEN << "Suma punktów za egzaminy: " << sumaEgzaminy << RESET << std::endl;
        
        // ----- CZĘŚĆ 2: PUNKTY ZA OCENY ZE ŚWIADECTWA -----
        std::cout << PURPLE << "\n===== PUNKTY ZA OCENY ZE ŚWIADECTWA =====" << RESET << std::endl;
        std::cout << "Punktacja:" << std::endl;
        std::cout << "Celujący - 18 pkt" << std::endl;
        std::cout << "Bardzo dobry - 17 pkt" << std::endl;
        std::cout << "Dobry - 14 pkt" << std::endl;
        std::cout << "Dostateczny - 8 pkt" << std::endl;
        std::cout << "Dopuszczający - 2 pkt" << std::endl;

        int liczbaPrzedmiotow = 2; // Domyślnie 2 przedmioty (Polski i Matematyka)
        std::cout << BLUE << "Domyślnie wybrane przedmioty: Język Polski, Matematyka." << RESET << std::endl;

        std::vector<std::pair<std::string, int>> przedmioty;
        przedmioty.push_back({"Język Polski", 0});
        przedmioty.push_back({"Matematyka", 0});

        std::string ocena;
        int sumaPunktowSwiadectwo = 0;

        // Wczytywanie ocen z przedmiotów
        for (int i = 0; i < liczbaPrzedmiotow; i++) {
            std::string ocena;
            
            // Wyczyść bufor wejściowy
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            std::cout << BLUE << "Podaj ocenę z przedmiotu " << przedmioty[i].first << " (słownie lub cyfrą): " << RESET;
            
            // Wczytanie oceny
            std::getline(std::cin, ocena);

            // Sprawdzamy, czy ocena jest pusta
            if (ocena.empty()) {
                std::cout << RED << "Ocena nie może być pusta. Spróbuj ponownie." << RESET << std::endl;
                i--;  // Zmniejszamy i, aby powtórzyć wpisanie dla tego przedmiotu
                continue;
            }

            // Zamiana oceny na małe litery dla ułatwienia porównania
            for (char& c : ocena) {
                c = std::tolower(c);
            }

            // Sprawdzamy punkty
            int punkty = ocenaNaPunkty(ocena);
            przedmioty[i].second = punkty;  // Przypisanie punktów do przedmiotu
            sumaPunktowSwiadectwo += punkty;
        }

        std::cout << BLUE << "Czy chcesz dodać 2 dodatkowe przedmioty? (T/N): " << RESET;
        char odpowiedz;
        std::cin >> odpowiedz;
        std::cin.ignore();  // Ignoruje znak nowej linii po odpowiedzi

        if (odpowiedz == 'T' || odpowiedz == 't') {
            for (int i = 0; i < 2; i++) {
                std::string nazwaPrzedmiotu;
                std::cout << BLUE << "Podaj nazwę dodatkowego przedmiotu " << i + 1 << ": " << RESET;
                std::getline(std::cin, nazwaPrzedmiotu);

                std::cout << BLUE << "Podaj ocenę z przedmiotu " << nazwaPrzedmiotu << " (słownie lub cyfrą): " << RESET;
                std::getline(std::cin, ocena);

                // Zamiana oceny na małe litery dla ułatwienia porównania
                for (char& c : ocena) {
                    c = std::tolower(c);
                }

                int punkty = ocenaNaPunkty(ocena);
                sumaPunktowSwiadectwo += punkty;
                przedmioty.push_back({nazwaPrzedmiotu, punkty});
                if (debug) std::cout << YELLOW << "[DEBUG]: PRZYZNANE PUNKTY ZA " << nazwaPrzedmiotu << ": " << punkty << RESET << std::endl;
            }
        }

        // Wyświetlenie podsumowania ocen
        std::cout << PURPLE << "\n===== PODSUMOWANIE PUNKTÓW ZA ŚWIADECTWO =====" << RESET << std::endl;
        for (const auto& przedmiot : przedmioty) {
            std::cout << przedmiot.first << ": " << GREEN << przedmiot.second << " pkt" << RESET << std::endl;
        }
        std::cout << "Suma punktów za świadectwo: " << GREEN << sumaPunktowSwiadectwo << " pkt" << RESET << std::endl;
        
        // ----- CZĘŚĆ 3: PUNKTY ZA DODATKOWE OSIĄGNIĘCIA -----
        std::cout << PURPLE << "\n===== PUNKTY ZA DODATKOWE OSIĄGNIĘCIA =====" << RESET << std::endl;
        
        int punktyDodatkowe = 0;
        std::vector<std::pair<std::string, int>> osiagniecia;
        
        // Wolontariat
        char odpowiedzWolontariat;
        std::cout << BLUE << "Czy uczeń brał udział w wolontariacie [T/N]: " << RESET;
        std::cin >> odpowiedzWolontariat;
        
        if (odpowiedzWolontariat == 'T' || odpowiedzWolontariat == 't') {
            punktyDodatkowe += 3;
            osiagniecia.push_back({"Wolontariat", 3});
            if (debug) std::cout << YELLOW << "[DEBUG]: DODANO 3 PKT ZA WOLONTARIAT" << RESET << std::endl;
        }
        
        // Świadectwo z wyróżnieniem
        char odpowiedzWyroznienie;
        std::cout << BLUE << "Czy uczeń otrzymał świadectwo ukończenia szkoły z wyróżnieniem [T/N]: " << RESET;
        std::cin >> odpowiedzWyroznienie;
        
        if (odpowiedzWyroznienie == 'T' || odpowiedzWyroznienie == 't') {
            punktyDodatkowe += 7;
            osiagniecia.push_back({"Świadectwo z wyróżnieniem", 7});
            if (debug) std::cout << YELLOW << "[DEBUG]: DODANO 7 PKT ZA ŚWIADECTWO Z WYRÓŻNIENIEM" << RESET << std::endl;
        }
        
        // Wyświetlenie podsumowania dodatkowych osiągnięć
        if (!osiagniecia.empty()) {
            std::cout << "\nDodatkowe osiągnięcia:" << std::endl;
            for (const auto& osiagniecie : osiagniecia) {
                std::cout << osiagniecie.first << ": " << GREEN << osiagniecie.second << " pkt" << RESET << std::endl;
            }
        } else {
            std::cout << "Brak dodatkowych osiągnięć." << std::endl;
        }
        
        std::cout << "Suma punktów za dodatkowe osiągnięcia: " << GREEN << punktyDodatkowe << " pkt" << RESET << std::endl;
        
        // ----- CZĘŚĆ 4: ŁĄCZNE PODSUMOWANIE -----
        std::cout << PURPLE << "\n===== PODSUMOWANIE KOŃCOWE =====" << RESET << std::endl;
        std::cout << "Punkty za egzaminy: " << GREEN << sumaEgzaminy << " pkt" << RESET << std::endl;
        std::cout << "Punkty za świadectwo: " << GREEN << sumaPunktowSwiadectwo << " pkt" << RESET << std::endl;
        std::cout << "Punkty za dodatkowe osiągnięcia: " << GREEN << punktyDodatkowe << " pkt" << RESET << std::endl;
        
        double sumaLaczna = sumaEgzaminy + sumaPunktowSwiadectwo + punktyDodatkowe;
        std::cout << "ŁĄCZNA LICZBA PUNKTÓW: " << GREEN << sumaLaczna << " pkt" << RESET << std::endl;
        
        if (debug) std::cout << YELLOW << "[DEBUG]: KONIEC PROGRAMU" << RESET << std::endl;
        
        waitForKeyPress(); // Czekaj na przycisk przed zamknięciem
        return 0;
    }
