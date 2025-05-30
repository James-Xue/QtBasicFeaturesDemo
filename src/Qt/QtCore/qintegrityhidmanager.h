// Copyright (C) 2015 Green Hills Software


#ifndef QINTEGRITYHIDMANAGER_P_H
#define QINTEGRITYHIDMANAGER_P_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include <QtCore/QThread>

QT_BEGIN_NAMESPACE

class HIDDriverHandler;

class QIntegrityHIDManager : public QThread
{
    Q_OBJECT
public:
    QIntegrityHIDManager(const QString &key, const QString &specification, QObject *parent = nullptr);
    ~QIntegrityHIDManager();

    void run(void) override;
private:
    void open_devices(void);

    QString m_spec;
    QList<HIDDriverHandler *> m_drivers;

};

QT_END_NAMESPACE

#endif // QINTEGRITYHIDMANAGER_P_H
