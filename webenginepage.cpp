#include <QDebug>
#include "webenginepage.h"
#include <QWebEngineHistory>

WebEnginePage::WebEnginePage(QWebEngineProfile *profile, QObject *parent) :
    QWebEnginePage(profile, parent)
{}

bool WebEnginePage::certificateError(const QWebEngineCertificateError &certificateError)
{
    Q_UNUSED(certificateError);

    auto url = certificateError.url();

    qDebug() << certificateError.errorDescription();
    qDebug() << url;

    // Since Cert. Errors trigger only once per page and session,
    // we need to store it, so we can fire it again, when browsing
    // history using next/prev!
    m_urlWithCertError.insert(url);

    emit onCertificateInvalid(url);

    // Unconditionally ignore error
    return true;
}

void WebEnginePage::next(void)
{
    if (!history()->canGoForward())
        return;

    auto nextUrl = history()->forwardItem().url();

    triggerAction(QWebEnginePage::Forward);

    if (m_urlWithCertError.contains(nextUrl))
        emit onCertificateInvalid(nextUrl);
}


void WebEnginePage::prev(void)
{
    if (!history()->canGoBack())
        return;

    auto prevUrl = history()->backItem().url();

    triggerAction(QWebEnginePage::Back);

    if (m_urlWithCertError.contains(prevUrl))
        emit onCertificateInvalid(prevUrl);
}
