#ifndef FEEDBACKPAGE_H
#define FEEDBACKPAGE_H

#include <QWidget>

class QTextEdit; // Forward declaration

class FeedbackPage : public QWidget
{
    Q_OBJECT
public:
    explicit FeedbackPage(QWidget *parent = nullptr);
    ~FeedbackPage();

signals:
    // Signal to tell MainWindow the user is done and wants to go back
    void feedbackSubmitted();

private slots:
    void onSubmitClicked();

private:
    QTextEdit* m_feedbackTextEdit;
};

#endif // FEEDBACKPAGE_H
