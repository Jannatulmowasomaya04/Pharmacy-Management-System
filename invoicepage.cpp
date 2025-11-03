#include "invoicepage.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QDateTime>
#include <QRandomGenerator>
#include <QLabel>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>

InvoicePage::InvoicePage(QWidget *parent) : QWidget(parent) {
    this->setObjectName("InvoicePage");

    auto contentPanel = new QWidget(this);
    contentPanel->setObjectName("contentPanel");

    auto titleLabel = new QLabel("Purchase Successful!", contentPanel);
    titleLabel->setObjectName("titleLabel");

    auto invoicePanel = new QWidget(contentPanel);
    invoicePanel->setObjectName("invoicePanel");

    m_invoiceNumberLabel = new QLabel("Invoice #: ", invoicePanel);
    m_dateLabel = new QLabel("Date: ", invoicePanel);
    m_itemsTable = new QTableWidget(invoicePanel);
    m_subtotalLabel = new QLabel("€0.00", invoicePanel);
    m_taxLabel = new QLabel("€0.00", invoicePanel);
    m_grandTotalLabel = new QLabel("€0.00", invoicePanel);
    QFont grandTotalFont = m_grandTotalLabel->font();
    grandTotalFont.setBold(true);
    m_grandTotalLabel->setFont(grandTotalFont);

    m_itemsTable->setColumnCount(4);
    m_itemsTable->setHorizontalHeaderLabels({"Item Description", "Unit Price", "Qty", "Total"});
    m_itemsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    m_itemsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    m_itemsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_itemsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    QVBoxLayout* invoiceLayout = new QVBoxLayout(invoicePanel);
    QHBoxLayout* invoiceHeaderLayout = new QHBoxLayout();
    invoiceHeaderLayout->addWidget(m_invoiceNumberLabel);
    invoiceHeaderLayout->addStretch();
    invoiceHeaderLayout->addWidget(m_dateLabel);

    QFormLayout* totalsLayout = new QFormLayout();
    totalsLayout->addRow("Subtotal:", m_subtotalLabel);
    totalsLayout->addRow("Tax (10%):", m_taxLabel);
    totalsLayout->addRow("Grand Total:", m_grandTotalLabel);

    invoiceLayout->addLayout(invoiceHeaderLayout);
    invoiceLayout->addSpacing(15);
    invoiceLayout->addWidget(m_itemsTable);
    invoiceLayout->addLayout(totalsLayout);

    // !!! NEW: Buttons at the bottom !!!
    auto newSaleButton = new QPushButton("Buy More?", contentPanel);
    auto feedbackButton = new QPushButton("Submit Feedback", contentPanel);
    feedbackButton->setObjectName("successButton"); // Green button

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    buttonLayout->addWidget(feedbackButton);
    buttonLayout->addWidget(newSaleButton);

    // --- Layout for the whole page ---
    QVBoxLayout *contentPageLayout = new QVBoxLayout(contentPanel);
    contentPageLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    contentPageLayout->addWidget(invoicePanel);
    contentPageLayout->addLayout(buttonLayout);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->addWidget(contentPanel);

    connect(newSaleButton, &QPushButton::clicked, this, &InvoicePage::startNewSaleClicked);
    connect(feedbackButton, &QPushButton::clicked, this, &InvoicePage::submitFeedbackClicked);
}

InvoicePage::~InvoicePage() {}

void InvoicePage::setInvoiceDetails(const QList<CartItem>& cart) {
    quint32 invNum = QRandomGenerator::global()->generate() % 900000 + 100000;
    QString dateStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    m_invoiceNumberLabel->setText("<b>Invoice #:</b> " + QString::number(invNum));
    m_dateLabel->setText("<b>Date:</b> " + dateStr);

    m_itemsTable->setRowCount(0);
    double subtotal = 0.0;
    for (const auto& item : cart) {
        int row = m_itemsTable->rowCount();
        m_itemsTable->insertRow(row);
        m_itemsTable->setItem(row, 0, new QTableWidgetItem(item.medicine.name));
        m_itemsTable->setItem(row, 1, new QTableWidgetItem("৳" + QString::number(item.medicine.price, 'f', 2)));
        m_itemsTable->setItem(row, 2, new QTableWidgetItem(QString::number(item.quantity)));
        double total = item.medicine.price * item.quantity;
        m_itemsTable->setItem(row, 3, new QTableWidgetItem("৳" + QString::number(total, 'f', 2)));
        subtotal += total;
    }

    double tax = subtotal * 0.10;
    double grandTotal = subtotal + tax;
    m_subtotalLabel->setText("৳" + QString::number(subtotal, 'f', 2));
    m_taxLabel->setText("৳" + QString::number(tax, 'f', 2));
    m_grandTotalLabel->setText("৳" + QString::number(grandTotal, 'f', 2));
}
