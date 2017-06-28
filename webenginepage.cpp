#include "webenginepage.h"

WebEnginePage::WebEnginePage(QObject *parent = Q_NULLPTR) :
    QWebEnginePage(parent)
{}

WebEnginePage::WebEnginePage(QWebEngineProfile *profile, QObject *parent) :
    QWebEnginePage(profile, parent)
{}

bool WebEnginePage::certificateError(const QWebEngineCertificateError &certificateError)
{
    Q_UNUSED(certificateError);

    qDebug() << certificateError.errorDescription();
    qDebug() << certificateError.url();

    // Unconditionally ignore error
    return true;
}
