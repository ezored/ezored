#include "FileHelperImpl.hpp"

namespace ezored
{
namespace io
{

std::shared_ptr<FileHelperImpl> FileHelperImpl::instance = nullptr;

FileHelperImpl::FileHelperImpl()
{
    ps = nullptr;
}

std::shared_ptr<FileHelper> FileHelper::shared()
{
    return FileHelperImpl::internalSharedInstance();
}

std::shared_ptr<FileHelperImpl> FileHelperImpl::internalSharedInstance()
{
    if (instance == nullptr)
    {
        instance = std::make_shared<FileHelperImpl>();
    }

    return instance;
}

void FileHelperImpl::setPlatformService(const std::shared_ptr<FileHelperPlatformService> &ps)
{
    this->ps = ps;
}

std::shared_ptr<FileHelperPlatformService> FileHelperImpl::getPlatformService()
{
    return ps;
}

bool FileHelperImpl::hasPlatformService()
{
    return (ps != nullptr);
}

bool FileHelper::createFile(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->createFile(path);
    }

    return false;
}

bool FileHelper::createFileWithStringContent(const std::string &path, const std::string &content)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->createFileWithStringContent(path, content);
    }

    return false;
}

bool FileHelper::createFileWithBinaryContent(const std::string &path, const std::vector<uint8_t> &content)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->createFileWithBinaryContent(path, content);
    }

    return false;
}

bool FileHelper::createDir(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->createDir(path);
    }

    return false;
}

std::vector<std::string> FileHelper::listFiles(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->listFiles(path);
    }

    return {};
}

std::string FileHelper::getExtension(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getExtension(path);
    }

    return "";
}

std::string FileHelper::getFilename(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getFilename(path);
    }

    return "";
}

std::string FileHelper::getBasename(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getBasename(path);
    }

    return "";
}

std::string FileHelper::getFilenameFromUrl(const std::string &url)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getFilenameFromUrl(url);
    }

    return "";
}

std::string FileHelper::getBasenameFromUrl(const std::string &url)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getBasenameFromUrl(url);
    }

    return "";
}

bool FileHelper::removeFile(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->removeFile(path);
    }

    return false;
}

bool FileHelper::removeDir(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->removeDir(path);
    }

    return false;
}

bool FileHelper::isDir(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->isDir(path);
    }

    return false;
}

bool FileHelper::isFile(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->isFile(path);
    }

    return false;
}

int64_t FileHelper::getFileSize(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getFileSize(path);
    }

    return 0;
}

bool FileHelper::copyFile(const std::string &from, const std::string &to)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->copyFile(from, to);
    }

    return false;
}

bool FileHelper::moveFile(const std::string &from, const std::string &to)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->moveFile(from, to);
    }

    return false;
}

std::string FileHelper::join(const std::string &first, const std::string &second)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->join(first, second);
    }

    return "";
}

std::string FileHelper::getFileContentAsString(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getFileContentAsString(path);
    }

    return "";
}

std::vector<uint8_t> FileHelper::getFileContentAsBinary(const std::string &path)
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getFileContentAsBinary(path);
    }

    return {};
}

std::string FileHelper::getHomeDir()
{
    if (FileHelper::shared()->hasPlatformService())
    {
        return FileHelper::shared()->getPlatformService()->getHomeDir();
    }

    return "";
}

} // namespace io
} // namespace ezored
