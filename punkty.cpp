// Obliczanie punktow do szkoly sredniej
// Program zgodny z podstawa naukowa 2025
// Wszystkie prawa zastrzezone Kerso 2025
#include <iostream>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

// Definiowanie kolorow ASCII
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[1;35m"

// Universal pause function
void waitForKeyPress() {
    std::cout << BLUE << "Naciśnij dowolny klawisz, aby wyjść..." << RESET << std::endl; 
    
    #ifdef _WIN32
        _getch();  // Wykryj przycisniecie klawisza (WIN)
    #else
        struct termios oldt, newt;
        tcgetattr(STDIN_FILENO, &oldt);  // Zdobadz aktualne ustawienia terminala
        newt = oldt;
        newt.c_lflag &= ~ICANON;  // Disable canonical mode (line buffering)
        newt.c_lflag &= ~ECHO;    // Disable echoing input characters
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);  // Apply the new settings

        getchar();  // Wait for any key press (Linux/macOS)

        tcsetattr(STDIN_FILENO, TCSADRAIN, &oldt);  // Restore the old terminal settings
    #endif
    
    // Wyjdz z programu
    exit(0);
}

// Glowna funkcja programu
int main() {
    // USTAWIENIA APLIKACJI
    bool debug = true;    // Zmienna decydujaca o trybie debugowania
    std::pmr::string wersjaAplikacji = "DEV 1.0.0"; // Zmienna informujaca o wersji programu
    bool blocked = false;   // Zmienna decydujaca o tym, czy program jest zablokowany
    
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
        waitForKeyPress();  // Zaczekaj na przycisniecie klawisza
    }

    // Zdobywanie danych o punktacji z egzamiów
    double pktPl, pktMat, pktEn;

    // J.POLSKI
    std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Języka Polskiego: " << RESET << std::endl;
    std::cin >> pktPl;
    pktPl *= 0.35;
    if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktPl << RESET << std::endl;

    // MATEMATYKA
    std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Matematyki: " << RESET << std::endl;
    std::cin >> pktMat;
    pktMat *= 0.35;
    if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktMat << RESET << std::endl;

    // J. OBCY NOWOŻYTNY
    std::cout << BLUE << "Proszę wprowadzić liczbę procent z egz. z Języka obcego nowożytnego: " << RESET << std::endl;
    std::cin >> pktEn;
    pktEn *= 0.30;
    if (debug) std::cout << YELLOW << "[DEBUG]: OBLICZONA ILOŚĆ PKT: " << pktEn << RESET << std::endl;

    // Sumowanie punktów za egzamin
    std::cout << PURPLE << "Suma punktów za egzamin: " << pktPl+pktMat+pktEn << RESET << std::endl;

    if (debug) std::cout << YELLOW << "[DEBUG]: KONIEC PROGRAMU" << RESET << std::endl;
    
    return (0);
}
