// Qt
#include <QFile>
#include <QDir>
#include <QString>
#include <QMessageBox>

// Self
#include "CSVHelper.h"


namespace Demo
{
    CSVHelper::CSVHelper()
    {
    }

    CSVHelper::~CSVHelper()
    {
    }

    bool CSVHelper::ReadCSVFromFloder(const std::string &sDirFullPath)
    {
        return ReadCSVFromFloder(QString::fromStdString(sDirFullPath));
    }

    bool CSVHelper::ReadCSVFromFloder(const QString& sDirFullPath)
    {
        // 1. Check if the folder exists
        QDir oneDir(sDirFullPath);
        if (false == oneDir.exists())
        {
            return false;
        }

        // 2. Set the name filters to only get .csv files
        QStringList listNameFilter;
        listNameFilter << QString::fromUtf8(u8"*.csv");
        oneDir.setNameFilters(listNameFilter);

        // 3. Get the list of .csv files in the folder
        QFileInfoList listFile = oneDir.entryInfoList();

        // 4. Iterate over the list of .csv files
        for (const QFileInfo &oneFileInfo : listFile)
        {
            // 1. Check if the file exists
            if (false == oneFileInfo.isFile())
            {
                continue;
            }

            // 2. Get the full path of the .csv file
            const QString sOneFilePath = oneFileInfo.absoluteFilePath();

            // 3. Call function A with the file path
            [[maybe_unused]] const bool bRet = ReadCSV(sOneFilePath);
            if (false == bRet)
            {
                QMessageBox::information(nullptr,
                    QString::fromUtf8(u8"Tips"),
                    QString::fromUtf8(u8"Invalid Data."));
            }
        }

        return true;
    }

    bool CSVHelper::ReadCSV(const std::string &sFileFullPath)
    {
        return ReadCSV(QString::fromStdString(sFileFullPath));
    }

    bool CSVHelper::ReadCSV(const QString &sFileFullPath)
    {
        // 1. Check if the file exists
        QFile oneQFile(sFileFullPath);
        if (false == oneQFile.exists())
        {
            return false;
        }

        // 2. Open the file
        if (false == oneQFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            return false;
        }

        // 3. Read the file line by line
        bool bBlank = false;
        while (false == oneQFile.atEnd())
        {
            const QByteArray line = oneQFile.readLine();
            m_vctString.push_back(line.toStdString());
            const QString str = line;
            if (true == str.trimmed().isEmpty())
            {
                bBlank = true;
                break;
            }
        }

        // 4. Close the file
        oneQFile.close();

        // 5. Return bool
        if (true == bBlank)
        {
            return false;
        }
        return true;
    }
} // namespace Demo
