// QT
#include <QDebug>
#include <QUrl>

// Myself
#include "DataInput.h"
#include "CSVHelper.h"

namespace Bio
{
    DataInput::DataInput(QObject* const pParent /* = nullptr*/)
        : QObject(pParent)
    {
    }

    DataInput::~DataInput()
    {
    }

    // 辅助函数：去除 file:/// 前缀，返回本地文件路径
    static QString toLocalFilePath(const QString& path)
    {
        QUrl url(path);
        if (url.isLocalFile())
        {
            return url.toLocalFile();
        }
        return path;
    }

    void DataInput::ImportFile(const QString& sPath) const
    {
        QString localPath = toLocalFilePath(sPath);
        qDebug() << u8"导入文件路径:" << localPath;

        // 调用 CSVHelper 读取数据到 std::vector<std::string>
        CSVHelper csvHelper;
        std::vector<std::string> csvData;
        bool ok = csvHelper.ReadCSV(localPath, csvData);

        if (ok)
        {
            qDebug() << u8"CSV 文件读取成功，行数:" << static_cast<int>(csvData.size());
            // 你可以在这里处理 csvData
        }
        else
        {
            qDebug() << u8"CSV 文件读取失败";
        }
    }

    bool DataInput::loadData(const QString& /*filePath*/)
    {
        return false;
    }

    QVector<double> DataInput::getSignalData(void) const
    {
        return {};
    }

    QString DataInput::getLastError(void) const
    {
        return {};
    }
} // namespace Bio
