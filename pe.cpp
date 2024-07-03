#include <stdio.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <string.h>
#include <string_view>
#include <conio.h>

void pe(const char* pe_file_path) {
    FILE* file = NULL; 
    errno_t error_code = fopen_s(&file, pe_file_path, "rb"); 

    if (error_code != 0 || file == NULL) {
        std::string error_message = "error opening file: " + std::to_string(error_code);
        throw std::runtime_error(error_message);
    }

    IMAGE_DOS_HEADER dos_header; 
    IMAGE_NT_HEADERS nt_header; 

    fread(&dos_header, sizeof(IMAGE_DOS_HEADER), 1, file); 

    if (dos_header.e_magic != IMAGE_DOS_SIGNATURE) {
        fclose(file); // closing the opened file
        throw std::runtime_error("invalid dos signature");
    }
    fseek(file, dos_header.e_lfanew, SEEK_SET);

    fread(&nt_header, sizeof(IMAGE_NT_HEADERS), 1, file); 


    if (nt_header.Signature != IMAGE_NT_SIGNATURE) {
        fclose(file);
        throw std::runtime_error("invalid nt signature");
    }

    std::cout << ">-> every value is within hex\n\n";
    std::cout << "<-> base address: 0x" << std::hex << nt_header.OptionalHeader.ImageBase << "\n";
    std::cout << "<-> size of image: 0x" << std::hex << nt_header.OptionalHeader.SizeOfImage << "\n";
    std::cout << "<-> size of stack reserve: 0x" << std::hex << nt_header.OptionalHeader.SizeOfStackReserve << "\n"; 

    _getch();
}


int main() {
    pe("C:\\Program Files (x86)\\AssaultCube 1.3.0.2\\bin_win32\\ac_client.exe");
}


