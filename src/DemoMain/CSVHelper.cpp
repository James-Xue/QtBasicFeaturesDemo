// Qt
#define QT_NO_VERSION_TAGGING
#include <QtCore/qchar.h>
#include <QtCore/qstring.h>

// Self
#include "CSVHelper.h"


namespace Demo
{
    CSVHelper::CSVHelper()
    {
        QChar chTest;
        QString sTest;
    }

    CSVHelper::~CSVHelper()
    {
    }

    bool CSVHelper::ReadCSV(const std::string &/*sFileFullPath*/)
    {
        //// 1. Check if the file exists
        //QFile oneQFile(QString::fromStdString(sFileFullPath));
        //if (false == oneQFile.exists())
        //{
        //    return false;
        //}

        //// 2. Open the file
        ////OpenMode mode = QIODevice::ReadOnly | QIODevice::Text;
        //if (false == oneQFile.open(QIODevice::ReadOnly | QIODevice::Text))
        //{
        //    return false;
        //}

        //// 3. Read the file line by line
        //while (false == oneQFile.atEnd())
        //{
        //    QByteArray line = oneQFile.readLine();
        //    m_vctString.push_back(line.toStdString());
        //}

        //// 4. Close the file
        //oneQFile.close();
        return true;
    }

} // namespace Demo
