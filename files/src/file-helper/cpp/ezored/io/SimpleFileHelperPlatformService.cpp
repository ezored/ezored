#include "SimpleFileHelperPlatformService.hpp"

#include "Poco/DirectoryIterator.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/Path.h"
#include "Poco/StreamCopier.h"
#include "Poco/URI.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace ezored
{
namespace io
{

bool SimpleFileHelperPlatformService::createFile(const std::string &path)
{
    try
    {
        Poco::File f(path);
        return f.createFile();
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::createFileWithStringContent(const std::string &path, const std::string &content)
{
    try
    {
        Poco::FileOutputStream stream(path, std::ios::out | std::ios::binary | std::ios::trunc);
        stream << content;
        stream.close();

        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::createFileWithBinaryContent(const std::string &path, const std::vector<uint8_t> &content)
{
    try
    {
        Poco::FileOutputStream stream(path, std::ios::in | std::ios::binary);

        for (auto &data : content)
        {
            stream << data;
        }

        stream.close();

        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::createDir(const std::string &path)
{
    try
    {
        Poco::File f(path);
        return f.createDirectory();
    }
    catch (const std::exception &)
    {
        return false;
    }
}

std::vector<std::string> SimpleFileHelperPlatformService::listFiles(const std::string &path)
{
    try
    {
        Poco::DirectoryIterator d(path);
        std::vector<std::string> files;

        d->list(files);

        return files;
    }
    catch (const std::exception &)
    {
        return {};
    }
}

std::string SimpleFileHelperPlatformService::getExtension(const std::string &path)
{
    try
    {
        Poco::Path p(path);
        return p.getExtension();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::string SimpleFileHelperPlatformService::getFilename(const std::string &path)
{
    try
    {
        Poco::Path p(path);
        return p.getFileName();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::string SimpleFileHelperPlatformService::getBasename(const std::string &path)
{
    try
    {
        Poco::Path p(path);
        return p.getBaseName();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::string SimpleFileHelperPlatformService::getFilenameFromUrl(const std::string &url)
{
    try
    {
        Poco::URI u(url);
        return Poco::Path(u.getPath()).getFileName();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::string SimpleFileHelperPlatformService::getBasenameFromUrl(const std::string &url)
{
    try
    {
        auto filename = getFilenameFromUrl(url);
        return Poco::Path(filename).getBaseName();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

bool SimpleFileHelperPlatformService::removeFile(const std::string &path)
{
    try
    {
        Poco::File f(path);
        f.remove(false);
        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::removeDir(const std::string &path)
{
    try
    {
        Poco::File f(path);
        f.remove(true);
        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::isDir(const std::string &path)
{
    try
    {
        Poco::File f(path);
        return f.isDirectory();
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::isFile(const std::string &path)
{
    try
    {
        Poco::File f(path);
        return f.isFile();
    }
    catch (const std::exception &)
    {
        return false;
    }
}

int64_t SimpleFileHelperPlatformService::getFileSize(const std::string &path)
{
    try
    {
        Poco::File f(path);
        return static_cast<int64_t>(f.getSize());
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::copyFile(const std::string &from, const std::string &to)
{
    try
    {
        Poco::File f(from);
        f.copyTo(to);
        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

bool SimpleFileHelperPlatformService::moveFile(const std::string &from, const std::string &to)
{
    try
    {
        Poco::File f(from);
        f.moveTo(to);
        return true;
    }
    catch (const std::exception &)
    {
        return false;
    }
}

std::string SimpleFileHelperPlatformService::join(const std::string &first, const std::string &second)
{
    try
    {
        Poco::Path p(first, second);
        return p.toString();
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::string SimpleFileHelperPlatformService::getFileContentAsString(const std::string &path)
{
    try
    {
        std::string data;
        Poco::FileStream stream(path);
        Poco::StreamCopier::copyToString(stream, data);

        return data;
    }
    catch (const std::exception &)
    {
        return "";
    }
}

std::vector<uint8_t> SimpleFileHelperPlatformService::getFileContentAsBinary(const std::string &path)
{
    try
    {
        std::ifstream stream(path, std::ios::in | std::ios::binary);
        std::vector<uint8_t> data((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
        return data;
    }
    catch (const std::exception &)
    {
        return {};
    }
}

std::string SimpleFileHelperPlatformService::getHomeDir()
{
    return Poco::Path::home();
}

} // namespace io
} // namespace ezored
