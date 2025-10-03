#pragma once

#ifdef _WIN32
#include <afxext.h>
#include <windows.h>
#else

#include <cstdint>
#include <string>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <list>

typedef unsigned char BYTE;
typedef int BOOL;
typedef long LONG;
typedef long long LONGLONG;
typedef uint32_t DWORD;
typedef uint16_t WORD;
typedef unsigned int UINT;
typedef long long __int64;
typedef long long _int64;
#ifndef LIBS101_API
#define LIBS101_API
#endif
typedef void* HMODULE;

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

struct tagPOINT { 
    long x; long y; 
    tagPOINT() : x(0), y(0) {}
    tagPOINT(long xx, long yy) : x(xx), y(yy) {}
};
typedef tagPOINT POINT;
typedef tagPOINT CPoint;
typedef wchar_t TCHAR;
#ifndef MAX_PATH
#define MAX_PATH 260
#endif

// CString minimal shim using std::wstring (UTF-16-esque API surface)
class CString {
public:
    CString() = default;
    CString(const wchar_t* ws) : w_(ws ? ws : L"") {}
    CString(const char* s) { w_ = utf8ToWstring(s ? std::string(s) : std::string()); }
    CString(const std::string& s) { w_ = utf8ToWstring(s); }

    int GetLength() const { return static_cast<int>(w_.size()); }
    const wchar_t* GetString() const { return w_.c_str(); }
    operator const wchar_t*() const { return w_.c_str(); }

    void Format(const wchar_t* fmt, const char* a) {
        // naive conversion: treat input as UTF-8
        std::wstring ws = utf8ToWstring(a ? std::string(a) : std::string());
        w_ = wstringFormat(fmt, ws.c_str());
    }

    void Format(const wchar_t* fmt, const wchar_t* a) {
        w_ = wstringFormat(fmt, a ? a : L"");
    }

    void Format(const wchar_t* fmt, int value) {
        wchar_t buf[64];
        std::swprintf(buf, sizeof(buf)/sizeof(buf[0]), fmt, value);
        w_ = buf;
    }

    void Format(const wchar_t* fmt, long long value) {
        wchar_t buf[64];
        std::swprintf(buf, sizeof(buf)/sizeof(buf[0]), fmt, value);
        w_ = buf;
    }

    CString& operator=(const wchar_t* ws) { w_ = ws ? ws : L""; return *this; }
    CString& operator=(const std::wstring& ws) { w_ = ws; return *this; }

    const std::wstring& std() const { return w_; }
    void AppendChar(wchar_t ch) { w_.push_back(ch); }

    // Append helpers
    void Append(const CString& other) { w_ += other.w_; }
    void Append(const wchar_t* s) { w_ += (s ? s : L""); }

    // Find helpers
    int Find(wchar_t ch) const {
        auto pos = w_.find(ch);
        return pos == std::wstring::npos ? -1 : static_cast<int>(pos);
    }
    int Find(const wchar_t* sub) const {
        if (!sub) return -1;
        auto pos = w_.find(sub);
        return pos == std::wstring::npos ? -1 : static_cast<int>(pos);
    }

    // Indexing
    wchar_t& operator[](int i) { return w_[static_cast<size_t>(i)]; }
    const wchar_t& operator[](int i) const { return w_[static_cast<size_t>(i)]; }

    // Delete one char at index
    void Delete(int i) {
        if (i >= 0 && static_cast<size_t>(i) < w_.size()) w_.erase(w_.begin() + i);
    }

    bool IsEmpty() const { return w_.empty(); }
    int ReverseFind(wchar_t ch) const {
        auto pos = w_.rfind(ch);
        return pos == std::wstring::npos ? -1 : static_cast<int>(pos);
    }
    CString Mid(int start) const {
        if (start < 0) start = 0;
        CString r; r.w_ = w_.substr(static_cast<size_t>(start)); return r;
    }
    CString Left(int count) const {
        if (count < 0) count = 0;
        if (static_cast<size_t>(count) > w_.size()) count = static_cast<int>(w_.size());
        CString r; r.w_ = w_.substr(0, static_cast<size_t>(count)); return r;
    }
    CString Right(int count) const {
        if (count < 0) count = 0;
        size_t c = static_cast<size_t>(count);
        if (c > w_.size()) c = w_.size();
        CString r; r.w_ = w_.substr(w_.size() - c); return r;
    }

    // Buffer access
    wchar_t* GetBuffer(int n) {
        w_.assign(static_cast<size_t>(n), L'\0');
        return w_.data();
    }
    void ReleaseBuffer() {
        w_.resize(std::wcslen(w_.c_str()));
    }

    // Concatenation
    CString operator+(const CString& other) const {
        CString r; r.w_ = w_ + other.w_; return r;
    }
    friend CString operator+(const wchar_t* lhs, const CString& rhs) {
        CString r; r.w_ = (lhs ? lhs : L"") + rhs.w_; return r;
    }

private:
    std::wstring w_;

    static std::wstring utf8ToWstring(const std::string& s) {
        std::wstring out;
        out.reserve(s.size());
        for (unsigned char c : s) out.push_back((wchar_t)c);
        return out;
    }

    static std::wstring wstringFormat(const wchar_t* fmt, const wchar_t* a) {
        // support only "%S" or "%ls" replacement of one argument used in code
        std::wstring f(fmt ? fmt : L"");
        size_t pos = f.find(L"%S");
        if (pos == std::wstring::npos) pos = f.find(L"%ls");
        if (pos != std::wstring::npos) {
            return f.substr(0, pos) + (a ? a : L"") + f.substr(pos + 2);
        }
        return f;
    }
};

// CArray minimal shim using std::vector
template <typename T>
class CArray {
public:
    void Add(const T& v) { data_.push_back(v); }
    void RemoveAll() { data_.clear(); }
    int GetSize() const { return static_cast<int>(data_.size()); }
    int GetCount() const { return GetSize(); }
    void InsertAt(int index, const T& v) {
        if (index < 0) index = 0;
        size_t idx = static_cast<size_t>(index);
        if (idx > data_.size()) idx = data_.size();
        data_.insert(data_.begin() + idx, v);
    }
    T& operator[](int i) { return data_[static_cast<size_t>(i)]; }
    const T& operator[](int i) const { return data_[static_cast<size_t>(i)]; }
private:
    std::vector<T> data_;
};

// Simple MFC-like CList for pointer types
typedef size_t POSITION;
template <typename T>
class CList {
public:
    void AddTail(T v) { data_.push_back(v); }
    POSITION GetHeadPosition() const { return data_.empty() ? 0u : 1u; }
    T GetNext(POSITION& pos) {
        if (pos == 0) return T();
        size_t idx = pos - 1;
        T val = data_[idx];
        if (idx + 1 < data_.size()) pos = static_cast<POSITION>(idx + 2); else pos = 0;
        return val;
    }
private:
    std::vector<T> data_;
};

// CFile minimal shim for read-only used in code
class CFile {
public:
    enum OpenFlags { modeRead = 0x0000 };
    CFile() : f_(nullptr), length_(0) {}
    ~CFile() { if (f_) std::fclose(f_); }

    bool Open(const CString& path, unsigned int /*flags*/) {
        std::string p8 = narrow(path.std());
        f_ = std::fopen(p8.c_str(), "rb");
        if (!f_) return false;
        std::fseek(f_, 0, SEEK_END);
        length_ = std::ftell(f_);
        std::fseek(f_, 0, SEEK_SET);
        return true;
    }

    LONGLONG GetLength() const { return length_; }

    size_t Read(void* buf, unsigned int len) {
        if (!f_) return 0;
        return std::fread(buf, 1, len, f_);
    }

    size_t Write(const void* buf, unsigned int len) {
        if (!f_) return 0;
        return std::fwrite(buf, 1, len, f_);
    }

    void Close() { if (f_) { std::fclose(f_); f_ = nullptr; } }

private:
    static std::string narrow(const std::wstring& ws) {
        std::string out;
        out.reserve(ws.size());
        for (wchar_t c : ws) out.push_back((char)(c & 0xFF));
        return out;
    }

    std::FILE* f_;
    LONGLONG length_;
};

// Stubs
inline bool AfxWinInit(void*, void*, const wchar_t*, int) { return true; }
inline void* GetModuleHandle(void*) { return nullptr; }
inline unsigned long GetCurrentDirectoryA(unsigned long, char*) { return 0; }
inline const wchar_t* GetCommandLine() { return L""; }
inline unsigned long GetModuleFileName(void*, wchar_t* buffer, unsigned long size) {
    if (buffer && size > 0) buffer[0] = L'\0';
    return 0;
}

inline void OutputDebugString(const wchar_t* s) {
    if (s) std::fwprintf(stderr, L"%ls", s);
}

#define _T(x) L##x
#define TEXT(x) L##x

#ifndef memcpy_s
#define memcpy_s(dest, destsz, src, count) std::memcpy((dest), (src), (count))
#endif

// UTF-8 helpers and CT2CA stub
#define CP_UTF8 65001
inline std::wstring compat_utf8_to_wstring(const char* s) {
    if (!s) return std::wstring();
    std::wstring out; out.reserve(std::strlen(s));
    for (const unsigned char* p = (const unsigned char*)s; *p; ++p) out.push_back((wchar_t)*p);
    return out;
}
class CT2CA {
public:
    CT2CA(const CString& s, int /*cp*/) { buf_ = narrow(s.std()); }
    operator const char*() const { return buf_.c_str(); }
private:
    static std::string narrow(const std::wstring& ws) {
        std::string out; out.reserve(ws.size());
        for (wchar_t c : ws) out.push_back((char)(c & 0xFF));
        return out;
    }
    std::string buf_;
};
// CA2W replacement
inline std::wstring CA2W(const char* s, int /*cp*/) { return compat_utf8_to_wstring(s); }
namespace ATL { inline std::wstring CA2W(const char* s, int cp) { return ::CA2W(s, cp); } }

// W2A stub for TRACE uses
class W2A {
public:
    W2A(const wchar_t* ws) { buf_ = narrow(ws ? std::wstring(ws) : std::wstring()); }
    operator const char*() const { return buf_.c_str(); }
private:
    static std::string narrow(const std::wstring& ws) {
        std::string out; out.reserve(ws.size());
        for (wchar_t c : ws) out.push_back((char)(c & 0xFF));
        return out;
    }
    std::string buf_;
};

#ifndef TRACE
#define TRACE(...) do { fprintf(stderr, __VA_ARGS__); fputc('\n', stderr); } while(0)
#endif
// no-op macro
#define USES_CONVERSION

#endif // _WIN32


