#ifndef CWIZEVENTLOOP_H
#define CWIZEVENTLOOP_H

#include <QEventLoop>
#include <QNetworkReply>
#include <QTimer>

/**
 * NOTE: CWizAutoTimeOutEventLoop would delete network reply at destruct,
 * should not delete network reply again
 */

class CWizAutoTimeOutEventLoop : public QEventLoop
{
    Q_OBJECT
public:
    explicit CWizAutoTimeOutEventLoop(QNetworkReply* pReply, QObject *parent = 0);
    ~CWizAutoTimeOutEventLoop();
    void setTimeoutWaitSeconds(int seconds);

public:
    QNetworkReply::NetworkError error() const { return m_error; }
    QString errorString() const { return m_errorString; }
    QByteArray result() const { return m_result; }
    bool timeOut() const { return m_timeOut; }
    QNetworkReply* networkReply() const;

    int exec(ProcessEventsFlags flags = AllEvents);

public Q_SLOTS:
    void on_replyFinished();
    void on_replyError(QNetworkReply::NetworkError);
    void on_timeOut();
    void on_downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void on_uploadProgress(qint64 bytesSent, qint64 bytesTotal);


protected:
    virtual void doFinished(QNetworkReply* reply);
    virtual void doError(QNetworkReply::NetworkError error);

    QByteArray m_result;
    QNetworkReply* m_reply;
    QNetworkReply::NetworkError m_error;
    QString m_errorString;
    bool m_timeOut;
    int m_timeOutSeconds;
    qint64 m_downloadBytes;
    qint64 m_lastDownloadBytes;
    qint64 m_uploadBytes;
    qint64 m_lastUploadBytes;
    QTimer m_timer;
};


class CWizXmlRpcEventLoop : public CWizAutoTimeOutEventLoop
{
    Q_OBJECT
public:
    explicit CWizXmlRpcEventLoop(QNetworkReply* pReply, QObject *parent = 0);

protected:
    virtual void doFinished(QNetworkReply* reply);
};

#endif // CWIZEVENTLOOP_H
