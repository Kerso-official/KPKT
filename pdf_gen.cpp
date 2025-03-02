// Testowy kod do generowania pliku PDF za pomocą libharu
// Wszystkie prawa zastrzeżone kerso.dev 2025
#include <iostream>
#include <hpdf.h>
#include <ctime>

// Definiowanie kolorow ASCII
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define PURPLE  "\033[1;35m"
    
// Handler errorów 
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void *user_data) {
    std::cerr << RED << "[ERROR]: " << error_no << ", detale: " << detail_no << RESET << std::endl;
}

// Pobranie aktualniej daty i godziny jako string
std::string getCurrentDateTime() {
    time_t now = time(0);
    struct tm tstruct;
    char buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", &tstruct);
    return std::string(buf);
}

void generatePDF(const std::string &filename, const std::string &title, const std::string &content) {
    HPDF_Doc pdf = HPDF_New(error_handler, nullptr);
    if (!pdf) {
        std::cerr << RED << "[ERROR]: Wystąpił bląd podczas tworzenia pliku PDF!" << RESET << std::endl;
        return;
    }

    // Enable UTF-8 support
    HPDF_UseUTFEncodings(pdf);
    HPDF_SetCurrentEncoder(pdf, "UTF-8");

    HPDF_Page page = HPDF_AddPage(pdf);
    HPDF_Page_SetWidth(page, 600);
    HPDF_Page_SetHeight(page, 800);

    // Load the TrueType font with proper encoding
    const char* fontname = HPDF_LoadTTFontFromFile(pdf, "/usr/share/fonts/TTF/DejaVuSans.ttf", HPDF_TRUE);
    if (!fontname) {
        std::cerr << RED << "[ERROR]: Wystąpił błąd podczas załadowywania czcionki!" << RESET << std::endl;
        HPDF_Free(pdf);
        return;
    }
    
    HPDF_Font font = HPDF_GetFont(pdf, fontname, "UTF-8");

    // Header (Title)
    HPDF_Page_SetFontAndSize(page, font, 24);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 750, title.c_str());
    HPDF_Page_EndText(page);

    // Date & Time
    HPDF_Page_SetFontAndSize(page, font, 16);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 400, 780, getCurrentDateTime().c_str());
    HPDF_Page_EndText(page);

    // Content
    HPDF_Page_SetFontAndSize(page, font, 16);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 700, content.c_str());
    HPDF_Page_EndText(page);

    // Footer
    HPDF_Page_SetFontAndSize(page, font, 12);
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, 50, 50, "Dokument wygenerowany za pomocą programu PDF GEN");
    HPDF_Page_EndText(page);

    // Save to file
    HPDF_SaveToFile(pdf, filename.c_str());
    HPDF_Free(pdf);

    std::cout << PURPLE << "[PDF ]: Plik PDF został wygenerowany: " << filename << RESET << std::endl;
}

int main() {
    std::cout << PURPLE << R"(
    __________________   _____  _____ _   _ 
    | ___ \  _  \  ___| |  __ \|  ___| \ | |
    | |_/ / | | | |_    | |  \/| |__ |  \| |
    |  __/| | | |  _|   | | __ |  __|| . ` |
    | |   | |/ /| |     | |_\ \| |___| |\  |
    \_|   |___/ \_|      \____/\____/\_| \_/                                                            
    )" << RESET << std::endl;
    std::cout << PURPLE << "Program testowy do generowania plików PDF" << RESET << std::endl;
    std::cout << PURPLE << "Autor programu: kerso :3" << RESET << std::endl;

    // Input danych do PDF-u
    std::cout << BLUE << "Proszę wprowadzić nazwę pliku PDF: " << RESET << std::endl;
    std::string fileNameInput;
    std::getline(std::cin >> std::ws, fileNameInput);
    fileNameInput += ".pdf"; // Dodawanie .pdf do nazwy pliku
    std::cout << BLUE << "Proszę wprowadzić tytuł dokumentu: " << RESET << std::endl;
    std::string titleInput;
    std::getline(std::cin >> std::ws, titleInput);
    std::cout << BLUE << "Proszę wprowadzić zawartość dokumentu: " << RESET << std::endl;
    std::string contentInput;
    std::getline(std::cin >> std::ws, contentInput);

    // Wykonywanie funkcji generatePDF
    std::cout << PURPLE << "[PDF]: Trwa generowanie pliku PDF. Proszę czekać..." << RESET << std::endl;
    generatePDF(fileNameInput, titleInput, contentInput);
    return 0;
}
