#include "registerpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

RegisterPage::RegisterPage(QMap<QString, QString>* users, QWidget *parent)
    : QWidget(parent), m_users(users)
{
    this->setObjectName("RegisterPage");
    QWidget *formContainer = new QWidget(this);
    formContainer->setObjectName("formContainer");
    formContainer->setMaximumWidth(1050); // !!! CHANGED: Increased width !!!

    auto titleLabel = new QLabel("Create an Account", formContainer);
    titleLabel->setObjectName("titleLabel");

    m_usernameLineEdit = new QLineEdit(formContainer);
    m_usernameLineEdit->setPlaceholderText("Choose a username");
    m_passwordLineEdit = new QLineEdit(formContainer);
    m_passwordLineEdit->setPlaceholderText("Create a password");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_confirmPasswordLineEdit = new QLineEdit(formContainer);
    m_confirmPasswordLineEdit->setPlaceholderText("Confirm password");
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    auto registerButton = new QPushButton("Register", formContainer);
    registerButton->setObjectName("successButton");

    auto loginButtonLink = new QPushButton("Already have an account? Login", formContainer);
    loginButtonLink->setObjectName("linkButton");
    loginButtonLink->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    QFormLayout *inputLayout = new QFormLayout();
    inputLayout->addRow("Username:", m_usernameLineEdit);
    inputLayout->addRow("Password:", m_passwordLineEdit);
    inputLayout->addRow("Confirm Password:", m_confirmPasswordLineEdit);

    formLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    formLayout->addLayout(inputLayout);
    formLayout->addSpacing(10);
    formLayout->addWidget(registerButton);
    formLayout->addSpacing(10);
    formLayout->addWidget(loginButtonLink, 0, Qt::AlignCenter);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(formContainer);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    connect(registerButton, &QPushButton::clicked, this, &RegisterPage::onRegisterButtonClicked);
    connect(loginButtonLink, &QPushButton::clicked, this, [this]() {
        emit loginRequested();
    });
}

RegisterPage::~RegisterPage() {}

void RegisterPage::onRegisterButtonClicked()
{
    const QString username = m_usernameLineEdit->text().trimmed();
    const QString password = m_passwordLineEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Username and password cannot be empty.");
        return;
    }
    if (password != m_confirmPasswordLineEdit->text()) {
        QMessageBox::warning(this, "Input Error", "Passwords do not match.");
        return;
    }
    if (m_users->contains(username)) {
        QMessageBox::warning(this, "Registration Failed", "This username is already taken.");
        return;
    }

    m_users->insert(username, password);
    qDebug() << "New user registered:" << username << "| Total users:" << m_users->count();
    QMessageBox::information(this, "Success", "Registration successful! Please log in.");
    emit registrationSuccessful();
}
