#include "feedbackpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QMessageBox>

FeedbackPage::FeedbackPage(QWidget *parent) : QWidget(parent)
{
    this->setObjectName("LandingPage"); // Reuse landing page background style

    // Use the same container style as the login page for consistency
    QWidget *formContainer = new QWidget(this);
    formContainer->setObjectName("formContainer");
    formContainer->setMaximumWidth(550);

    auto titleLabel = new QLabel("Share Your Feedback", formContainer);
    titleLabel->setObjectName("titleLabel");

    auto descriptionLabel = new QLabel("We value your opinion. Please let us know how we did.", formContainer);
    descriptionLabel->setAlignment(Qt::AlignCenter);
    descriptionLabel->setWordWrap(true);

    m_feedbackTextEdit = new QTextEdit(formContainer);
    m_feedbackTextEdit->setPlaceholderText("Enter your comments here...");
    m_feedbackTextEdit->setMinimumHeight(100);

    auto submitButton = new QPushButton("Submit Feedback", formContainer);
    submitButton->setObjectName("successButton");

    // --- Layout for the form elements ---
    QVBoxLayout *formLayout = new QVBoxLayout(formContainer);
    formLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    formLayout->addWidget(descriptionLabel);
    formLayout->addSpacing(10);
    formLayout->addWidget(m_feedbackTextEdit);
    formLayout->addSpacing(10);
    formLayout->addWidget(submitButton);

    // --- Main layout to center the form on the page ---
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addStretch();
    mainLayout->addWidget(formContainer);
    mainLayout->addStretch();
    this->setLayout(mainLayout);

    // --- Connections ---
    connect(submitButton, &QPushButton::clicked, this, &FeedbackPage::onSubmitClicked);
}

FeedbackPage::~FeedbackPage() {}

void FeedbackPage::onSubmitClicked()
{
    if (m_feedbackTextEdit->toPlainText().trimmed().isEmpty()) {
        QMessageBox::warning(this, "Empty Feedback", "Please enter your feedback before submitting.");
        return;
    }

    // In a real app, you would save this feedback to a database.
    // For now, we just show a thank you message.
    QMessageBox::information(this, "Thank You!", "Your feedback has been submitted successfully. We appreciate your time.");

    m_feedbackTextEdit->clear(); // Clear the text for the next user
    emit feedbackSubmitted(); // Tell MainWindow to navigate away
}
