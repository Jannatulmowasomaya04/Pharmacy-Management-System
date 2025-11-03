#include "landingpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

LandingPage::LandingPage(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("LandingPage");

    auto titleLabel = new QLabel("PharmaGo", this);
    titleLabel->setObjectName("landingTitleLabel");

    auto descriptionLabel = new QLabel("Your trusted source for pharmaceutical needs. "
                                       "Browse our extensive catalog or log in to manage your purchases.", this);
    descriptionLabel->setObjectName("landingDescriptionLabel");
    descriptionLabel->setWordWrap(true);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setMaximumWidth(550); // Give it a generous width

    auto browseButton = new QPushButton("Browse Products as Guest", this);
    auto loginButton = new QPushButton("Login / Register", this);

    // --- Layout ---
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addSpacing(10);

    QHBoxLayout *descriptionLayout = new QHBoxLayout();
    descriptionLayout->addStretch();
    descriptionLayout->addWidget(descriptionLabel);
    descriptionLayout->addStretch();
    mainLayout->addLayout(descriptionLayout);

    mainLayout->addSpacing(30);
    mainLayout->addWidget(browseButton, 0, Qt::AlignCenter);
    mainLayout->addWidget(loginButton, 0, Qt::AlignCenter);
    mainLayout->addStretch();

    // Constrain the width of the central content
    browseButton->setFixedWidth(250);
    loginButton->setFixedWidth(250);

    // --- Connections ---
    connect(browseButton, &QPushButton::clicked, this, &LandingPage::browseAsGuestClicked);
    connect(loginButton, &QPushButton::clicked, this, &LandingPage::loginRegisterClicked);
}

LandingPage::~LandingPage() {}
