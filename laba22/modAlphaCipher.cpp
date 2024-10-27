#include "modAlphaCipher.h"

Cipher::Cipher(std::wstring& ws_key)
{
    column = getValidKey(ws_key);
}
void Cipher::set_key(std::wstring& ws_key)
{
    column = getValidKey(ws_key);
}
void Cipher::set_tableform(const std::wstring& open_text)
{
    len_text = open_text.size();
    if (len_text > column) {
        num_letters_entered = len_text / column;
        if (len_text % column > 0) num_letters_entered += 1;
    } else {
        num_letters_entered = 1;
    }
}
std::wstring Cipher::encrypt(std::wstring& open_text)
{
    open_text = getValidOpenText(open_text);
    set_tableform(open_text);
    std::wstring table_chiper[num_letters_entered][column];
    int nums_text = 0;
    for (int y = 0; y < num_letters_entered; y++) {
        for (int x = 0; x < column; x++) {
            if (nums_text < len_text) {
                table_chiper[y][x] = open_text[nums_text];
            } else {
                table_chiper[y][x] = L"-";
            }
            nums_text++;
        }
    }
    std::wstring encrypt_text;
    for (int x = column - 1; x >= 0; x--) {
        for (int y = 0; y < num_letters_entered; y++) {
            encrypt_text += table_chiper[y][x];
        }
    }
    return encrypt_text;
}
std::wstring Cipher::decrypt(const std::wstring& cipher_text)
{
    set_tableform(getValidCipherText(cipher_text));
    std::wstring table_chiper[num_letters_entered][column];
    int nums_text = 0;
    for (int x = column - 1; x >= 0; x--) {
        for (int y = 0; y < num_letters_entered; y++) {
            table_chiper[y][x] = cipher_text[nums_text];
            nums_text++;
        }
    }
    std::wstring decrypt_text;
    for (int y = 0; y < num_letters_entered; y++) {
        for (int x = 0; x < column; x++) {
            if (table_chiper[y][x] != L"-")
                decrypt_text += table_chiper[y][x];
        }
    }
    return decrypt_text;
}
inline int Cipher::getValidKey(std::wstring& ws_key)
{
    if (ws_key.empty())
        throw cipher_error("Empty key");
    std::string s_key = codec.to_bytes(ws_key);
    for (auto& c : ws_key) {
        if (!iswdigit(c)) {
            throw cipher_error(std::string("Invalid key") + s_key);
        }
    }
    int key = std::stoi(ws_key);
    if (key <= 0) {
        throw cipher_error(std::string("Invalid key. Enter a number > 0"));
    }
    return key;
}
inline std::wstring Cipher::getValidOpenText(const std::wstring& ws_open_text)
{
    std::wstring tmp;
    for (auto c : ws_open_text) {
        if (iswalpha(c)) {
            if (iswlower(c))
                tmp.push_back(towupper(c));
            else
                tmp.push_back(c);
        }
    }
    if (tmp.empty())
        throw cipher_error("Input text is missing");
    return tmp;
}
inline std::wstring Cipher::getValidCipherText(const std::wstring& ws_cipher_text)
{
    if (ws_cipher_text.empty())
        throw cipher_error("Output text is missing");

    for (auto c : ws_cipher_text) {
        if (!iswupper(c)) {
            if (c != L'-') {
                throw cipher_error(std::string("Invalid text"));
            }
        }
    }
    return ws_cipher_text;
}