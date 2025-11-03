#ifndef LANDINGPAGE_H
#define LANDINGPAGE_H

#include <QWidget>

class LandingPage : public QWidget
{
    Q_OBJECT
public:
    explicit LandingPage(QWidget *parent = nullptr);
    ~LandingPage();

signals:
    void browseAsGuestClicked();
    void loginRegisterClicked();
};

#endif // LANDINGPAGE_H
