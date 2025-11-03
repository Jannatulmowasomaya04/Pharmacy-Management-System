#include "loginpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QDebug>

LoginPage::LoginPage(QMap<QString, QString>* users, QWidget *parent)
    : QWidget(parent), m_users(users)
{
    this->setObjectName("LoginPage");
    QWidget *formContainer = new QWidget(this);
    formContainer->setObjectName("formContainer");
    formContainer->setMaximumWidth(1050);

    auto titleLabel = new QLabel("User Login", formContainer);
    titleLabel->setObjectName("titleLabel");

    m_usernameLineEdit = new QLineEdit(formContainer);
    m_usernameLineEdit->setPlaceholderText("Username");
    m_passwordLineEdit = new QLineEdit(formContainer);
    m_passwordLineEdit->setPlaceholderText("Password");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);

    auto loginButton = new QPushButton("Login", formContainer);
    auto registerButtonLink = new QPushButton("Don't have an account? Register", formContainer);
    registerButtonLink->setObjectName("linkButton");
    registerButtonLink->setCursor(Qt::PointingHandCursor);

    auto backButtonLink = new QPushButton("« Back to Welcome Page", formContainer);
    backButtonLink->setObjectName("linkButton");
    backButtonLink->setCursor(Qt::PointingHandCursor);

    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    QFormLayout *inputLayout = new QFormLayout();
    inputLayout->setSpacing(10);
    inputLayout->addRow("Username:", m_usernameLineEdit);
    inputLayout->addRow("Password:", m_passwordLineEdit);

    formLayout->addWidget(backButtonLink, 0, Qt::AlignLeft);
    formLayout->addSpacing(15);
    formLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    formLayout->addLayout(inputLayout);
    formLayout->addSpacing(15);
    formLayout->addWidget(loginButton);
    formLayout->addSpacing(10);
    formLayout->addWidget(registerButtonLink, 0, Qt::AlignCenter);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(formContainer);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    connect(loginButton, &QPushButton::clicked, this, &LoginPage::onLoginButtonClicked);
    connect(registerButtonLink, &QPushButton::clicked, this, [this]() { emit registerRequested(); });
    connect(backButtonLink, &QPushButton::clicked, this, [this]() { emit backToLandingClicked(); });
}

LoginPage::~LoginPage() {}

void LoginPage::onLoginButtonClicked()
{
    const QString username = m_usernameLineEdit->text();
    const QString password = m_passwordLineEdit->text();

    if (m_users->contains(username) && (*m_users)[username] == password) {
        emit loginSuccessful(username);
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password.");
    }
}
