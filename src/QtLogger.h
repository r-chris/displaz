// Copyright 2015, Christopher J. Foster and the other displaz contributors.
// Use of this code is governed by the BSD-style license found in LICENSE.txt

#ifndef QT_LOGGER_H_INCLUDED
#define QT_LOGGER_H_INCLUDED

#include <QObject>
#include <QString>

#include "logger.h"
#include "qtutil.h"

/// Logger class which logs output to qt signals
class QtLogger : public QObject, public Logger
{
    Q_OBJECT
    public:
        QtLogger(QObject* parent = 0) : QObject(parent) {}

        virtual void log(LogLevel level, const std::string& msg)
        {
            emit logMessage(level, QString::fromUtf8(msg.c_str()));
        }

    signals:
        /// Signal emitted every time a log message comes in
        void logMessage(int logLevel, QString msg);

        /// Signal emitted when processing progress has been made
        void progressPercent(int percent);

    protected:
        virtual void progressImpl(double progressFraction)
        {
            emit progressPercent(int(100*progressFraction));
        }
};


/// Global displaz logger instance
extern QtLogger g_logger;


#endif // QT_LOGGER_H_INCLUDED
