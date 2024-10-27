#include "modAlphaCipher.h"
#include <iostream>
#include <locale>
#include <codecvt>
using namespace std;
void check(wstring text, wstring key, bool destructCipherText = false)
{
    try {
        wstring cipherText;
        wstring decryptedText;
        Cipher cipher(key);
        cipherText = cipher.encrypt(text);
        if (destructCipherText)
            cipherText.front() = towlower(cipherText.front());
        decryptedText = cipher.decrypt(cipherText);
        wcout << L"key=" << key << endl;
        wcout << text << endl;
        wcout << cipherText << endl;
        wcout << decryptedText << endl;
    } catch (const cipher_error& e) {
        wcerr << "Error: " << e.what() << endl;
    }
}
void interface_program()
{
    wstring key;
    wstring text;
    unsigned op;
    wcout << L"Введите ключ(Кол-во столбцов): ";
    wcin >> key;
    Cipher cipher(key);
    do {
        wcout << L"Выберите операцию (0-выход, 1-зашифровать, 2-расшифровать, 3-ключ): ";
        wcin >> op;
        if (op > 3) {
            wcout << L"Не может быть, попробуй другую операцию\n";
        } else if (op > 0 && op < 3) {
            wcout << L"Введите текст: ";
            wcin >> text;
            if (op == 1) {
                wcout << L"Зашифрованный текст: " << cipher.encrypt(text) << endl;
            } else {
                wcout << L"Расшифрованный текст: " << cipher.decrypt(text) << endl;
            }
        } else if (op == 3) {
            wcout << L"Введите ключ заново(Кол-во столбцов): ";
            wcin >> key;
            cipher.set_key(key);
        }
    } while (op != 0);
}
int main(int argc, char** argv)
{
    locale loc("ru_RU.UTF-8");
    locale::global(loc);
    wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t> codec;
    unsigned mode_program;
    do {
        wcout << L"Интерфейс (1) или тест программы (2)? Выход (0). Ввод:";
        wcin >> mode_program;
        if (mode_program == 1) {
            interface_program();
        } else if (mode_program == 2) {
            wstring nothing = L"------------------------------";
            check(L"Привет", L"0");
            wcout << nothing << endl;
            check(L"Привет", L"");
            wcout << nothing << endl;
            check(L"Привет", L">!-*k");
            wcout << nothing << endl;
            check(L"Привет", L"5", true);
            wcout << nothing << endl;
            check(L"Привет", L"5");
            wcout << nothing << endl;
            check(L"При4вет", L"5");
            wcout << nothing << endl;
            check(L"Привет", L"5");
            wcout << nothing << endl;
            check(L"", L"5");
            wcout << nothing << endl;
            check(L"Привет", L"5");
            wcout << nothing << endl;
            return 0;
        }
    } while (mode_program != 0);
    return 0;
}