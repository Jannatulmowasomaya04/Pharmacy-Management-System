#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMap>

class LoginPage : public QWidget {
    Q_OBJECT
public:
    explicit LoginPage(QMap<QString, QString>* users, QWidget *parent = nullptr);
    ~LoginPage();

signals:
    void loginSuccessful(const QString& username);
    void registerRequested();
    void backToLandingClicked();

private slots:
    void onLoginButtonClicked();

private:
    QLineEdit *m_usernameLineEdit;
    QLineEdit *m_passwordLineEdit;
    QMap<QString, QString>* m_users;
};
#endif // LOGINPAGE_H
