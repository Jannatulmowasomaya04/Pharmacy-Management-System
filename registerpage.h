#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMap> // Include for user map

class RegisterPage : public QWidget {
    Q_OBJECT
public:
    explicit RegisterPage(QMap<QString, QString>* users, QWidget *parent = nullptr);
    ~RegisterPage();

signals:
    void registrationSuccessful();
    void loginRequested();

private slots:
    void onRegisterButtonClicked();

private:
    QLineEdit *m_usernameLineEdit;
    QLineEdit *m_passwordLineEdit;
    QLineEdit *m_confirmPasswordLineEdit;
    QMap<QString, QString>* m_users; // Pointer to the shared user map
};
#endif // REGISTERPAGE_H
