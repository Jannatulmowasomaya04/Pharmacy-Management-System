#include "cartpage.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

CartPage::CartPage(QList<CartItem>* cart, QWidget *parent) :
    QWidget(parent), m_cart(cart)
{
    auto titleLabel = new QLabel("Your Shopping Cart", this);
    titleLabel->setObjectName("titleLabel");
    m_cartTableWidget = new QTableWidget(this);
    m_subtotalLabel = new QLabel("Subtotal: €0.00", this);
    m_taxLabel = new QLabel("Tax (10%): €0.00", this);
    m_grandTotalLabel = new QLabel("Grand Total: €0.00", this);
    QFont totalsFont = m_grandTotalLabel->font();
    totalsFont.setBold(true);
    m_grandTotalLabel->setFont(totalsFont);
    auto confirmPurchaseButton = new QPushButton("Confirm Purchase", this);
    auto backToShopButton = new QPushButton("Back to Shop", this);
    backToShopButton->setObjectName("backToShopButton");

    m_cartTableWidget->setColumnCount(4);
    m_cartTableWidget->setHorizontalHeaderLabels({"Medicine", "Unit Price", "Quantity", "Total Price"});
    m_cartTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    m_cartTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QFormLayout *totalsLayout = new QFormLayout();
    QHBoxLayout *buttonsLayout = new QHBoxLayout();

    totalsLayout->addRow(m_subtotalLabel);
    totalsLayout->addRow(m_taxLabel);
    totalsLayout->addRow(m_grandTotalLabel);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(backToShopButton);
    buttonsLayout->addWidget(confirmPurchaseButton);

    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(m_cartTableWidget);
    mainLayout->addLayout(totalsLayout);
    mainLayout->addLayout(buttonsLayout);
    this->setLayout(mainLayout);

    connect(confirmPurchaseButton, &QPushButton::clicked, this, [this](){
        if(m_cart->isEmpty()){
            QMessageBox::warning(this, "Empty Cart", "Your cart is empty. Please add items before purchasing.");
            return;
        }
        emit purchaseConfirmed();
    });
    connect(backToShopButton, &QPushButton::clicked, this, [this](){ emit backToShopClicked(); });
}

CartPage::~CartPage() {}

void CartPage::updateCartView() {
    m_cartTableWidget->setRowCount(0);
    for (const auto& item : *m_cart) {
        int row = m_cartTableWidget->rowCount();
        m_cartTableWidget->insertRow(row);
        m_cartTableWidget->setItem(row, 0, new QTableWidgetItem(item.medicine.name));
        m_cartTableWidget->setItem(row, 1, new QTableWidgetItem("€" + QString::number(item.medicine.price, 'f', 2)));
        m_cartTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(item.quantity)));
        double total = item.medicine.price * item.quantity;
        m_cartTableWidget->setItem(row, 3, new QTableWidgetItem("€" + QString::number(total, 'f', 2)));
    }
    calculateTotals();
}

void CartPage::calculateTotals() {
    double subtotal = 0.0;
    for (const auto& item : *m_cart) {
        subtotal += item.medicine.price * item.quantity;
    }
    double tax = subtotal * 0.10;
    double grandTotal = subtotal + tax;
    m_subtotalLabel->setText(QString("Subtotal: €%1").arg(QString::number(subtotal, 'f', 2)));
    m_taxLabel->setText(QString("Tax (10%%): €%1").arg(QString::number(tax, 'f', 2)));
    m_grandTotalLabel->setText(QString("Grand Total: €%1").arg(QString::number(grandTotal, 'f', 2)));
}
