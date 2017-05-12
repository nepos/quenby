#ifndef WEBENGINEPAGE_H
#define WEBENGINEPAGE_H

#include <QWebEnginePage>

class WebEnginePage : public QWebEnginePage
{
public:
	explicit WebEnginePage(QObject *parent);
	WebEnginePage(QWebEngineProfile *profile, QObject *parent = Q_NULLPTR);

protected:
	virtual bool certificateError(const QWebEngineCertificateError &certificateError);

};

#endif // WEBENGINEPAGE_H
