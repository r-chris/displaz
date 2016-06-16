//------------------------------------------------------------------------------
/// Viewer widget for log messages.
///
/// This is intended to work together with the Logger class as a frontend which
/// does to the actual log message formatting.  The logger frontend is
/// threadsafe, but LogViewer must run on the GUI thread.

#ifndef LOG_VIEWER_H_INCLUDED
#define LOG_VIEWER_H_INCLUDED

#include <QPlainTextEdit>

class QtLogger;

class LogViewer : public QPlainTextEdit
{
    Q_OBJECT
    public:
        LogViewer(QWidget* parent = 0);

    public slots:
        /// Connect given logger to the viewer.
        ///
        /// Note that for thread safety this must be a queued connection, hence
        /// the special purpose method here.
        void connectLogger(QtLogger* logger);

        /// Append plain text message to the running log
        void appendLogMessage(int logLevel, QString msg);
};

#endif // LOG_VIEWER_H_INCLUDED
