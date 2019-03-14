#ifndef RUNPY_H
#define RUNPY_H

#include <QThread>
#include <QString>
#include <QProcess>

class RunPy : public QThread
{
    Q_OBJECT

public:
    RunPy();
    ~RunPy();

    void processPy(const QString &pyName, const QStringList &argList=QStringList());

private slots:
    void slotStart();
    /**
     * @brief slotOutput:   Print stdout of python script executed by QProcess
     * @note    Response ot readyReadStandardOutput signal, the performance of
     *          slotOuput() is same as slotOutputLine();
     */
    void slotOutput();
    void slotOutputLine();
    /**
     * @brief slotError:    Print standard error information raised in Python
     *                      script
     * @note    This is important for supervising exceptions in Python script
     */
    void slotError();
    /**
     * @brief slotFinished: Print exit status of the process when finished.
     * @param exitCode
     * @param exitStatus
     */
    void slotFinished(const int &exitCode, const QProcess::ExitStatus &exitStatus);

private:
    QProcess *m_process;
};

#endif // RUNPY_H
