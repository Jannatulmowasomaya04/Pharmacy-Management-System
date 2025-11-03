#include "dashboardpage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include <QHeaderView>
#include <QDebug>

// Constructor is the same as the last version you had
DashboardPage::DashboardPage(QList<CartItem>* cart, QWidget *parent)
    : QWidget(parent), m_cart(cart)
{
    this->setObjectName("DashboardPage");
    auto contentPanel = new QWidget(this);
    contentPanel->setObjectName("contentPanel");
    m_welcomeLabel = new QLabel("Welcome, Guest!", contentPanel);
    m_welcomeLabel->setObjectName("welcomeLabel");
    m_logoutButton = new QPushButton("Logout", contentPanel);
    m_logoutButton->setObjectName("logoutButton");
    m_categoryComboBox = new QComboBox(contentPanel);
    m_medicineTableWidget = new QTableWidget(contentPanel);
    m_addToCartSection = new QWidget(contentPanel);
    QHBoxLayout *addToCartLayout = new QHBoxLayout(m_addToCartSection);
    m_quantitySpinBox = new QSpinBox(m_addToCartSection);
    m_quantitySpinBox->setMinimum(1);
    m_quantitySpinBox->setValue(1);
    auto addToCartButton = new QPushButton("Add to Cart", m_addToCartSection);
    addToCartLayout->addStretch();
    addToCartLayout->addWidget(new QLabel("Quantity:", m_addToCartSection));
    addToCartLayout->addWidget(m_quantitySpinBox);
    addToCartLayout->addWidget(addToCartButton);
    addToCartLayout->addStretch();
    addToCartLayout->setContentsMargins(0,0,0,0);
    auto viewCartButton = new QPushButton("View Cart", contentPanel);
    m_medicineTableWidget->setColumnCount(3);
    m_medicineTableWidget->setHorizontalHeaderLabels({"Name", "Price (BDT)", "Available Stock"});
    m_medicineTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_medicineTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_medicineTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_medicineTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    QVBoxLayout *contentLayout = new QVBoxLayout(contentPanel);
    QHBoxLayout *headerLayout = new QHBoxLayout();
    headerLayout->addWidget(m_welcomeLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_logoutButton);
    contentLayout->addLayout(headerLayout);
    contentLayout->addSpacing(15);
    contentLayout->addWidget(new QLabel("Select Category:", contentPanel));
    contentLayout->addWidget(m_categoryComboBox);
    contentLayout->addWidget(m_medicineTableWidget);
    contentLayout->addWidget(m_addToCartSection);
    contentLayout->addSpacing(10);
    contentLayout->addWidget(viewCartButton);
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(contentPanel);
    this->setLayout(mainLayout);
    connect(m_categoryComboBox, &QComboBox::currentIndexChanged, this, &DashboardPage::onCategoryChanged);
    connect(addToCartButton, &QPushButton::clicked, this, &DashboardPage::onAddToCartClicked);
    connect(m_logoutButton, &QPushButton::clicked, this, [this](){ emit logoutClicked(); });
    connect(viewCartButton, &QPushButton::clicked, this, &DashboardPage::onViewCartClicked);
    setupMockData();
    populateCategories();
    setMode(Guest);
}

DashboardPage::~DashboardPage() {}

// !!! THE BIG DATA UPDATE IS HERE !!!
void DashboardPage::setupMockData() {
    m_medicineData.clear();
    int idCounter = 101;
    int stock = 100;

    m_medicineData["Pain Reliever"] = {
        {idCounter++, "Napa", "Pain Reliever", 2, stock},
        {idCounter++, "Roxicam", "Pain Reliever", 7, stock},
        {idCounter++, "Ace", "Pain Reliever", 2, stock},
        {idCounter++, "Napa Extra", "Pain Reliever", 3, stock},
        {idCounter++, "Panol", "Pain Reliever", 2, stock},
        {idCounter++, "Tylol", "Pain Reliever", 2, stock}
    };
    m_medicineData["Gastric"] = {
        {idCounter++, "Seclo", "Gastric", 5, stock},
        {idCounter++, "Losectil", "Gastric", 6, stock},
        {idCounter++, "Maxpro", "Gastric", 6, stock},
        {idCounter++, "Renorma", "Gastric", 2, stock},
        {idCounter++, "Seclo-Plus", "Gastric", 7, stock},
        {idCounter++, "Lansoprazole", "Gastric", 6, stock},
        {idCounter++, "Esoral", "Gastric", 7, stock},
        {idCounter++, "Domperidone", "Gastric", 5, stock},
        {idCounter++, "Itopride", "Gastric", 6, stock},
        {idCounter++, "Ranitin", "Gastric", 3, stock},
        {idCounter++, "Omez", "Gastric", 5, stock}
    };
    m_medicineData["Antibiotic"] = {
        {idCounter++, "Ciprocin", "Antibiotic", 10, stock},
        {idCounter++, "Flagyl", "Antibiotic", 3, stock},
        {idCounter++, "Filmet", "Antibiotic", 5, stock},
        {idCounter++, "Azith", "Antibiotic", 25, stock},
        {idCounter++, "Clavurin", "Antibiotic", 18, stock},
        {idCounter++, "Cetil", "Antibiotic", 20, stock},
        {idCounter++, "Azycin", "Antibiotic", 25, stock},
        {idCounter++, "Zimax", "Antibiotic", 28, stock},
        {idCounter++, "Norflox", "Antibiotic", 8, stock},
        {idCounter++, "Aristophen", "Antibiotic", 11, stock}
    };
    m_medicineData["Heart/Blood Pressure"] = {
        {idCounter++, "Amdocal", "Heart/Blood Pressure", 4, stock}
    };
    m_medicineData["Anti-allergic"] = {
        {idCounter++, "Fexo", "Anti-allergic", 8, stock},
        {idCounter++, "Monas", "Anti-allergic", 10, stock},
        {idCounter++, "Histacin", "Anti-allergic", 2, stock},
        {idCounter++, "Rupa", "Anti-allergic", 4, stock},
        {idCounter++, "Histagone", "Anti-allergic", 3, stock},
        {idCounter++, "Deslor", "Anti-allergic", 5, stock},
        {idCounter++, "Montene", "Anti-allergic", 10, stock},
        {idCounter++, "Loratin", "Anti-allergic", 3, stock}
    };
    m_medicineData["Injection"] = {
        {idCounter++, "Arixon", "Injection", 120, stock}
    };
    m_medicineData["Anti-diarrheal"] = {
        {idCounter++, "Neotack", "Anti-diarrheal", 1, stock},
        {idCounter++, "Amodis", "Anti-diarrheal", 2, stock}
    };
    m_medicineData["Multivitamin"] = {
        {idCounter++, "Aristovit-M", "Multivitamin", 5, stock},
        {idCounter++, "Bextram Gold", "Multivitamin", 10, stock}
    };
    m_medicineData["Mental Health"] = {
        {idCounter++, "Sertral", "Mental Health", 12, stock}
    };
    m_medicineData["Contraceptive"] = {
        {idCounter++, "Norpill", "Contraceptive", 20, stock}
    };
    m_medicineData["Antifungal"] = {
        {idCounter++, "Nizoral", "Antifungal", 15, stock},
        {idCounter++, "Ketoral", "Antifungal", 14, stock},
        {idCounter++, "Fungidal", "Antifungal", 12, stock}
    };
    m_medicineData["Skin"] = {
        {idCounter++, "Betnovate-N", "Skin", 18, stock}
    };
    m_medicineData["Cold & Cough"] = {
        {idCounter++, "Decil", "Cold & Cough", 3, stock}
    };
    m_medicineData["Motion Sickness"] = {
        {idCounter++, "Meclizine", "Motion Sickness", 4, stock}
    };
    m_medicineData["Vitamin C"] = {
        {idCounter++, "Ceevit", "Vitamin C", 2, stock}
    };
}


// ALL OTHER FUNCTIONS in dashboardpage.cpp remain the same as the last version
// (onViewCartClicked, setMode, updateWelcomeMessage, populateCategories, etc.)
void DashboardPage::onViewCartClicked(){ if (m_currentMode == Guest) { QMessageBox::information(this, "Login Required", "Please log in to view your cart and make a purchase."); emit loginRequired(); } else { emit viewCartClicked(); } }
void DashboardPage::setMode(Mode mode){ m_currentMode = mode; if (mode == Guest) { m_welcomeLabel->setText("Welcome, Guest!"); m_addToCartSection->hide(); m_logoutButton->hide(); } else { m_addToCartSection->show(); m_logoutButton->show(); } }
void DashboardPage::updateWelcomeMessage(const QString &username){ m_welcomeLabel->setText(QString("Welcome, %1!").arg(username)); }
void DashboardPage::populateCategories(){ m_categoryComboBox->blockSignals(true); m_categoryComboBox->clear(); m_categoryComboBox->addItems(m_medicineData.keys()); m_categoryComboBox->blockSignals(false); onCategoryChanged(0); }
void DashboardPage::onCategoryChanged(int){ QString selectedCategory = m_categoryComboBox->currentText(); populateMedicines(selectedCategory); }
void DashboardPage::populateMedicines(const QString &category){ m_medicineTableWidget->setRowCount(0); if (!m_medicineData.contains(category)) return; const QList<Medicine>& medicines = m_medicineData[category]; for (const auto& med : medicines) { int row = m_medicineTableWidget->rowCount(); m_medicineTableWidget->insertRow(row); m_medicineTableWidget->setItem(row, 0, new QTableWidgetItem(med.name)); m_medicineTableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(med.price, 'f', 2))); m_medicineTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(med.stock))); m_medicineTableWidget->item(row, 0)->setData(Qt::UserRole, med.id); } }
void DashboardPage::onAddToCartClicked(){ int selectedRow = m_medicineTableWidget->currentRow(); if (selectedRow < 0) { QMessageBox::warning(this, "Selection Error", "Please select a medicine from the table."); return; } int medicineId = m_medicineTableWidget->item(selectedRow, 0)->data(Qt::UserRole).toInt(); int quantity = m_quantitySpinBox->value(); QString category = m_categoryComboBox->currentText(); for (auto& med : m_medicineData[category]) { if (med.id == medicineId) { if (quantity > med.stock) { QMessageBox::warning(this, "Stock Error", "Not enough items in stock."); return; } med.stock -= quantity; m_cart->append({med, quantity}); QMessageBox::information(this, "Success", QString("%1 of %2 added to cart.").arg(quantity).arg(med.name)); m_quantitySpinBox->setValue(1); refreshTable(); return; } } }
void DashboardPage::refreshTable(){ populateMedicines(m_categoryComboBox->currentText()); }
