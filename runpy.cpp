#include "runpy.h"

#include <QDebug>
#include <QFileInfo>
#include <QDir>

RunPy::RunPy()
{
    m_process = new QProcess();

    connect(m_process, SIGNAL(started()), this, SLOT(slotStart()));
    connect(m_process, SIGNAL(readyReadStandardOutput()), this,
            SLOT(slotOutput()));
    connect(m_process, SIGNAL(readyReadStandardError()), this,
            SLOT(slotError()));
    connect(m_process, SIGNAL(finished(int,QProcess::ExitStatus)), this,
            SLOT(slotFinished(int, QProcess::ExitStatus)));
}

RunPy::~RunPy()
{
    delete m_process;
}

void RunPy::processPy(const QString &pyName, const QStringList &argList)
{
    //Judge whether the python script file 'pyName' exist
    QFileInfo fInfo(pyName);
    if(!fInfo.exists() || !fInfo.isFile())
        return;

    QString workPath = fInfo.absolutePath();
    QString fileName = fInfo.fileName();
    /** NOTE:
     *  With this setting, the fileName imported to QProcess::start() as one of
     *  arguments can be the pure file name without directory.
     */
    m_process->setWorkingDirectory(workPath);

    /** NOTE:
     *  The following setting about process environment is used to attempt to
     *  run 'python' instead of 'python3.6' in QProcess.start(), while it seems
     *  not working.
     */
//    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
//    env.insert("PYTHONHOME", "/usr/local/anaconda3/bin");
//    env.insert("PYTHONLIB", "/usr/local/anaconda3/lib");
//    m_process->setProcessEnvironment(env);

    //QC: Display some configuration information
    qDebug() << "Current Path: " << QDir::currentPath();
    qDebug() << "Process Environment: " << m_process->processEnvironment().toStringList();
    qDebug() << "Working Directory: " << m_process->workingDirectory();

    QStringList cmdArgs = QStringList() << fileName << argList;
    qDebug() << "PyCommand: " << cmdArgs.join(" ");

    /** NOTE:
     *      Pay attention to 'program' parameter, for multiple python versions,
     *      it may induce some confusion.
     *      For Python in Linux OS, although python3.6 has been renamed as a
     *      'python' alias, if 'python' is passed into the start() function,
     *      python2.6 is executed.
     */
    m_process->start("python3.6", cmdArgs);
}

void RunPy::slotStart()
{
    qDebug() << "Process started successfully!";
}

void RunPy::slotOutput()
{
    QByteArray output = m_process->readAllStandardOutput();
    qDebug() << QString::fromUtf8(output.data());
}

void RunPy::slotOutputLine()
{
    //NOTE: the output information is in line-by-line form, but is outputted
    //      synchronously when python program ended.
    //The above phenomenon is due to Python print (solved by sys.stdout.flush()),
    //      not QProcess setting
    while(m_process->canReadLine()){
        qDebug() << QString::fromUtf8(m_process->readLine().data());
    }
}

void RunPy::slotError()
{
    QByteArray error = m_process->readAllStandardError();
    qDebug() << QString::fromUtf8(error.data());
}

void RunPy::slotFinished(const int &exitCode,
                         const QProcess::ExitStatus &exitStatus)
{
    qDebug() << "The process finished with exitCode as " << exitCode;

    QString msg;
    if(exitStatus==QProcess::NormalExit)
        msg = "The process exited normally!";
    else
        msg = "The process crashed!";
    qDebug() << msg;
}
