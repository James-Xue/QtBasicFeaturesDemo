// Qt
#include <QFile>
#include <QDir>
#include <QString>
#include <QMessageBox>

//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>

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

    bool CSVHelper::ReadCSVFromFloder(const std::string &sDirFullPath) const
    {
        return ReadCSVFromFloder(QString::fromStdString(sDirFullPath));
    }

    bool CSVHelper::ReadCSVFromFloder(const QString &sDirFullPath) const
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
            std::vector<std::string> vctString;
            [[maybe_unused]] const bool bRet = ReadCSV(sOneFilePath, vctString);
            if (false == bRet)
            {
                QMessageBox::information(nullptr,
                    QString::fromUtf8(u8"Tips"),
                    QString::fromUtf8(u8"Invalid Data."));
            }
        }

        return true;
    }

    bool ConvertStringsToInts(const std::vector<std::string> &vctString, std::vector<int> &vctInt)
    {
        vctInt.clear();
        vctInt.reserve(vctString.size());

        for (const auto &str : vctString)
        {
            try
            {
                vctInt.push_back(std::stoi(str));
            }
            catch ([[maybe_unused]] const std::invalid_argument &e) 
            {
                // 处理无法转换的字符串
                //throw std::invalid_argument("Non-integer value found: " + str);
                return false;
            }
            catch ([[maybe_unused]] const std::out_of_range &e)
            {
                // 处理超出 int 范围的值
                //throw std::out_of_range("Value out of int range: " + str);
                return false;
            }
        }

        return true;
    }

    bool CSVHelper::ReadCSV(const std::string &sFileFullPath, std::vector<int> &vctInt) const
    {
        std::vector<std::string> vctString;
        const bool bRet = ReadCSV(sFileFullPath, vctString);
        if (false == bRet)
        {
            return false;
        }

        return ConvertStringsToInts(vctString, vctInt);
    }

    bool CSVHelper::ReadCSV(const std::string &sFileFullPath, std::vector<std::string> &vctString) const
    {
        const QString qstrFileFullPath = QString::fromStdString(sFileFullPath);
        return ReadCSV(qstrFileFullPath, vctString);
    }

    bool CSVHelper::ReadCSV(const QString &sFileFullPath, std::vector<std::string> &vctString) const
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
            vctString.push_back(line.toStdString());
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
