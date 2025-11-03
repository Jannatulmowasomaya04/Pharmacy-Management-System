#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QList>
#include <QMap>

// Forward declarations
class LandingPage;
class LoginPage;
class RegisterPage;
class DashboardPage;
class CartPage;
class InvoicePage;
class FeedbackPage;
struct CartItem;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void goToLandingPage();
    void goToLoginPage();
    void goToRegisterPage();
    void goToDashboardAsGuest();
    void goToDashboardAsUser(const QString& username);
    void goToCartPage();
    void goToInvoicePage();
    void goToFeedbackPage();
    void handleLogout();

private:
    void setupPages();
    void applyStylesheet();
    void saveUsersToFile();
    void loadUsersFromFile();

    QStackedWidget *m_stackedWidget;

    // Page pointers
    LandingPage* m_landingPage;
    LoginPage* m_loginPage;
    RegisterPage* m_registerPage;
    DashboardPage* m_dashboardPage;
    CartPage* m_cartPage;
    InvoicePage* m_invoicePage;
    FeedbackPage* m_feedbackPage;

    // Shared Data
    QList<CartItem>* m_cart;
    QMap<QString, QString>* m_users;
    QString m_currentUsername;
};

#endif // MAINWINDOW_H
