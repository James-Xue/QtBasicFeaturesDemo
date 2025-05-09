// Copyright (C) 2011 - 2012 Research In Motion


#ifndef VIRTUALKEYBOARDPPS_H
#define VIRTUALKEYBOARDPPS_H

#include "qqnxabstractvirtualkeyboard.h"
#include <QtCore/QLoggingCategory>

#include <sys/pps.h>

QT_BEGIN_NAMESPACE

Q_DECLARE_LOGGING_CATEGORY(lcQpaQnxVirtualKeyboard);

class QSocketNotifier;

class QQnxVirtualKeyboardPps : public QQnxAbstractVirtualKeyboard
{
    Q_OBJECT
public:
    QQnxVirtualKeyboardPps();
    ~QQnxVirtualKeyboardPps();

    bool showKeyboard() override;
    bool hideKeyboard() override;

public Q_SLOTS:
    void start();

protected:
    void applyKeyboardOptions() override;

private Q_SLOTS:
    void ppsDataReady();

private:
    // Will be called internally if needed.
    bool connect();
    void close();
    bool queryPPSInfo();
    void handleKeyboardInfoMessage();

    const char* keyboardModeStr() const;
    const char* enterKeyTypeStr() const;

    bool prepareToSend();
    bool writeCurrentPPSEncoder();

    pps_encoder_t  *m_encoder;
    pps_decoder_t  *m_decoder;
    char           *m_buffer;
    int             m_fd;
    QSocketNotifier *m_readNotifier;

    // Path to keyboardManager in PPS.
    static const char *ms_PPSPath;
    static const size_t ms_bufferSize;
};

QT_END_NAMESPACE

#endif // VIRTUALKEYBOARDPPS_H
