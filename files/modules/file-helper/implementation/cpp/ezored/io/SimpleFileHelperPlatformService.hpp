#pragma once

#include "ezored/io/FileHelperPlatformService.hpp"

namespace ezored
{
namespace io
{

class SimpleFileHelperPlatformService : public FileHelperPlatformService
{
public:
    virtual ~SimpleFileHelperPlatformService() override {}

    bool createFile(const std::string &path) override;

    bool createFileWithStringContent(const std::string &path, const std::string &content) override;

    bool createFileWithBinaryContent(const std::string &path, const std::vector<uint8_t> &content) override;

    bool createDir(const std::string &path) override;

    std::vector<std::string> listFiles(const std::string &path) override;

    std::string getExtension(const std::string &path) override;

    std::string getFilename(const std::string &path) override;

    std::string getBasename(const std::string &path) override;

    std::string getFilenameFromUrl(const std::string &url) override;

    std::string getBasenameFromUrl(const std::string &url) override;

    bool removeFile(const std::string &path) override;

    bool removeDir(const std::string &path) override;

    bool isDir(const std::string &path) override;

    bool isFile(const std::string &path) override;

    int64_t getFileSize(const std::string &path) override;

    bool copyFile(const std::string &from, const std::string &to) override;

    bool moveFile(const std::string &from, const std::string &to) override;

    std::string join(const std::string &first, const std::string &second) override;

    std::string getFileContentAsString(const std::string &path) override;

    std::vector<uint8_t> getFileContentAsBinary(const std::string &path) override;

    std::string getHomeDir() override;
};

} // namespace io
} // namespace ezored
