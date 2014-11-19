#include "Common.h"
#include "FileUtil2.h"
#include "FileUtil.h"

namespace path {

// http://msdn.microsoft.com/en-us/library/windows/desktop/bb773569(v=vs.85).aspx
// TODO: on win8 use PathCchCanonicalize or PathCchCanonicalizeEx
void NormalizeInPlace(WCHAR* src, size_t srcCchSize) {
    // TODO: make it work even if srcCchSize is < MAX_PATH
    CrashIf(srcCchSize < MAX_PATH);
    WCHAR buf[MAX_PATH];
    BOOL ok = PathCanonicalizeW(buf, src);
    if (!ok) {
        return;
    }
    memcpy(src, buf, sizeof(buf));
}

void Join(std::string& sInOut, const char* s, size_t sLen) {
    char c = str::LastChar(sInOut);
    if (!IsSep(c)) {
        sInOut.append(1, '\\');
    }
    if (sLen == 0) {
        sLen = str::Len(s);
    }
    if (IsSep(*s)) {
        ++s;
        --sLen;
    }
    sInOut.append(s, sLen);
}

void Join(std::string& sInOut, const std::string& s2) {
    return Join(sInOut, s2.c_str(), s2.size());
}

// consider using PathRemoveFileSpec()
// http://msdn.microsoft.com/en-us/library/windows/desktop/bb773748(v=vs.85).aspx
std::string GetDir(const std::string& path) {
    std::string res(path);
    if (path.empty()) {
        return res;
    }
    const char* start = res.c_str();
    const char* end = start + res.size() - 1;
    while (end >= start) {
        char c = *end;
        if (IsSep(c)) {
            size_t idx = end - start;
            res.erase(idx, res.size());
            return res;
        }
        --end;
    }
    return res;
}

} // namespace path

namespace file {

bool Exists(const char* path) {
    if (str::IsEmpty(path)) {
        return false;
    }
    AutoUtf8ToWstr pathW(path);

    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    BOOL res = GetFileAttributesEx(pathW.Get(), GetFileExInfoStandard, &fileInfo);
    if (0 == res) {
        return false;
    }

    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        return false;
    }
    return true;
}

bool Copy(const char *dst, const char *src) {
    AutoUtf8ToWstr dstW(dst);
    AutoUtf8ToWstr srcW(src);
    BOOL failIfExists = TRUE;
    BOOL res = CopyFileW(srcW.Get(), dstW.Get(), failIfExists);
    return res != 0;
}

// Return true if the file wasn't there or was successfully deleted
bool Delete(const char *path) {
    AutoUtf8ToWstr pathW(path);
    BOOL ok = DeleteFile(pathW.Get());
    return ok || GetLastError() == ERROR_FILE_NOT_FOUND;
}

} // namespace file

namespace dir {

bool Exists(const char* dir) {
    if (str::IsEmpty(dir)) {
        return false;
    }
    AutoUtf8ToWstr dirW(dir);

    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    BOOL res = GetFileAttributesEx(dirW, GetFileExInfoStandard, &fileInfo);
    if (0 == res) {
        return false;
    }

    if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
        return true;
    }
    return false;
}

// Return true if a directory already exists or has been successfully created
bool Create(const std::string& dir) {
    AutoUtf8ToWstr dirW(dir);
    BOOL ok = CreateDirectory(dirW.Get(), NULL);
    if (ok)
        return true;
    return ERROR_ALREADY_EXISTS == GetLastError();
}

// creates a directory and all its parent directories that don't exist yet
bool CreateAll(const std::string& dir) {
    std::string parent(path::GetDir(dir));
    if (parent != dir && !Exists(parent.c_str())) {
        CreateAll(parent);
    }
    return Create(dir);
}

bool CreateForFile(const std::string& path) {
    auto dir(path::GetDir(path));
    return dir::CreateAll(dir);
}

} // namespace dir
