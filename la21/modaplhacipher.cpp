#include "modalphacipher.h"
modalphacipher::modalphacipher(
    const std::wstring& wskey)
{
    for (unsigned i = 0; i < numAlpha.size(); i++) {
        alphaNum[numAlpha[i]] = i;
    }
    key = convert(getValidKey(wskey));
}
std::wstring modalphacipher::encrypt(const std::wstring& open_text)
{
    std::vector<int> work = convert(getValidOpenText(open_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
std::wstring modalphacipher::decrypt(const std::wstring& cipher_text)
{
    std::vector<int> work = convert(getValidCipherText(cipher_text));
    for (unsigned i = 0; i < work.size(); i++) {
        work[i] = (work[i] + alphaNum.size() - key[i % key.size()]) % alphaNum.size();
    }
    return convert(work);
}
inline std::vector<int> modalphacipher::convert(const std::wstring& ws)
{
    std::vector<int> result;
    for (auto c : ws) {
        result.push_back(alphaNum[c]);
    }
    return result;
}
inline std::wstring modalphacipher::convert(const std::vector<int>& v)
{
    std::wstring result;
    for (auto i : v) {
        result.push_back(numAlpha[i]);
    }
    return result;
}
inline std::wstring modalphacipher::getValidKey(const std::wstring& ws)
{
    if (ws.empty())
        throw cipher_error("Empty key");
    std::wstring tmp(ws);
    std::string s = codec.to_bytes(ws);
    for (auto& c : tmp) {
        if (!iswalpha(c)) {
            throw cipher_error(std::string("Invalid key") + s);
        }
        if (iswlower(c))
            c = towupper(c);
    }
    return tmp;
}
inline std::wstring modalphacipher::getValidOpenText(const std::wstring& ws)
{

    std::wstring tmp;
    for (auto c : ws) {
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
inline std::wstring modalphacipher::getValidCipherText(const std::wstring& ws)
{
    if (ws.empty())
        throw cipher_error("Output text is missing");
    for (auto c : ws) {
        std::string s = codec.to_bytes(ws);
        if (!iswupper(c))
            throw cipher_error(std::string("Invalid text") + s);
    }
    return ws;
}