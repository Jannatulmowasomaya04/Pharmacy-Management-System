#include "mainwindow.h"
#include "landingpage.h"
#include "loginpage.h"
#include "registerpage.h"
#include "dashboardpage.h"
#include "cartpage.h"
#include "invoicepage.h"
#include "feedbackpage.h"
#include "datastructures.h"

#include <QFile>
#include <QDataStream> // !!! NEW: Include for file I/O !!!
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_stackedWidget = new QStackedWidget(this);
    this->setCentralWidget(m_stackedWidget);
    setWindowTitle("PharmaGo - Pharmacy Management System");

    m_cart = new QList<CartItem>();
    m_users = new QMap<QString, QString>();

    // !!! NEW: Load users from file at startup !!!
    loadUsersFromFile();

    setupPages();
    applyStylesheet();

    m_stackedWidget->setCurrentWidget(m_landingPage);
}

MainWindow::~MainWindow()
{
    // !!! NEW: Save users to file on exit !!!
    saveUsersToFile();

    delete m_cart;
    delete m_users;
}

// !!! NEW: Implementation to save the user map to a file !!!
void MainWindow::saveUsersToFile()
{
    QFile file("users.dat");
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning("Could not open users.dat for writing.");
        return;
    }

    QDataStream out(&file);
    out.setVersion(QDataStream::Qt_6_2); // Use a consistent Qt version
    out << *m_users; // Serialize the map to the file
    file.close();
    qDebug() << "User data saved successfully.";
}

// !!! NEW: Implementation to load the user map from a file !!!
void MainWindow::loadUsersFromFile()
{
    QFile file("users.dat");
    if (!file.exists()) {
        qDebug() << "users.dat not found. Creating a default admin user.";
        m_users->insert("admin", "admin"); // Create default if file doesn't exist
        return;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning("Could not open users.dat for reading.");
        return;
    }

    QDataStream in(&file);
    in.setVersion(QDataStream::Qt_6_2);
    in >> *m_users; // Deserialize the file into the map
    file.close();

    if (m_users->isEmpty()) {
        qDebug() << "User data file was empty. Creating a default admin user.";
        m_users->insert("admin", "admin");
    }

    qDebug() << "User data loaded successfully. Total users:" << m_users->count();
}


void MainWindow::setupPages()
{
    m_landingPage = new LandingPage(this);
    m_loginPage = new LoginPage(m_users, this);
    m_registerPage = new RegisterPage(m_users, this);
    m_dashboardPage = new DashboardPage(m_cart, this);
    m_cartPage = new CartPage(m_cart, this);
    m_invoicePage = new InvoicePage(this);
    m_feedbackPage = new FeedbackPage(this);

    m_stackedWidget->addWidget(m_landingPage);
    m_stackedWidget->addWidget(m_loginPage);
    m_stackedWidget->addWidget(m_registerPage);
    m_stackedWidget->addWidget(m_dashboardPage);
    m_stackedWidget->addWidget(m_cartPage);
    m_stackedWidget->addWidget(m_invoicePage);
    m_stackedWidget->addWidget(m_feedbackPage);

    connect(m_landingPage, &LandingPage::browseAsGuestClicked, this, &MainWindow::goToDashboardAsGuest);
    connect(m_landingPage, &LandingPage::loginRegisterClicked, this, &MainWindow::goToLoginPage);
    connect(m_loginPage, &LoginPage::loginSuccessful, this, &MainWindow::goToDashboardAsUser);
    connect(m_loginPage, &LoginPage::registerRequested, this, &MainWindow::goToRegisterPage);
    connect(m_loginPage, &LoginPage::backToLandingClicked, this, &MainWindow::goToLandingPage);
    connect(m_registerPage, &RegisterPage::registrationSuccessful, this, &MainWindow::goToLoginPage);
    connect(m_registerPage, &RegisterPage::loginRequested, this, &MainWindow::goToLoginPage);
    connect(m_dashboardPage, &DashboardPage::viewCartClicked, this, &MainWindow::goToCartPage);
    connect(m_dashboardPage, &DashboardPage::logoutClicked, this, &MainWindow::handleLogout);
    connect(m_dashboardPage, &DashboardPage::loginRequired, this, &MainWindow::goToLoginPage);
    connect(m_cartPage, &CartPage::backToShopClicked, this, [this]() {
        goToDashboardAsUser(m_currentUsername);
    });
    connect(m_cartPage, &CartPage::purchaseConfirmed, this, &MainWindow::goToInvoicePage);
    connect(m_invoicePage, &InvoicePage::startNewSaleClicked, this, [this]() {
        goToDashboardAsUser(m_currentUsername);
    });
    connect(m_invoicePage, &InvoicePage::submitFeedbackClicked, this, &MainWindow::goToFeedbackPage);
    connect(m_feedbackPage, &FeedbackPage::feedbackSubmitted, this, &MainWindow::goToLandingPage);
}

void MainWindow::applyStylesheet()
{
    QFile styleFile(":/styles/style.qss");
    if (styleFile.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(styleFile.readAll());
        this->setStyleSheet(styleSheet);
    } else {
        qDebug() << "Could not load stylesheet.";
    }
}

void MainWindow::goToLandingPage() { m_stackedWidget->setCurrentWidget(m_landingPage); }
void MainWindow::goToLoginPage() { m_stackedWidget->setCurrentWidget(m_loginPage); }
void MainWindow::goToRegisterPage() { m_stackedWidget->setCurrentWidget(m_registerPage); }

void MainWindow::goToDashboardAsGuest()
{
    m_dashboardPage->setMode(DashboardPage::Guest);
    m_stackedWidget->setCurrentWidget(m_dashboardPage);
}

void MainWindow::goToDashboardAsUser(const QString& username)
{
    m_currentUsername = username;
    m_dashboardPage->setMode(DashboardPage::LoggedIn);
    m_dashboardPage->updateWelcomeMessage(username);
    m_stackedWidget->setCurrentWidget(m_dashboardPage);
}

void MainWindow::goToCartPage()
{
    m_cartPage->updateCartView();
    m_stackedWidget->setCurrentWidget(m_cartPage);
}

void MainWindow::goToInvoicePage()
{
    m_invoicePage->setInvoiceDetails(*m_cart);
    m_cart->clear();
    m_dashboardPage->refreshTable();
    m_stackedWidget->setCurrentWidget(m_invoicePage);
}

void MainWindow::goToFeedbackPage()
{
    m_stackedWidget->setCurrentWidget(m_feedbackPage);
}

void MainWindow::handleLogout()
{
    m_currentUsername.clear();
    m_cart->clear();
    goToLandingPage();
}
